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
    u32 index_new = WIN_LEN-1;
    u32 index_old = 0;
    for( i= 0;i<WIN_LEN;i++){
    	 frame_sync(RX_DATA[index_old++],RX_DATA[index_new++]);
    }

    timer_start();
    uint32_t start = timer_gettime();
    printf("%lu\r\n",start);

    while( !frame_sync(RX_DATA[index_old++],RX_DATA[index_new++]) );

    uint32_t end = timer_gettime();
    printf("%lu\r\n",end);






    cleanup_platform();
    return 0;
}
