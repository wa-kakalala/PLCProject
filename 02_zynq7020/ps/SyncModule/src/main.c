#include <stdio.h>
#include "type.h"
#include "simulated_data.h"
#include "private_timer_init.h"
#include "platform.h"
#include "xil_types.h"
#include "xtime_l.h"
// xil_types.h have done this:
// typedef uint8_t u8;
// typedef uint16_t u16;
// typedef uint32_t u32;

//#include <time.h>

void sys_init()
{
	if( timer_init() != XST_SUCCESS ){
		printf("timer init failed !!!\r\n");
	}else{
		printf("timer init successful !!!\r\n");
	}

	//定时器中断初始化
	timer_intr_init();
}

int main(void)
{

    printf("Hello World\n");
    printf("Successfully run Hello World application\n");

    XTime tBegin, tEnd;
    int i = 0;
    u32 index_new = WIN_LEN-1;
    u32 index_old = 0;
    u32 symbol_index = 0;
    u32 symbol_count = 0;

    for(i= 0;i<WIN_LEN;i++){
    	frame_sync(RX_DATA[index_old++],RX_DATA[index_new++]);
    }
    // 8倍采样
    for( i= 0; i<127; i++){
		symbol_sync(RX_DATA[symbol_index]);
		symbol_index += 8;
    }

    //u32 begin_instret, end_instret, instret_vector,instret;
    //u32 begin_cycle,   end_cycle,   cycle_vector,cycle;

    // begin_instret =  __get_rv_instret();
    // begin_cycle   =  __get_rv_cycle();

    uint32_t start =0 ;
    uint32_t end = 0;
    sys_init();
    timer_start();
    start = timer_gettime();
    XTime_GetTime(&tBegin);
    while( !frame_sync(RX_DATA[index_old++],RX_DATA[index_new++]));
    start = timer_gettime();

    for(symbol_count=0; symbol_count<128*8; symbol_count++ ){
    	symbol_sync(RX_DATA[symbol_index]);
    	symbol_index += 8;
    }


    //end_instret = __get_rv_instret();
	//end_cycle   = __get_rv_cycle();


	//instret_vector = end_instret - begin_instret;
	//cycle_vector   = end_cycle - begin_cycle;
    //printf("instret_vector is %d, cycle_vector is %d\n",instret_vector,cycle_vector);

    XTime_GetTime(&tEnd);
    end = timer_gettime();
    printf("frame + symbol sync using time: %lu us\r\n",end-start);
    printf("- Counts per second: %d\r\n", COUNTS_PER_SECOND);
    printf("- Cycles: %llu\r\n", tEnd-tBegin);

    return 0;
}
