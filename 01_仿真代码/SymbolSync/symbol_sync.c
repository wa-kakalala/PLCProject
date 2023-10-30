#include "type.h"
u16       index_count_symbol    = 0         ;
u16       now_head_index_symbol = 0         ;
u16       now_tail_index_symbol = WIN_LEN-1 ;

POINT_TYPE R_SEQUENCE[WIN_LEN] = { 0 }      ;   // 接收到的序列 
POINT_TYPE P_SEQUENCE[WIN_LEN] = { 0 }      ;   // 本地存储的P序列 
u32        Ep                  =   100      ;   // 可以一开始就计算出来的 
  
u16        index               = 0          ; 
u16        symbol_judg_count   = 0          ;    

float32    symbol_judg         = 0.0        ;  

u8         SYMBOL_THRS         = 0.6;   
float32    SYMBOL_JUGE_THRS    = 8         ;   // 判决门限  
u32        Pn                  = 0;
u32        Er                  = 0;
int        now_index           = 0;

u8 symbol_sync(POINT_TYPE point){
	if( index_count_symbol < WIN_LEN ){
		R_SEQUENCE[ index_count_symbol ] = point;
		Er += point * point;
		index_count_symbol ++;
	}else {
		Er -= R_SEQUENCE[now_head_index_symbol]*R_SEQUENCE[now_head_index_symbol];
		Er += point*point;	
		R_SEQUENCE[now_head_index_symbol] = point;
	}
	
	now_head_index_symbol = (now_head_index_symbol + 1) & 0x3ff;
	
	if( index_count_symbol < WIN_LEN ) return 0;
	for(index = 0; index < WIN_LEN;index++){
		now_index = (now_head_index_symbol+index) & 0x3ff;
		Pn += R_SEQUENCE[now_index] * P_SEQUENCE[index] ; 
	}
	
	symbol_judg =  Pn*Pn / (Ep * Er); 
	
	if( symbol_judg > SYMBOL_THRS ) symbol_judg_count++;
	
	if( symbol_judg_count >= SYMBOL_JUGE_THRS ){
		symbol_judg_count = 0;
		return 1;
	}else{
		return 0;
	}
	
	
}
