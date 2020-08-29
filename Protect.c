#include "MYTYPE.H"
#include "PROTECT.H"
#include "UART.H"

extern uint time;//接收到的时间
extern uchar tem;
extern uchar str[2];
uchar buzzer_num;
uchar protect_num,protect_num_show,protect_num_show_last;
uchar warn_cnt_1,warn_cnt_2,protect_cnt_1,protect_cnt_2;
uchar warm_ventilate_show;//定时
uchar warm_ventilate_cnt1,warm_ventilate_cnt2;

void buzzer_on(void)    //蜂鸣器
{
	if(buzzer_flag)
	{
		buzzer = 1;
		buzzer_num ++;
	}
	else 
	{
		buzzer = 0;
	}
	if(buzzer_num == 50)
	{
		buzzer_flag = 0;
		buzzer_num = 0;
	}
}
void warn_up(void)//警报开启标志位控制
{
	if(buf == 0)
	{
		warn_cnt_1 = 0;
	    warn_cnt_2 = 0;
	}
	else
	{
		warn_cnt_1++;
	}
	if(warn_cnt_1 >= 50)
	{
		warn_cnt_1 = 0;
		warn_cnt_2++;
	}
	if(warn_cnt_2 > 6)
	{
		if(warn == 0) Uart_sendchars("1a55b1",6);
		warn = 1;
	}
}
void warn_buzzer(void)    //警报蜂鸣器控制
{
	if (warn == 1)  
	{
		buzzer_flag = 1;	
	}
}
void protect_up(void)//开启过热保护标志位
{
	if(warm_A == 1 || warm_B == 1)
	{
		protect_cnt_1++;
	}
	if(protect_cnt_1 > 100)
	{ 
		protect_cnt_2++;
		protect_cnt_1 = 0;
	}
	if((warm_A == 0 && warm_B == 0)|| power == 0) 
	{
	  if(protect == 1)
	  {
		if(protect_cnt_2 > 15)
		{
			protect_flag = 1;
			power = 1;
		    blowing = 1;
			link_flag = 1;
		}
	  }
		protect_cnt_1 = 0;
		protect_cnt_2 = 0;
		
	}
}
void protection(void)    //过热保护
{	
	if(protect_flag == 1)
	{
		power = 1;
		blowing = 1;
		warm_A = 0;
		warm_B = 0;
		light = 0;
		protect_num ++;
	}
	if(protect_num == 133)
	{
		protect_num = 0;
		protect_num_show --;
		inttochar(protect_num_show);
	    Uart_sendchars("1e",2);
	    Uart_sendchars( str,2);
	    Uart_sendchars("f1",2);		
	}
	if(protect_num_show == 0)
	{
	    protect_flag = 0;
		protect_num = 0;
		protect_num_show = 50;
		blowing = 0;
		power = 0;
		Uart_sendchars("1c",2);
	    inttochar(tem);
	    Uart_sendchars(str,2);
	    Uart_sendchars("d1",2);
		link_flag = 1;
	}
	else if(protect_num_show == 10)
	{
		buzzer_flag = 1;
	}
}
void ventilate_auto_up(void)//取暖关闭自动开启换气
{ 
    if(((warm_A == 0 && warm_B == 0)||power == 0) && warm_last == 1) 
	{	 
	    if(warm_ventilate == 1)
	    {
	    	warm_ventilate_flag = 1;
	    	ventilate = 1;
	    	power = 1;
	    	link_flag = 1;
	    	warm_ventilate_show = time;
	    }
	}
	if(warm_A == 1 || warm_B == 1)
	{
		warm_last = 1;
	}
	else
	{
		warm_last = 0;
	}
}
void ventilate_auto(void)//开启换气时间
{
	if(warm_ventilate_flag == 1)
	{
		power = 1;
		ventilate = 1;
		light = 0;
		warm_A = 0;
		warm_B = 0;
		warm_ventilate_cnt1 ++;
		if(warm_ventilate_cnt1 > 250)
	    {
    	    warm_ventilate_cnt1 = 0;
	    	warm_ventilate_cnt2++;
	    }
	    if(warm_ventilate_cnt2 > 3)
	    {
	        warm_ventilate_cnt2 = 0; 
	    	warm_ventilate_show--;
	    }
	    if(warm_ventilate_show == 0)
	    {
	    	warm_ventilate_flag = 0;
	    	warm_ventilate_cnt1 = 0;
	    	warm_ventilate_cnt2 = 0;
	    	ventilate = 0;
	    	power = 0;
	    	link_flag = 1;
	    }
	    _clrwdt();
	}
}
