#ifndef _UART_H_
#define _UART_H_
#include "MYTYPE.H"

void Uart_sendchar(uchar datas);    //���͵�������  
void Uart_sendchars(volatile uchar *senddata,uchar length);    //���Ͷ������
void send_datas(void);//��������
DEFINE_ISR(Uart_Rev,0x10);    //uart�ж�:��������
void inttochar(int num);//int����תΪ�ַ���

#endif