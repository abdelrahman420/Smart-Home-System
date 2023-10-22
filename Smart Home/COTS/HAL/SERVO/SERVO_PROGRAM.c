
#include "../../MCAL/TIMERS/TIMER_INTERFACE.h"
#include "SERVO_INTERFACE.h"
#include "SERVO_PRIVATE.h"
#include "SERVO_CONFIG.h"

void Servo_voidInit(void)
{
	TMR1_Init();
}
void Servo_voidSetAngle(u8 copy_u8Angle)
{
	u16 Local_u16CompareVal;
	Local_u16CompareVal = ((100/9)*copy_u8Angle) + 500;
	TMR1_voidSetCompareVal(Local_u16CompareVal);
}


