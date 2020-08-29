#ifndef _MYTYPE_H_
#define _MYTYPE_H_

#include "BS66F360.h"

#ifdef   	_GLOBALS_
#define  	EXT
#else
#define  	EXT  extern
#endif

typedef  unsigned char  uchar;  
typedef  unsigned int   uint;
typedef  unsigned long  ulong;






   
#define C3                  _pa7   //LED控制
#define C2                  _pa6   //数码管2控制          
#define C1                  _pa5   //数码管1控制
#define pe                  _pe    //数码管
#define led_c               _pd7   //温度符号
#define led_warm_A          _pe0   //风暖Aled灯
#define led_warm_B          _pe1   //风暖Bled灯
#define led_blowing         _pe2   //吹风led灯
#define led_ventilate       _pe3   //换气led灯
#define led_power           _pe6   //电源led灯
#define led_light           _pe7   //照明led灯
#define buzzer              _pd1   //蜂鸣器
#define key_warm_A          _pd2   //风暖Aled灯
#define key_warm_B          _pd3   //风暖Bled灯
#define key_blowing         _pd4   //吹风led灯
#define key_ventilate       _pd5   //换气led灯
#define key_light           _pd6   //照明led灯
//开启标志位    
#define  power                _flag2._bits_8._b0    //按键标志位，1使能，0解除
#define  warm_A               _flag2._bits_8._b1    //按键标志位，1使能，0解除
#define  warm_B               _flag2._bits_8._b2   
#define  light                _flag2._bits_8._b3  
#define  blowing              _flag2._bits_8._b4  
#define  ventilate            _flag2._bits_8._b5
#define  warn                 _flag2._bits_8._b6
#define  buf                  _flag2._bits_8._b7

#define  digital_half         _flag1._bits_8._b0    //半亮标志位
#define  buzzer_flag          _flag1._bits_8._b1    //蜂鸣器标志位
#define  protect_flag         _flag1._bits_8._b2    //过热保护标志位
#define  protect              _flag1._bits_8._b3    //过热保护开启标志位
#define  night_flag           _flag1._bits_8._b4    //夜间标志位
#define  red_flag             _flag1._bits_8._b5    //红外线标志位
#define  night_light_flag     _flag1._bits_8._b6    //夜灯标志位
#define  night                _flag1._bits_8._b7    //夜灯开启标志位


#define  order_start          _flag0._bits_8._b0   //接收命令标志位
#define  time_start           _flag0._bits_8._b1   //接收时间标志位
#define  warm_ventilate       _flag0._bits_8._b2   //取暖关闭自动开启换气标志位
#define  warm_ventilate_flag  _flag0._bits_8._b3   //自动开启换气标志位
#define  warm_last            _flag0._bits_8._b4   
#define  units_flag           _flag0._bits_8._b5 
#define  link_flag            _flag0._bits_8._b7 


 typedef struct 
{   // 定义结构体
    volatile uchar _b0 : 1;
    volatile uchar _b1 : 1;
    volatile uchar _b2 : 1;
    volatile uchar _b3 : 1;
    volatile uchar _b4 : 1;
    volatile uchar _b5 : 1;
    volatile uchar _b6 : 1;
    volatile uchar _b7 : 1;
}bits;

typedef union 
{ // 定义联合体
   volatile  bits   _bits_8; // 结构体的使用
   volatile  uchar  byte;
}bytes;
 
DEFINE_SFR(bytes,_flag0,0x480);
DEFINE_SFR(bytes,_flag1,0x481);
DEFINE_SFR(bytes,_flag2,0x482);
   







#endif
