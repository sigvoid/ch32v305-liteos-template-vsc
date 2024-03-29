SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.12)

SET(CPU_FLAGS "-march=rv32imacxw -mabi=ilp32")
SET(COMMON_FLAGS
    "${CPU_FLAGS} -msmall-data-limit=8 -msave-restore \
    -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections \
    -fno-common -nostartfiles --specs=nano.specs --specs=nosys.specs \
    -Wall -Wextra -Wno-missing-field-initializers -Wno-comment -Wno-cast-function-type \
    -Werror=return-type -Werror=return-local-addr -Werror=uninitialized"
)

SET(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/Ld/Link.ld")
SET(CMAKE_ASM_FLAGS_INIT "${COMMON_FLAGS} -x assembler-with-cpp")
SET(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS}")
SET(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -fno-rtti -fno-exceptions -fno-unwind-tables -Wno-volatile")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections,--print-memory-usage -T ${LINKER_SCRIPT}")

# Project
project(app C CXX ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS
    Ld/Link.ld
    Startup/startup_ch32v30x_D8C.S
    Core/*.*
    Debug/*.*
    Peripheral/src/*.*
    User/*.*

    LiteOS_device/arch/risc-v/V4A/gcc/*.*
    LiteOS_device/config/*.*

    LiteOS/arch/risc-v/common/*.c

    LiteOS/kernel/src/*.c
    LiteOS/utils/*.c
    LiteOS/kal/cmsis/*.c
    third_party/bounds_checking_function/src/*.c
)

message("src files:")
foreach(file ${SRCS})
    message(STATUS ${file})
endforeach()

add_executable(${PROJECT_NAME}.elf ${SRCS})
target_link_libraries(${PROJECT_NAME}.elf PRIVATE m)
target_include_directories(${PROJECT_NAME}.elf PUBLIC
    Startup
    Debug
    Core
    User
    Peripheral/inc

    LiteOS_device/arch/risc-v/V4A/gcc
    LiteOS_device/config

    LiteOS/arch/risc-v/riscv32/gcc/asm
    LiteOS/arch/risc-v/common
    LiteOS/arch/include

    LiteOS/utils
    LiteOS/kernel/include
    third_party/bounds_checking_function/include
    third_party/cmsis/CMSIS/Core/Include
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")


set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${HEX_FILE}\nBuilding ${BIN_FILE}"
)

