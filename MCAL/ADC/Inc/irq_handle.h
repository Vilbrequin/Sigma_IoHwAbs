/*
 * irq_handle.h
 *
 *  Created on: Sep 11, 2025
 *      Author: Lenovo X13
 */

#ifndef INC_IRQ_HANDLE_H_
#define INC_IRQ_HANDLE_H_


#include <stdint.h>
#include "stm32f4xx.h"

void nvic_enable_irq(IRQn_Type irqn);
void nvic_disable_irq(IRQn_Type irqn);
void nvic_set_priority(IRQn_Type irqn, uint32_t prio);
void cpu_irq_enable(void);
void cpu_irq_disable(void);

#endif /* INC_IRQ_HANDLE_H_ */
