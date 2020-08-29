#include    "USER_PROGRAM.H"
#define   	_GLOBALS_
#include	"MYTYPE.H"
#include	"KEY.h"
#include	"UART.h"
#include	"DISPLAY.h"
#include	"AD.h"
#include	"PROTECT.h"

       
extern uint time;//接收到的时间
extern uint inter_num;    //中断次数
extern volatile uchar KeyHold,KeyHold2;
extern uchar protect_num_show;
extern uchar light_num_time;
extern uint send_cnt_1;
extern uchar i;


void display(void);    //显示
void touch_key(void);    //触控按钮
void show_tem(void);    //温度转换
void buzzer_on(void);    //蜂鸣器
void digital_check(void);    //数码管检测
void number_choice(void);    //数码管显示选择
void protection(void);    //过热保护
void night_light(void);    //夜间照明
void warn_buzzer(void);    //警报
void send_datas(void);    //发送数据
void ventilate_auto(void);    //自动换气
void ventilate_auto_up(void);    //取暖关闭自动换气开启
void warn_up(void);    //警报开启
void protect_up(void);    //过热保护开启


void USER_PROGRAM_INITIAL()  //初始化          
{
	//GPIO INIT
	//_pa = 0xe2; _pac = 0x02; _papu = 0x02;    //pa7:C3;pa6:C2;pa5:c1
	//_pb = 0x00; _pbc = 0x00; _pbpu = 0x00;
	_pa = 0xe2; _pac = 0x16; _papu = 0x02;    //pa7:C3;pa6:C2;pa5:c1，PA4：蓝牙输出高电平则表示蓝牙已经连接；PA1:红外输入
	//pa3:蓝牙输入，蓝牙发送数据前，拉低该引脚，发送结束后，拉高
	_pb = 0x0c; _pbc = 0x18; _pbpu = 0x00;//PB3为数据输出端，连接蓝牙，PB7：为0时唤醒模块的串口
	_pc = 0x00; _pcc = 0xfc; _pcpu = 0x00;
	_pd = 0x00; _pdc = 0x00; 
	_pe = 0x20; _pec = 0x20;     //数码管和LED
	_pf = 0x00; _pfc = 0x00; _pfpu = 0x00;
    _pe5 = 1; _pec5 = 1;_pepu5 = 1;
	//AD初始化
	_pbs0 = 0x5f;    //确认引脚功能	
	_adcr1 = 0x03;    //adcr1：选择A/D转换时钟
	_adcen = 1;     //adcen：adc转换器使能
	_adrfs = 1;    //1：A/D 转换数据格式 →SADOH=D[11:8]; SADOL=D[7:0]		
	             //0：A/D 转换数据格式 →SADOH=D[11:4]; SADOL=D[3:0]
	_acs3 = 0; _acs2 = 0; _acs1 = 0; _acs0 = 1;	    //A/D接口选择
    _emi = 1;    //总中断开关
    power = 0;       warm_A = 0;         warm_B = 0;            
    light = 0;       blowing = 0;        ventilate = 0;          
    warn = 0;        buf = 0;                
    digital_half = 0;          buzzer_flag  = 0;          protect_flag = 0;    
    night_flag = 0;            red_flag = 0;              night_light_flag = 0; 
    warm_ventilate_flag = 0;   link_flag = 0;
    night = 0;                 protect = 0;               warm_ventilate = 0;     
    order_start = 0;           time_start = 0;            
    
    //UART初始化
    _ucr1 = 0x80;    //UART功能使能
    _ucr2 = 0xc4;    //发送使能，接收使能，波特率发生器低速，接收中断使能
    _brg = 25;    //9600,16M/9600/64-1=25
    _ure = 1;    //串口中断使能
    inter_num = 0;
    protect_num_show = 50;  light_num_time = 10;
    i = 0;
    //inter = 0;
    time = 5;
    warm_last = 0;
    send_cnt_1 = 0;
    digital_check();
    
}
void USER_PROGRAM()      //主循环              
{
    GET_KEY_BITMAP();
    KeyHold = DATA_BUF[0];
    KeyHold2 = DATA_BUF[1];
    show_tem(); 
    if((KeyHold != 0x00)|(KeyHold2 != 0x00))
    {   
    	if(buf == 0) touch_key(); 
    }
    else buf = 0;
    warn_up();//判断是否开启警报
    protect_up();//判断是否开启过热保护
    ventilate_auto_up();//判断是否需要开启换气
    warn_buzzer();//警报蜂鸣器控制
    if(night == 1)//判断是否需要开启照明   
    {
    	night_light(); 
    } 
    if(protect == 1) //过热保护计时
    {
    	protection();
    }
    ventilate_auto();//换气计时
    number_choice();//数码管显示选择
    display();//数码管和led灯的显示
    send_datas();//发送数据
    buzzer_on(); //蜂鸣器  
    _clrwdt();    
}
