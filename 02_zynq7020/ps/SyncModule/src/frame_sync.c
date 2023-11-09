#include "type.h"


POINT_TYPE C_win[WIN_LEN] = {0};
POINT_TYPE P_win[WIN_LEN] = {0};
u32 C_win_sum      = 0  ;
u32 P_win_sum      = 0  ;

u16        index_count    = 0;
u16        now_head_index = 0;

float32    frame_judg       = 0;

float32    FRAME_THRESH     = 0.1;
u16        frame_judg_count = 0;
u8         FRAME_JUDG_THRS  = 32; 

u8 frame_sync(POINT_TYPE point_new,POINT_TYPE point_old){
	if( index_count < WIN_LEN ){
		C_win[now_head_index] = point_new * point_old ;
		C_win_sum = C_win_sum + point_new * point_old;
		P_win[now_head_index] = point_old * point_old;
		P_win_sum = P_win_sum + point_old * point_old;
		index_count ++;	
	} else {
		C_win_sum = C_win_sum - C_win[now_head_index];
		P_win_sum = P_win_sum - P_win[now_head_index];
		
		C_win[now_head_index] = point_new * point_old;
		P_win[now_head_index] = point_old * point_old;
	}
	
	now_head_index = (now_head_index + 1) & 0x3ff;
	
	if( index_count < WIN_LEN ) return 0;
	
	frame_judg = C_win_sum / P_win_sum;
	//printf("frame_jude:%f\r\n",frame_judg);
	
	if( frame_judg > FRAME_THRESH  ) frame_judg_count ++;
	if( frame_judg < FRAME_THRESH  ) frame_judg_count = 0;
	
	if( frame_judg_count >= FRAME_JUDG_THRS ){
		frame_judg_count = 0;
		return 1;
	}else return 0;
}
