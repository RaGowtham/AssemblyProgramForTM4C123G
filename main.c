
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
extern void Timer0IntHandler(void);

#define RCGC_GPIOF  	((unsigned int *) 0x400FE608)
#define GPIOF_DATA  	((unsigned int *) 0x40025000)
#define GPIOF_DIR      *((unsigned int *) 0x40025400)
#define GPIOF_DEN  	   *((unsigned int *) 0x4002551C)
#define RCGC_TIMER0  	((unsigned int *) 0x400FE604)
#define GPTMCTL_TIMER0  ((unsigned int *) 0x4003000C)
#define GPTMCFG_TIMER0  ((unsigned int *) 0x40030000)
#define GPTMAMR_TIMER0  ((unsigned int *) 0x40030004)
#define GPTMAILR_TIMER0 ((unsigned int *) 0x40030028)
#define GPTMICR_TIMER0  ((unsigned int *) 0x40030024)
#define GPTMIMR_TIMER0  ((unsigned int *) 0x40030018)
#define GPTMSEN_TIMER0A *((unsigned int *) 0xE000E100)
void toggle(void)
{

	if((*(GPIOF_DATA + 0x0E)) == 2)
	{
		*(GPIOF_DATA + 0x0E) = 4;
	}
	else if((*(GPIOF_DATA + 0x0E)) == 4)
	{
		*(GPIOF_DATA + 0x0E) = 8;
	}
	else
	{
		*(GPIOF_DATA + 0x0E) = 2;
	}
}


int main()
{

	//Enablinng PORTF
	*(RCGC_GPIOF) = 0x20;
	//PIN 1,2,3 as a output
	GPIOF_DIR = 0X0E;
	//PIN 1,2,3 as a digital pin
	GPIOF_DEN = 0X0E;


	*(RCGC_TIMER0) 		= 0x01;
	*(GPTMCTL_TIMER0)	= 0x00;
	*(GPTMCFG_TIMER0)	= 0x00;
	*(GPTMAMR_TIMER0)   = 0x02;
	*(GPTMAILR_TIMER0)	= (SysCtlClockGet() / 10);
	*(GPTMCTL_TIMER0)	= 0x01;


	GPTMSEN_TIMER0A |= (1 << 19);
	*(GPTMIMR_TIMER0) = 0x01;
	*(GPIOF_DATA + 0x0E) = 0X04;
	while(1);
}
