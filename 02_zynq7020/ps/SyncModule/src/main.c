/* ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "private_timer_init.h"
#include "type.h"
#include "simulated_data.h"

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

int main()
{
    init_platform();

    print("\r\nHello World\n\r");
    print("Successfully ran Hello World application\r\n");

    sys_init();

    int i = 0;
    u32 index_new = WIN_LEN;
    u32 index_old = 0;
    u32 symbol_index = 0;
    u32 symbol_count = 0;
    for( i= 0;i<WIN_LEN-1;i++){
    	 frame_sync(RX_DATA[index_old++],RX_DATA[index_new++]);
    }

    // 8倍采样
    for( i= 0;i<WIN_LEN/8 -1 ;i++){
		 symbol_sync(RX_DATA[symbol_index]);
		 symbol_index += 8;
    }

    timer_start();
    uint32_t start = timer_gettime();


    while( !frame_sync(RX_DATA[index_old++],RX_DATA[index_new++]) );

    for(symbol_count=0;symbol_count< 128*8;symbol_count++ ){
    	 symbol_sync(RX_DATA[symbol_index]);
    	 symbol_index += 8;
    }

    uint32_t end = timer_gettime();
    printf("using time: %lu us",end-start);

    cleanup_platform();
    return 0;
}
