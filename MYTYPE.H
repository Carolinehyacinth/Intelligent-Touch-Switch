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






   
#define C3                  _pa7   //LED����
#define C2                  _pa6   //�����2����          
#define C1                  _pa5   //�����1����
#define pe                  _pe    //�����
#define led_c               _pd7   //�¶ȷ���
#define led_warm_A          _pe0   //��ůAled��
#define led_warm_B          _pe1   //��ůBled��
#define led_blowing         _pe2   //����led��
#define led_ventilate       _pe3   //����led��
#define led_power           _pe6   //��Դled��
#define led_light           _pe7   //����led��
#define buzzer              _pd1   //������
#define key_warm_A          _pd2   //��ůAled��
#define key_warm_B          _pd3   //��ůBled��
#define key_blowing         _pd4   //����led��
#define key_ventilate       _pd5   //����led��
#define key_light           _pd6   //����led��
//������־λ    
#define  power                _flag2._bits_8._b0    //������־λ��1ʹ�ܣ�0���
#define  warm_A               _flag2._bits_8._b1    //������־λ��1ʹ�ܣ�0���
#define  warm_B               _flag2._bits_8._b2   
#define  light                _flag2._bits_8._b3  
#define  blowing              _flag2._bits_8._b4  
#define  ventilate            _flag2._bits_8._b5
#define  warn                 _flag2._bits_8._b6
#define  buf                  _flag2._bits_8._b7

#define  digital_half         _flag1._bits_8._b0    //������־λ
#define  buzzer_flag          _flag1._bits_8._b1    //��������־λ
#define  protect_flag         _flag1._bits_8._b2    //���ȱ�����־λ
#define  protect              _flag1._bits_8._b3    //���ȱ���������־λ
#define  night_flag           _flag1._bits_8._b4    //ҹ���־λ
#define  red_flag             _flag1._bits_8._b5    //�����߱�־λ
#define  night_light_flag     _flag1._bits_8._b6    //ҹ�Ʊ�־λ
#define  night                _flag1._bits_8._b7    //ҹ�ƿ�����־λ


#define  order_start          _flag0._bits_8._b0   //���������־λ
#define  time_start           _flag0._bits_8._b1   //����ʱ���־λ
#define  warm_ventilate       _flag0._bits_8._b2   //ȡů�ر��Զ�����������־λ
#define  warm_ventilate_flag  _flag0._bits_8._b3   //�Զ�����������־λ
#define  warm_last            _flag0._bits_8._b4   
#define  units_flag           _flag0._bits_8._b5 
#define  link_flag            _flag0._bits_8._b7 


 typedef struct 
{   // ����ṹ��
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
{ // ����������
   volatile  bits   _bits_8; // �ṹ���ʹ��
   volatile  uchar  byte;
}bytes;
 
DEFINE_SFR(bytes,_flag0,0x480);
DEFINE_SFR(bytes,_flag1,0x481);
DEFINE_SFR(bytes,_flag2,0x482);
   







#endif