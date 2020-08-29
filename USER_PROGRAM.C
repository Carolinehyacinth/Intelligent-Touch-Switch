#include    "USER_PROGRAM.H"
#define   	_GLOBALS_
#include	"MYTYPE.H"
#include	"KEY.h"
#include	"UART.h"
#include	"DISPLAY.h"
#include	"AD.h"
#include	"PROTECT.h"

       
extern uint time;//���յ���ʱ��
extern uint inter_num;    //�жϴ���
extern volatile uchar KeyHold,KeyHold2;
extern uchar protect_num_show;
extern uchar light_num_time;
extern uint send_cnt_1;
extern uchar i;


void display(void);    //��ʾ
void touch_key(void);    //���ذ�ť
void show_tem(void);    //�¶�ת��
void buzzer_on(void);    //������
void digital_check(void);    //����ܼ��
void number_choice(void);    //�������ʾѡ��
void protection(void);    //���ȱ���
void night_light(void);    //ҹ������
void warn_buzzer(void);    //����
void send_datas(void);    //��������
void ventilate_auto(void);    //�Զ�����
void ventilate_auto_up(void);    //ȡů�ر��Զ���������
void warn_up(void);    //��������
void protect_up(void);    //���ȱ�������


void USER_PROGRAM_INITIAL()  //��ʼ��          
{
	//GPIO INIT
	//_pa = 0xe2; _pac = 0x02; _papu = 0x02;    //pa7:C3;pa6:C2;pa5:c1
	//_pb = 0x00; _pbc = 0x00; _pbpu = 0x00;
	_pa = 0xe2; _pac = 0x16; _papu = 0x02;    //pa7:C3;pa6:C2;pa5:c1��PA4����������ߵ�ƽ���ʾ�����Ѿ����ӣ�PA1:��������
	//pa3:�������룬������������ǰ�����͸����ţ����ͽ���������
	_pb = 0x0c; _pbc = 0x18; _pbpu = 0x00;//PB3Ϊ��������ˣ�����������PB7��Ϊ0ʱ����ģ��Ĵ���
	_pc = 0x00; _pcc = 0xfc; _pcpu = 0x00;
	_pd = 0x00; _pdc = 0x00; 
	_pe = 0x20; _pec = 0x20;     //����ܺ�LED
	_pf = 0x00; _pfc = 0x00; _pfpu = 0x00;
    _pe5 = 1; _pec5 = 1;_pepu5 = 1;
	//AD��ʼ��
	_pbs0 = 0x5f;    //ȷ�����Ź���	
	_adcr1 = 0x03;    //adcr1��ѡ��A/Dת��ʱ��
	_adcen = 1;     //adcen��adcת����ʹ��
	_adrfs = 1;    //1��A/D ת�����ݸ�ʽ ��SADOH=D[11:8]; SADOL=D[7:0]		
	             //0��A/D ת�����ݸ�ʽ ��SADOH=D[11:4]; SADOL=D[3:0]
	_acs3 = 0; _acs2 = 0; _acs1 = 0; _acs0 = 1;	    //A/D�ӿ�ѡ��
    _emi = 1;    //���жϿ���
    power = 0;       warm_A = 0;         warm_B = 0;            
    light = 0;       blowing = 0;        ventilate = 0;          
    warn = 0;        buf = 0;                
    digital_half = 0;          buzzer_flag  = 0;          protect_flag = 0;    
    night_flag = 0;            red_flag = 0;              night_light_flag = 0; 
    warm_ventilate_flag = 0;   link_flag = 0;
    night = 0;                 protect = 0;               warm_ventilate = 0;     
    order_start = 0;           time_start = 0;            
    
    //UART��ʼ��
    _ucr1 = 0x80;    //UART����ʹ��
    _ucr2 = 0xc4;    //����ʹ�ܣ�����ʹ�ܣ������ʷ��������٣������ж�ʹ��
    _brg = 25;    //9600,16M/9600/64-1=25
    _ure = 1;    //�����ж�ʹ��
    inter_num = 0;
    protect_num_show = 50;  light_num_time = 10;
    i = 0;
    //inter = 0;
    time = 5;
    warm_last = 0;
    send_cnt_1 = 0;
    digital_check();
    
}
void USER_PROGRAM()      //��ѭ��              
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
    warn_up();//�ж��Ƿ�������
    protect_up();//�ж��Ƿ������ȱ���
    ventilate_auto_up();//�ж��Ƿ���Ҫ��������
    warn_buzzer();//��������������
    if(night == 1)//�ж��Ƿ���Ҫ��������   
    {
    	night_light(); 
    } 
    if(protect == 1) //���ȱ�����ʱ
    {
    	protection();
    }
    ventilate_auto();//������ʱ
    number_choice();//�������ʾѡ��
    display();//����ܺ�led�Ƶ���ʾ
    send_datas();//��������
    buzzer_on(); //������  
    _clrwdt();    
}