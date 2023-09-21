#include "type.h"

POINT_TYPE C_win[WIN_LEN] = {0};
POINT_TYPE P_win[WIN_LEN] = {0};

u16        index_count    = 0;
u16        now_head_index = 0;
u16        now_tail_index = WIN_LEN-1;

float32    frame_judg = 0;
u16        frame_judg_count = 0;
u16        frame_judg_threah = FRAME_THRESH;

u8 frame_sync(POINT_TYPE point){
	int index = 0;
	u32 Cn = 0;
	u32 Pn = 0;
	if( index_count <= WIN_LEN ){
		C_win[index_count ++ ] = point;
	}else if(index_count <= WIN_LEN * 2 ){
		P_win[index_count ++ ] = point;
	}else{
		C_win[now_head_index] = point;
		P_win[now_head_index] = point;
		
		now_head_index = (now_head_index + 1) % WIN_LEN;	
	}
	
	if( index_count < WIN_LEN * 2 ) return 0;
	
	u16 now_index = 0; 
	for(index = 0; index < WIN_LEN;index++){
		now_index = (now_head_index+now_index) % WIN_LEN;
		Cn += C_win[now_index] * P_win[now_index];
		Pn += P_win[now_index] * P_win[now_index]; 
	}
	
	frame_judg = abs(Cn) / Pn;
	if( frame_judg > FRAME_THRESH  ) frame_judg_count ++;
	if( frame_judg < FRAME_THRESH  ) frame_judg_count = 0;
	
	if( frame_judg_count > WIN_LEN* 2 ) return 1;
	else return 0;
}
