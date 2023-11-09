#include "type.h"
#include "simulated_data.h"
u16       index_count_symbol    = 0         ;
u16       now_head_index_symbol = 0         ;
u16       now_tail_index_symbol = WIN_LEN-1 ;

POINT_TYPE R_SEQUENCE[WIN_LEN] = { 0 }      ;   // 接收到的序列 
// POINT_TYPE P_SEQUENCE[WIN_LEN] = { 0 }      ;   // 本地存储的P序列
uint32_t        Ep                  =   66365394 / 8 ;   // 可以一开始就计算出来的
  
u16        index_              = 0          ;   // index_ 的原因是 index是一个内建函数
u16        symbol_judg_count   = 0          ;    

float32    symbol_judg         = 0.0        ;  

u8         SYMBOL_THRS         = 0.6;   
float32    SYMBOL_JUGE_THRS    = 8          ;   // 判决门限
uint32_t        Pn             = 0;
uint32_t        Er             = 0;
int        now_index           = 0;

u8 symbol_sync(POINT_TYPE point){
	if( index_count_symbol < WIN_LEN/8 ){
		R_SEQUENCE[ index_count_symbol ] = point;
		Er += point * point;
		index_count_symbol ++;
	}else {
		Er -= R_SEQUENCE[now_head_index_symbol]*R_SEQUENCE[now_head_index_symbol];
		Er += point*point;	
		R_SEQUENCE[now_head_index_symbol] = point;
	}
	
	now_head_index_symbol = (now_head_index_symbol + 1) & 0x3ff;
	
	if( index_count_symbol < WIN_LEN / 8 ) return 0;
	Pn = 0;
	for(index_ = 0; index_ < WIN_LEN / 8 ;index_++){
		now_index = (now_head_index_symbol+index_) & 0x3ff;
		Pn += R_SEQUENCE[now_index] * P_SEQUENCE[index_] ;
	}
	


	symbol_judg =  (float32)(Pn*Pn)  / (Ep * Er);
	//printf("symbol_jude:%f\r\n",symbol_judg);


	
	if( symbol_judg > SYMBOL_THRS ) symbol_judg_count++;
	
	if( symbol_judg_count >= SYMBOL_JUGE_THRS ){
		symbol_judg_count = 0;
		return 1;
	}else{
		return 0;
	}
	
	
}
