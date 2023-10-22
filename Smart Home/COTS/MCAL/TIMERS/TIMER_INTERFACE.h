/*
 * TIMER_INTERFACE.h
 *
 *  Created on: 15Aug.,2023
 *      Author: abdel
 */

#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include "../../LIB/STD.h"

typedef enum
{
	Normal_mode,
	PWM_Phase_correct,
	Compare_Mood,
	Fast_PWM
}TMR0_Mode_t;

typedef enum
{
	Disconnect_OC0,
	Toggle,
	Clear_OC0,
	Set_OC0
}TMR0_OC0_NonPWM_t;
typedef enum
{
	FastNon_inverting = 2,
	FastInverting
}TMR0_OC0_FastPWM_t;

typedef enum
{
	PhaseNon_inverting = 2,
	PhaseInverting
}TMR0_OC0_PhaseCorrectPWM_t;
typedef enum
{
	No_CLK,
	CLK_FCPU,
	CLK_FCPU_8,
	CLK_FCPU_64,
	CLK_FCPU_256,
	CLK_FCPU_1024,
	External_Falling,
	External_Rising
}TMR0_CLKSEL_t;
typedef enum
{
	POLLING,
	INTERRUPT
}TMR0_Technique;
typedef struct
{
	TMR0_Mode_t        			Mode;
	TMR0_OC0_NonPWM_t  			OC0_Options;
	TMR0_OC0_FastPWM_t          OC0_FastPWM;
	TMR0_OC0_PhaseCorrectPWM_t  OC0_PhaseCorrectPWM;
	TMR0_CLKSEL_t       		CLOCK;
	u8                 			Preload_Value;
	u8						    Compare_Value;
	TMR0_Technique     			Technique;

}TMR0_Conf_t;

void TMR0_Init(TMR0_Conf_t *Ptr_Conf);
void TMR0_Start(TMR0_Conf_t *Ptr_Conf);
void TMR0_DeInit(void);
void TMR0_SetCallBack(void (*Ptr2Func) (void));
u8 TMR0_SwitchCounter(void);
void TMR1_Init(void);
void TMR1_voidSetCompareVal(u16 copy_u16CompareValue);
void TMR1_voidSetICRValue(u16 copy_u16ICRValue);
u16 TMR1_u16ReadTCNT1(void);
void TMR1_voidWriteTCNT1(u16 copy_u16TCNT1Value);
void TMR1_SetCallBack(void (*Ptr2Func) (void));



#endif /* COTS_MCAL_TIMERS_TIMER_INTERFACE_H_ */
