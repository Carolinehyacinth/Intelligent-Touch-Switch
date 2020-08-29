#define   	_GLOBALS_
#include "MYTYPE.H"
#include "UART.H"
uint time;//���յ���ʱ��
uchar udatas_rec;
uint send_cnt_1;
uchar i;
extern uchar tem;//�¶�
extern uchar tem_last;
uchar data[3];//�����ַ�������
uchar str[2];


void Uart_sendchar(uchar datas)    //���͵�������  
{
	if(_txif)
	{
		_txr_rxr = datas;
		while(!_txif);    //�ȴ����ݴ���TSR
		while(!_tidle);    //�ȴ����ݴ������
	}
}
void Uart_sendchars(volatile uchar *senddata,uchar length)    //���Ͷ������
{
   while(length)
	{
	   Uart_sendchar(*senddata++);
	   length--;	
    }
}
void send_datas(void)//��������
{        
 //��������
   if(link_flag)
  {
      if(send_cnt_1 == 50)
      {
      	  if(power == 1)	 Uart_sendchars("1a11b1",6); 
          if(power == 0)     Uart_sendchars("1a10b1",6);  
      }
      else if(send_cnt_1 == 100) 
      {
      	  if(light == 1)     Uart_sendchars("1a21b1",6);
          if(light == 0)     Uart_sendchars("1a20b1",6); 
      }  
      else if(send_cnt_1 == 150) 
      {
      	  if(blowing == 1)   Uart_sendchars("1a31b1",6);
          if(blowing == 0)   Uart_sendchars("1a30b1",6); 
      }  
      else if(send_cnt_1 == 200) 
      {
      	  if(ventilate == 1) Uart_sendchars("1a41b1",6);
          if(ventilate == 0) Uart_sendchars("1a40b1",6);
      } 
      else if(send_cnt_1 == 250) 
      {
      	  if(warm_A == 1)    Uart_sendchars("1a51b1",6);
          if(warm_A == 0)    Uart_sendchars("1a50b1",6);
      } 
      else if(send_cnt_1 == 300) 
      {
      	  if(warm_B == 1)    Uart_sendchars("1a61b1",6);
          if(warm_B == 0)    Uart_sendchars("1a60b1",6);
      } 
      else if(send_cnt_1 == 350) 
      {
       	  if(protect == 1)   Uart_sendchars("1a71b1",6);
	      if(protect == 0)   Uart_sendchars("1a70b1",6);
      } 
      else if(send_cnt_1 == 400) 
      {
      	  if(night == 1)     Uart_sendchars("1a81b1",6);
	      if(night == 0)     Uart_sendchars("1a80b1",6);
      } 
      else if(send_cnt_1 == 450) 
      {
      	  if(warm_ventilate == 1)     Uart_sendchars("1a91b1",6);
	      if(warm_ventilate == 0)     Uart_sendchars("1a90b1",6);
      } 
      else if(send_cnt_1 == 500)
      {
      	Uart_sendchars("1c",2);
	    inttochar(tem);
	    Uart_sendchars(str,2);
	    Uart_sendchars("d1",2);
      }
      else if(send_cnt_1 == 550) 
      {
      	  if(warn == 1)     Uart_sendchars("1a55b1",6);
	      link_flag=0;
	      send_cnt_1 = 0;
      } 
      send_cnt_1 ++;   
  }
             
   if((tem_last != tem) && (protect_flag == 0))//���ʱ��ı�ͷ�
   {
	    //����	     
	    Uart_sendchars("1c",2);
	    inttochar(tem);
	    Uart_sendchars(str,2);
	    Uart_sendchars("d1",2);
  }  	      
	
}
DEFINE_ISR(Uart_Rev,0x10)    //uart�ж�:��������
{
	if(_rxif)
	{
		udatas_rec = _txr_rxr;
		//��������
		if(udatas_rec == 'a') {order_start = 1;}    
		else if(udatas_rec == 'b'){order_start = 0;}
		else if(udatas_rec == 'c'){time_start = 1;}
		else if(udatas_rec == 'd'){time_start = 0;}
		else if(udatas_rec == 'g'){link_flag = 1;}	
	    if((order_start)||(time_start))
	    {
		   data[i]=udatas_rec;
		   i++;
	    }
	    else if(udatas_rec == 'b')
	    { 
		        if(data[1] == '1' && data[2] == '1'){power = 1;i = 1;}//��Դ
		   else if(data[1] == '1' && data[2] == '0')
		   {
			    power = 0;
			    buzzer_flag = 1;
			    i = 1;
			    link_flag = 1;
		   }
		   else if(data[1] == '2' && data[2] == '1'){light = 1;i = 1;}     //����
		   else if(data[1] == '2' && data[2] == '0'){light = 0;i = 1;}
	 	   else if(data[1] == '3' && data[2] == '1'){blowing = 1;i = 1;}   //����
		   else if(data[1] == '3' && data[2] == '0'){blowing = 0;i = 1;}
		   else if(data[1] == '4' && data[2] == '1'){ventilate = 1;i = 1;} //����
		   else if(data[1] == '4' && data[2] == '0'){ventilate = 0;i = 1;}
		   else if(data[1] == '5' && data[2] == '1'){warm_A = 1;i = 1;}    //��ůA
           else if(data[1] == '5' && data[2] == '0'){warm_A = 0;i = 1;}
           else if(data[1] == '6' && data[2] == '1'){warm_B = 1; i = 1;}   //��ůB
           else if(data[1] == '6' && data[2] == '0'){warm_B = 0;i = 1;}
           else if(data[1] == '7' && data[2] == '1'){protect = 1;} //���ȱ���
           else if(data[1] == '7' && data[2] == '0'){protect = 0;}
           else if(data[1] == '8' && data[2] == '1'){night = 1;}    //����
           else if(data[1] == '8' && data[2] == '0'){night = 0;}
           else if(data[1] == '9' && data[2] == '1'){warm_ventilate = 1;}//ȡů�ر��Զ���������
           else if(data[1] == '9' && data[2] == '0'){warm_ventilate = 0; }  
           else if(data[1] == '5' && data[2] == '4'){warn = 0; } 
           if( i==1 && power) buzzer_flag = 1;
           i=0;
	    }
	    else if(udatas_rec == 'd')//�����յ���Ϊʱ��
	    {
	    	time = 0;
	        for(i=1;i<3;i++)
	        time=time*10+(data[i]-'0');
	        i = 0;	    	
	    }      		
	}
}
void inttochar(int num)//int����תΪ�ַ���
{
	int s=0;
	int j=1;
	if(num>9)
	{
	    while(num){
		s=num%10;
		num=num/10;
		str[j--]=s+'0';
	    }	   
	}
	else {str[0]=0+'0';str[1]=num+'0';}
	
}
