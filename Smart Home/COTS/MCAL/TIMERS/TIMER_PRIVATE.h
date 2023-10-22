/*
 * TIMER_PRIVATE.h
 *
 *  Created on: 15Aug.,2023
 *      Author: abdel
 */

#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H


#define TCCR0_REG  *((volatile u8*)0x53)


#define WGM01_BIT    3
#define WGM00_BIT    6
#define FOC0_BIT     7



#define TCNT0_REG  *((volatile u8*)0x52)
#define OCR0_REG   *((volatile u8*)0x5C)

#define TOIE0_BIT  0
#define OCIE0_BIT  0



#define TIMSK_REG  *((volatile u8*)0x59)
#define TIFR_REG   *((volatile u8*)0x58)

#define TOV0_BIT  0
#define OCF0_BIT  1


#define TCCR1A_REG	*((volatile u8*)0x4F)
#define TCCR1B_REG	*((volatile u8*)0x4E)
#define TCNT1_REG   *((volatile u16*)0x4C)
#define OCR1A_REG	*((volatile u16*)0x4A)
#define OCR1B_REG	*((volatile u16*)0x48)
#define ICR1_REG 	*((volatile u16*)0x46)



#endif /* COTS_MCAL_TIMERS_TIMER_PRIVATE_H_ */
