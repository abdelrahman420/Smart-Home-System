///*
// * APP.c
// *
// *  Created on: 30Aug.,2023
// *      Author: abdel
// */
//
#define F_CPU 8000000UL
#include <util/delay.h>

#include "../LIB/STD.h"
#include "../LIB/BitMath.h"

#include "../MCAL/DIO/DIO_INTERFACE.h"
#include "../MCAL/USART/USART_INTERFACE.h"

#include "../HAL/LED/LED_INTERFACE.h"
#include "../HAL/LCD/LCD_INTERFACE.h"
#include "../HAL/SERVO/SERVO_INTERFACE.h"

#include "APP.h"
typedef struct
{
	u8 UserName[10];
	u8 PassWord[10];
}Users_t;
Users_t UsersArray[10] =
{
		{"ahmed","1234"},{"abdo","9845"},
		{"galal","9267"},{"reda","3284"},
		{"asmaa","2974"},{"hamze","69420"},
		{"alaa","6222"},{"sama","1547"},
		{"khamis","2468"},{"samy","0000"}
};
LED_t RLED1 = {DIO_PORTD,DIO_PIN2,Active_High};
LED_t RLED2 = {DIO_PORTD,DIO_PIN3,Active_High};
LED_t GLED1 = {DIO_PORTD,DIO_PIN6,Active_High};
LED_t GLED2 = {DIO_PORTD,DIO_PIN7,Active_High};
Users_t User1;
u8 i = 0;
u8 flag = 0;
u8 attempts = 0;
u8 Choice1,Choice2;
u8 UserCorrect = 0;
u8 PassCorrect = 0;
void APP_voidInit(void)
{
	USART_voidInit(9600);
	LED_voidInit(&RLED1);
	LED_voidInit(&RLED2);
	LED_voidInit(&GLED1);
	LED_voidInit(&GLED2);
	LCD_voidInit();
	Servo_voidInit();
	Servo_voidSetAngle(90);
	/* BUZZER PIN CONFIGURATION AS OUTPUT */
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN4,DIO_OUTPUT);
	/* SERVO PIN CONFIGURATION AS OUTPUT */
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);

}
void SmartHome(void)
{
	while (attempts < 3 && UserCorrect == 0)
	{
		_delay_ms(1000);
		LCD_voidsendCommand(LCD_CLR_DISPLAY);
		USART_voidSendString("ENTER USERNAME\n\r");
		LCD_voidSendString((u8 *)"ENTER USER NAME");
		USART_voidRecieveString(User1.UserName);
		LCD_voidSetPosition(LCD_ROW_2,LCD_COL_1);
		for(u8 j = 0;j <10;j++ )
		{
			while(User1.UserName[i] != '\0')
			{
				if(User1.UserName[i] == UsersArray[j].UserName[i])
				{
					flag++;
				}
				i++;
			}
			if(flag == i)
			{
				UserCorrect = 1;
				break;
			}
			i = 0;
			flag = 0;
		}
		USART_voidSendString(User1.UserName);
		USART_voidSendString("\n\r");
		LCD_voidSendString(User1.UserName);
		_delay_ms(1000);
		LCD_voidsendCommand(LCD_CLR_DISPLAY);
		if (UserCorrect == 0)
		{
			USART_voidSendString("Invalid username. Try again.\n\r");
			LCD_voidsendCommand(LCD_CLR_DISPLAY);
			LCD_voidSendString((u8 *)"Invalid username.");
			LCD_voidSetPosition(LCD_ROW_2,LCD_COL_1);
			LCD_voidSendString((u8 *)"Try again.      ");
			attempts++;
		}
	}
	if(UserCorrect == 0)
	{
		LED_voidOn(&RLED1);
		LED_voidOn(&RLED2);
		USART_voidSendString("Access denied. Maximum attempts exceeded.\n\r");
		LCD_voidsendCommand(LCD_CLR_DISPLAY);
		LCD_voidSendString((u8 *)"Access denied.");
		LCD_voidSetPosition(LCD_ROW_2,LCD_COL_1);
		LCD_voidSendString((u8 *)"3 trials reached");
		DIO_voidSetPinValue(DIO_PORTD,DIO_PIN4,DIO_HIGH);
	}
	if (UserCorrect == 1 && attempts < 3)
	{
		attempts = 0;
		_delay_ms(1000);
		LCD_voidsendCommand(LCD_CLR_DISPLAY);
		USART_voidSendString("USER NAME OK\n\r");
		LCD_voidSendString((u8 *)"USER NAME OK");
		_delay_ms(1000);
		LCD_voidsendCommand(LCD_CLR_DISPLAY);
		USART_voidSendString("ENTER PASSWORD\n\r");
		LCD_voidSendString((u8 *)"ENTER PASSWORD");
		while (attempts < 3 && PassCorrect == 0)
		{
			USART_voidRecieveString(User1.PassWord);
			LCD_voidSetPosition(LCD_ROW_2,LCD_COL_1);
			flag = 0;
			i = 0;
			for(u8 j = 0;j <10;j++ )
			{
				while(User1.PassWord[i] != '\0')
				{
					if(User1.PassWord[i] == UsersArray[j].PassWord[i])
					{
						flag++;
					}
					i++;
				}
				if(flag == i)
				{
					PassCorrect = 1;
					break;
				}
				i = 0;
				flag = 0;
			}
			USART_voidSendString(User1.PassWord);
			USART_voidSendString("\n\r");
			LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
			LCD_voidSendString("*****");
			_delay_ms(1000);
			LCD_voidsendCommand(LCD_CLR_DISPLAY);
			if (PassCorrect == 0)
			{
				USART_voidSendString("Invalid password. Try again.\n\r");
				LCD_voidsendCommand(LCD_CLR_DISPLAY);
				LCD_voidSendString((u8 *)"Invalid password.");
				LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
				LCD_voidSendString((u8 *)"Try again.      ");
				_delay_ms(1000);
				LCD_voidsendCommand(LCD_CLR_DISPLAY);
				LCD_voidSendString((u8 *)"REENTER PASSWORD");
				attempts++;
			}
		}
		if(PassCorrect == 0)
		{
			LED_voidOn(&RLED1);
			LED_voidOn(&RLED2);
			USART_voidSendString("Access denied. Maximum attempts exceeded.\n\r");
			LCD_voidsendCommand(LCD_CLR_DISPLAY);
			LCD_voidSendString((u8 *)"Access denied.");
			LCD_voidSetPosition(LCD_ROW_2,LCD_COL_1);
			LCD_voidSendString((u8 *)"3 trials reached");
			DIO_voidSetPinValue(DIO_PORTD,DIO_PIN4,DIO_HIGH);
		}
		if(PassCorrect == 1)
		{
			LCD_voidsendCommand(LCD_CLR_DISPLAY);
			USART_voidSendString("Access granted.\n\r");
			LCD_voidSendString((u8 *)"PASSWORD OK");
			LCD_voidSetPosition(LCD_ROW_2,LCD_COL_1);
			LCD_voidSendString((u8 *)"Access granted.");
			_delay_ms(1000);
			LCD_voidsendCommand(LCD_CLR_DISPLAY);
			LCD_voidSendString((u8 *)"WELCOME ");
			LCD_voidSetPosition(LCD_ROW_1,LCD_COL_9);
			LCD_voidSendString(User1.UserName);
			_delay_ms(1000);
			LCD_voidsendCommand(LCD_CLR_DISPLAY);
			USART_voidSendString("1-DOOR CONTROL\n\r");
			LCD_voidSendString((u8 *)"1-DOOR CONTROL");
			LCD_voidSetPosition(LCD_ROW_2,LCD_COL_1);
			USART_voidSendString("2-LIGHT CONTROL\n\r");
			LCD_voidSendString((u8 *)"2-LIGHT CONTROL");
			while (1)
			{
				Choice1 = USART_u16ReceiveData();
				if (Choice1 == '1')
				{
					LCD_voidsendCommand(LCD_CLR_DISPLAY);
					LCD_voidSetPosition(LCD_ROW_1, LCD_COL_1);
					USART_voidSendString("1-OPEN\n\r");
					LCD_voidSendString("1-OPEN ");
					LCD_voidSetPosition(LCD_ROW_1, LCD_COL_10);
					USART_voidSendString("2-BacK \n\r");
					LCD_voidSendString("2-BacK ");
					LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
					USART_voidSendString("3-CLOSE\n\r");
					LCD_voidSendString("3-CLOSE");
					while(1)
					{
						Choice2 = USART_u16ReceiveData();
						if (Choice2 == '1')
						{
							LCD_voidsendCommand(LCD_CLR_DISPLAY);
							Servo_voidSetAngle(180);
							USART_voidSendString("DOOR OPENED\n\r");
							LCD_voidSendString((u8 *)"DOOR OPENED");
							LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
							LCD_voidSendString("2-BacK ");
						}
						else if (Choice2 == '2')
						{
							break;
						}
						else if (Choice2 == '3')
						{
							LCD_voidsendCommand(LCD_CLR_DISPLAY);
							Servo_voidSetAngle(0);
							USART_voidSendString("DOOR CLOSED\n\r");
							LCD_voidSendString("DOOR CLOSED");
							LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
							LCD_voidSendString("2-BacK ");
						}
					}
					LCD_voidsendCommand(LCD_CLR_DISPLAY);
					USART_voidSendString("1-DOOR CONTROL\n\r");
					LCD_voidSendString((u8 *)"1-DOOR CONTROL");
					LCD_voidSetPosition(LCD_ROW_2,LCD_COL_1);
					USART_voidSendString("2-LIGHT CONTROL\n\r");
					LCD_voidSendString((u8 *)"2-LIGHT CONTROL");
				}
				else if (Choice1 == '2')
				{
					LCD_voidsendCommand(LCD_CLR_DISPLAY);
					LCD_voidSetPosition(LCD_ROW_1, LCD_COL_1);
					USART_voidSendString("1-TURN ON\n\r");
					LCD_voidSendString("1-TURN ON ");
					LCD_voidSetPosition(LCD_ROW_1, LCD_COL_10);
					USART_voidSendString("2-BacK \n\r");
					LCD_voidSendString("2-BacK ");
					LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
					USART_voidSendString("3-TURN OFF\n\r");
					LCD_voidSendString("3-TURN OFF");
					while(1)
					{
						Choice2 = USART_u16ReceiveData();
						if (Choice2 == '1')
						{
							LCD_voidsendCommand(LCD_CLR_DISPLAY);
							LED_voidOn(&GLED1);
							LED_voidOn(&GLED2);
							USART_voidSendString("LIGHT ON\n\r");
							LCD_voidSendString((u8 *)"LIGHT ON");
							LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
							LCD_voidSendString("2-BacK ");
						}
						else if (Choice2 == '2')
						{
							break;
						}
						else if (Choice2 == '3')
						{
							LCD_voidsendCommand(LCD_CLR_DISPLAY);
							LED_voidOff(&GLED1);
							LED_voidOff(&GLED2);
							USART_voidSendString("LIGHT OFF\n\r");
							LCD_voidSendString("LIGHT OFF");
							LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
							LCD_voidSendString("2-BacK ");
						}
					}
					LCD_voidsendCommand(LCD_CLR_DISPLAY);
					USART_voidSendString("1-DOOR CONTROL\n\r");
					LCD_voidSendString((u8 *)"1-DOOR CONTROL");
					LCD_voidSetPosition(LCD_ROW_2,LCD_COL_1);
					USART_voidSendString("2-LIGHT CONTROL\n\r");
					LCD_voidSendString((u8 *)"2-LED CONTROL");
				}
			}
		}
	}
}
void APP_voidStart(void)
{
	while(1)
	{
		SmartHome();
	}
}

