/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _SOC_H
#define _SOC_H
#include "soc_common.h"

/*
 * Get the response interrupt number via mcause.
 * id = mcause & MCAUSE_INT_ID_MASK
 */
// #define MSIP                                          0x2000000
// #define MTIMERCMP                                     0x2004000
// #define MTIMER                                        0x200BFF8
// #define CLOCK_CONTRAL_REG                             0x10008000

// #define UART0_BASE                                     0x10000000

// #define UART0_CLK_FREQ                                 0x32000000
// #define UART0_BAUDRAT                                  115200

#define SOC_INT_MAX                                    103

#endif
