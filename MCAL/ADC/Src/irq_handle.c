/*
 * irq_handle.c
 *
 *  Created on: Sep 11, 2025
 *      Author: Lenovo X13
 */

#include "irq_handle.h"

#define NVIC_NUM_PRIO_BITS	4u
#define NVIC_IPR_SHIFT		4u

void nvic_enable_irq(IRQn_Type irqn)
{
    if ((int32_t)irqn < 0) return;
    NVIC->ISER[(uint32_t)irqn >> 5u] = (uint32_t)1u << ((uint32_t)irqn & 31u);
}

void nvic_disable_irq(IRQn_Type irqn)
{
    if ((int32_t)irqn < 0) return;
    NVIC->ICER[(uint32_t)irqn >> 5u] = (uint32_t)1u << ((uint32_t)irqn & 31u);
    /* Clear any pending */
    NVIC->ICPR[(uint32_t)irqn >> 5u] = (uint32_t)1u << ((uint32_t)irqn & 31u);
}

void nvic_set_priority(IRQn_Type irqn, uint32_t prio)
{
    prio &= ((1u << NVIC_NUM_PRIO_BITS) - 1u);

    if ((int32_t)irqn >= 0) {
        /* External interrupt priority lives in NVIC->IP[]; only top 4 bits used */
        NVIC->IP[(uint32_t)irqn] = (uint8_t)(prio << NVIC_IPR_SHIFT);
    }
}


void cpu_irq_enable(void)  { __asm volatile ("cpsie i" ::: "memory"); }
void cpu_irq_disable(void) { __asm volatile ("cpsid i" ::: "memory"); }
