#ifndef _BSP_H_
#define _BSP_H_

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/* 提供给其他C文件调用的函数 */
void bsp_Init(void);
void bsp_Idle(void);

#endif

