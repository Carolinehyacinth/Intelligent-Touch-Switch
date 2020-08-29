#ifndef _UART_H_
#define _UART_H_
#include "MYTYPE.H"

void Uart_sendchar(uchar datas);    //发送单个数据  
void Uart_sendchars(volatile uchar *senddata,uchar length);    //发送多个数据
void send_datas(void);//发送数据
DEFINE_ISR(Uart_Rev,0x10);    //uart中断:接收数据
void inttochar(int num);//int类型转为字符串

#endif