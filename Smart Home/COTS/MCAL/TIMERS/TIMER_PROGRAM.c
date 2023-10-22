/*
 * TIMER_PROGRAM.c
 *
 *  Created on: 15Aug.,2023
 *      Author: abdel
 */


#include "../../LIB/STD.h"
#include "../../LIB/BitMath.h"
#include "TIMER_INTERFACE.h"
#include "TIMER_PRIVATE.h"
#include "TIMER_CONFIG.h"

volatile static void (*Glopal_Ptr2Func)(void) = NULL;
void TMR0_Init(TMR0_Conf_t *Ptr_Conf)
{
	if(Ptr_Conf->Mode == Normal_mode || Ptr_Conf->Mode == Compare_Mood )
	{
		//NON PWM MODE SET FOC0 in TCCR0
		SET_BIT(TCCR0_REG,FOC0_BIT);
	}
	else
	{
		//PWM MODE CLR FOC0 in TCCR0
		CLR_BIT(TCCR0_REG,FOC0_BIT);
	}
	switch(Ptr_Conf->Mode)
	{
		case Normal_mode:
		{
			CLR_BIT(TCCR0_REG,WGM01_BIT);
			CLR_BIT(TCCR0_REG,WGM00_BIT);
		}
		break;
		case PWM_Phase_correct:
		{
			CLR_BIT(TCCR0_REG,WGM01_BIT);
			SET_BIT(TCCR0_REG,WGM00_BIT);
			TCCR0_REG &= 0xcf;
			TCCR0_REG |= ((Ptr_Conf->OC0_PhaseCorrectPWM) << 4);

//			switch(Ptr_Conf->OC0_PhaseCorrectPWM)
//			{
//				case PhaseNon_inverting:
//				{
//					CLR_BIT(TCCR0_REG,4);
//					SET_BIT(TCCR0_REG,5);
//				}
//				break;
//				case PhaseInverting:
//				{
//					SET_BIT(TCCR0_REG,4);
//					SET_BIT(TCCR0_REG,5);
//				}
//				break;
//				default:
//				break;
//			}
		}
		break;
		case Compare_Mood:
		{
			SET_BIT(TCCR0_REG,WGM01_BIT);
			CLR_BIT(TCCR0_REG,WGM00_BIT);
		}
		break;
		case Fast_PWM:
		{
			SET_BIT(TCCR0_REG,WGM01_BIT);
			SET_BIT(TCCR0_REG,WGM00_BIT);
			TCCR0_REG &= 0xcf;
			TCCR0_REG |= ((Ptr_Conf->OC0_FastPWM) << 4);
//			{
//				case FastNon_inverting:
//				{
//					CLR_BIT(TCCR0_REG,4);
//					SET_BIT(TCCR0_REG,5);
//				}
//				break;
//				case FastInverting:
//				{
//					SET_BIT(TCCR0_REG,4);
//					SET_BIT(TCCR0_REG,5);
//				}
//				break;
//				default:
//				break;
//			}
		}
		break;
		default:
		break;
	}
	// Clearing Least significant three bits in TCCR0
	TCCR0_REG &= 0xF8;
	//Inserting required clock select
	TCCR0_REG |= Ptr_Conf->CLOCK;
	switch(Ptr_Conf->Technique)
	{
	  case POLLING:
	  break;
	  case INTERRUPT:
	  {
		  switch(Ptr_Conf->Mode)
		  {
		  	  case Normal_mode: SET_BIT(TIMSK_REG,TOIE0_BIT);
		  	  break;
		  	  case Compare_Mood: SET_BIT(TIMSK_REG,OCIE0_BIT);
		  	  break;
		  }
	  }
	  break;
	}
	TCNT0_REG = 0;
}
void TMR0_Start(TMR0_Conf_t *Ptr_Conf)
{
	switch(Ptr_Conf->Mode)
	{
		case Normal_mode:
		{
			TCNT0_REG = Ptr_Conf->Preload_Value;
			switch(Ptr_Conf->Technique)
			{
				case POLLING:
				{
					//WAIT UNTIL TIMER FINISHES COUNTING
					while(GET_BIT(TIFR_REG,TOV0_BIT) == 0);
					//CLEARING FLAG
					SET_BIT(TIFR_REG,TOV0_BIT);
				}
				break;
				case INTERRUPT:
				break;
			}
		}
		break;
		case PWM_Phase_correct:
		{
			TCNT0_REG = Ptr_Conf->Preload_Value;
			OCR0_REG  = Ptr_Conf->Compare_Value;
		}
		break;
		case Compare_Mood:
		{
			TCNT0_REG = Ptr_Conf->Preload_Value;
			OCR0_REG  = Ptr_Conf->Compare_Value;
			switch(Ptr_Conf->Technique)
			{
				case POLLING:
				{
					//WAIT UNTIL TIMER FINISHES COUNTING
					while(GET_BIT(TIFR_REG,OCF0_BIT) == 0);
					//CLEARING FLAG
					SET_BIT(TIFR_REG,OCF0_BIT);
				}
				break;
				case INTERRUPT:
				break;
			}
		}
		break;
		case Fast_PWM:
		{
			TCNT0_REG = Ptr_Conf->Preload_Value;
			OCR0_REG  = Ptr_Conf->Compare_Value;
		}
		break;
		default:
		break;
	}
}
void TMR0_DeInit(void)
{
	TCCR0_REG  = 0;
	TCNT0_REG  = 0;
	TIMSK_REG &= 0xFC;
	OCR0_REG   = 0;
}
void TMR1_Init(void)
{
//		/*NORMAL MOOD*/
//		CLR_BIT(TCCR1A_REG,0);
//		CLR_BIT(TCCR1A_REG,1);
//		CLR_BIT(TCCR1B_REG,3);
//		CLR_BIT(TCCR1B_REG,4);
//
//		/*PRESCALER*/
//		CLR_BIT(TCCR1B_REG,0);
//		SET_BIT(TCCR1B_REG,1);
//	    CLR_BIT(TCCR1B_REG,2);
//
//	    //Enable PIE
//	    SET_BIT(TIMSK_REG,2);
	/*FAST PWM*/
	CLR_BIT(TCCR1A_REG,0);
	SET_BIT(TCCR1A_REG,1);
	SET_BIT(TCCR1B_REG,3);
	SET_BIT(TCCR1B_REG,4);

	/*NON INVERTED*/

	SET_BIT(TCCR1A_REG,7);
	CLR_BIT(TCCR1A_REG,6);


	/*PRESCALER*/
	CLR_BIT(TCCR1B_REG,0);
	SET_BIT(TCCR1B_REG,1);
    CLR_BIT(TCCR1B_REG,2);
    /*SET ICR*/
    TMR1_voidSetICRValue(20000);
}
void TMR1_voidSetCompareVal(u16 copy_u16CompareValue)
{
	OCR1A_REG = copy_u16CompareValue;
}
void TMR1_voidSetICRValue(u16 copy_u16ICRValue)
{
   ICR1_REG = copy_u16ICRValue;
}
u16 TMR1_u16ReadTCNT1(void)
{
	return TCNT1_REG;
}
void TMR1_voidWriteTCNT1(u16 copy_u16TCNT1Value)
{
	TCNT1_REG = 0;
}
void TMR1_SetCallBack(void (*Ptr2Func) (void))
{
	Glopal_Ptr2Func = Ptr2Func;
}
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	if(Glopal_Ptr2Func != NULL)
	{
		Glopal_Ptr2Func();
	}
}



//void TMR0_SetCallBack(void (*Ptr2Func) (void))
//{
//
//	Glopal_Ptr2Func = Ptr2Func;
//}
//
//
//void __vector_10_(void) __attribute__((signal));
//void __vector_10_(void)
//{
//	if(Glopal_Ptr2Func != NULL)
//	{
//		Glopal_Ptr2Func();
//	}
//}
//u8 TMR0_SwitchCounter(void)
//{
//	return TCNT0_REG;
//}



