#ifndef _PRIVATE_TIMER_INIT_H_
#define _PRIVATE_TIMER_INIT_H_
#include <stdio.h>
#include "xparameters.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xil_exception.h"

#define TIMER_DEVICE_ID     XPAR_XSCUTIMER_0_DEVICE_ID   //��ʱ��ID
#define INTC_DEVICE_ID      XPAR_SCUGIC_SINGLE_DEVICE_ID //�ж�ID
#define TIMER_IRPT_INTR     XPAR_SCUTIMER_INTR           //��ʱ���ж�ID


//˽�ж�ʱ����ʱ��Ƶ�� = CPUʱ��Ƶ��/2 = 333MHz
//��ʱ��װ��ֵ   --> 1us
#define TIMER_LOAD_VALUE    332

extern  volatile uint32_t  usec ;
extern  XScuGic Intc;               //�жϿ�������������ʵ��
extern  XScuTimer Timer;            //��ʱ����������ʵ��

int timer_init(void);
void timer_intr_init(void);
void timer_start(void);
uint32_t timer_gettime(void);

#endif

