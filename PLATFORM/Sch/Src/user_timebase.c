/*
 * user_timebase.c
 *
 *  Created on: Jan 12, 2026
 *      Author: Lenovo X13
 */


#include "user_timebase.h"

static volatile uint32_t g_userMs = 0;

uint32_t User_GetMs(void)
{
    return g_userMs;
}

// called from SysTick_Handler
void User_Timebase_Inc1ms(void)
{
    g_userMs++;
}
