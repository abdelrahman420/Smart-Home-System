/*
Author:Abdelrahman Mostafa
Date :3/8/2023
SWC  : DIO
Version : 1.0
*/
#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H


#define PORTA_REG   *((volatile u8*)0x3B)    
#define PORTB_REG   *((volatile u8*)0x38)
#define PORTC_REG   *((volatile u8*)0x35)
#define PORTD_REG   *((volatile u8*)0x32)

#define PINA_REG    *((volatile u8*)0x39)
#define PINB_REG    *((volatile u8*)0x36)
#define PINC_REG    *((volatile u8*)0x33)
#define PIND_REG    *((volatile u8*)0x30)

#define DDRA_REG    *((volatile u8*)0x3A)
#define DDRB_REG    *((volatile u8*)0x37)
#define DDRC_REG    *((volatile u8*)0x34)
#define DDRD_REG    *((volatile u8*)0x31)


#endif