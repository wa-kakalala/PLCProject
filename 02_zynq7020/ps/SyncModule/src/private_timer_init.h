#ifndef _PRIVATE_TIMER_INIT_H_
#define _PRIVATE_TIMER_INIT_H_
#include <stdio.h>
#include "xparameters.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xil_exception.h"

#define TIMER_DEVICE_ID     XPAR_XSCUTIMER_0_DEVICE_ID   //定时器ID
#define INTC_DEVICE_ID      XPAR_SCUGIC_SINGLE_DEVICE_ID //中断ID
#define TIMER_IRPT_INTR     XPAR_SCUTIMER_INTR           //定时器中断ID


//私有定时器的时钟频率 = CPU时钟频率/2 = 333MHz
//定时器装载值   --> 1us
#define TIMER_LOAD_VALUE    332

extern  volatile uint32_t  usec ;
extern  XScuGic Intc;               //中断控制器驱动程序实例
extern  XScuTimer Timer;            //定时器驱动程序实例

int timer_init(void);
void timer_intr_init(void);
void timer_start(void);
uint32_t timer_gettime(void);

#endif

