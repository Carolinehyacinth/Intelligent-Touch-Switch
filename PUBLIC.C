#include "PUBLIC.H"
#include "BS66F360.H"
#include "MYTYPE.H"



void System_Init()
{
	//GPIO INIT
	_pac=0x00;
	_papu=0x00;
	_pa=0x00;
	_pbc=0x00;
	_pbpu=0x00;
	_pb=0x00;
	_pcc=0x00;
	_pcpu=0x00;
	_pc=0x00;
	_pdc=0xfe;
	_pd=0xfe;
	_pec=0x0f;
	_pe=0x0f;
	_pfc=0x00;
	_pfpu=0x00;
	_pf=0x00;
	_pe5=1;
	_pec5=1;
	_pepu5=1;
	//TIMER INIT
	//ctm0
	_ctm0c0=0x38;//f=fh/64  _ctm0on=0;  4us
	_ctm0c1=0xc1;
	_ctm0al=1000%256;//1us*500
	_ctm0ah=1000>>8;
	_mf0e=1;
	_ctm0ae=1;
	//ctm1  蜂鸣器驱动频率中断
	_ctm1c0=0x28;//f=fh/16   _ctm1on=1;
	_ctm1c1=0xc1; 
//	_ctm1al=500%256;//1us*500
//	_ctm1ah=500>>8;
	_ctm1al=125;//1us*250
	_ctm1ah=0;
	_mf1e=1;
	_ctm1ae=1;
	_emi=1;//开总中断
	//WatchDog_INIT
	_wdtc=0xaf;
	_rstc=0x55;
	//系统时钟配置
	_hircc=0x09;
	_scc=0x03;
	//ADCInit
	_pbs0=0x0c;
	_adcen=1;//adc转换器使能
	_adrfs=1;//1：A/D 转换数据格式 →SADOH=D[11:8]; SADOL=D[7:0]
			//0：A/D 转换数据格式 →SADOH=D[11:4]; SADOL=D[3:0]
	_acs2=0;	//通道选择
	_acs1=0;
	_acs0=1;//选择通道1
	_adcr1 = 0x05;
	
	GCC_CLRWDT();
	GCC_CLRWDT1();
	GCC_CLRWDT2();
	
	
	
	
}

////获取AD值  
//void ADC_GetData()
//{
//	_start=0;	//执行AD转换
//	_start=1;
//	_start=0;				//ADC
//	while(_adbz);
//	addata=((u16)_adrh<<8)+_adrl;
//	sumtemp+=addata;
//	if(++tempchara==128)
//	{
//		tempchara=0;
//		tempint_add=sumtemp/128;
//		sumtemp=0;
//		if(tempint_add>=3997)
//		{
//			tempint_add
//		}
//		if(tempint_add>=3922) 
//		{
//			realtemperture = 0;
//		}
//		else if(tempint_add<=85) 
//		{
//			realtemperture = 230;//边界检查
//		}
//		else
//		{
//			//查表
//			for(i=0;i<320;i++)
//			{
//				if(tempint_add>TEMPTABLE[i]) 
//				{
//					realtemperture = i-20;
//					break;
//				}
//			}
//		}
//		
//	}
//	/*tempint_max=addata;
//	tempint_min=addata;
//	tempint_add=tempint_max+tempint_min;
//	for(tempchara=0;tempchara<10;tempchara++)
//	{
//		tempinta=addata;
//		tempint_add+=tempinta;
//		if(tempinta>tempint_max) 
//		{
//			tempint_max=tempinta;
//		}
//		if(tempinta<tempint_min) 
//		{
//			tempint_min=tempinta;
//		}	
//	}
//	tempint_add-=tempint_max;
//	tempint_add-=tempint_min;
//	tempint_add/=10;*/
//	
//}
//void ADC_GetData()
//{
////	u8 tempchara=0;
////	u16 tempint_add,tempinta,tempint_max,tempint_min,i;
////	u16 addata;
//	_start=0;	//执行AD转换
//	_start=1;
//	_start=0;				//ADC
//	while(_adbz);
//	addata=((u16)_adrh<<8)+_adrl;
//	tempint_max=addata;
//	tempint_min=addata;
//	tempint_add=tempint_max+tempint_min;
//	for(tempchara=0;tempchara<10;tempchara++)
//	{
//		tempinta=addata;
//		tempint_add+=tempinta;
//		if(tempinta>tempint_max) 
//		{
//			tempint_max=tempinta;
//		}
//		if(tempinta<tempint_min) 
//		{
//			tempint_min=tempinta;
//		}	
//	}
//	tempint_add-=tempint_max;
//	tempint_add-=tempint_min;
//	tempint_add/=10;
//	if(tempint_add>=3922) 
//	{
//		realtemperture = 0;
//	}
//	else if(tempint_add<=85) 
//	{
//		realtemperture = 230;//边界检查
//	}
//	else
//	{
//		//查表
//		for(i=0;i<320;i++)
//		{
//			if(tempint_add>TEMPTABLE[i]) 
//			{
//				realtemperture = i-20;
//				break;
//			}
//		}
//	}
//} 

//void BeepWork()
//{
//	static volatile unsigned int a	__attribute__ ((at(0x580)));
//	static volatile unsigned int x	__attribute__ ((at(0x582)));   
//   	for (a=0;a<2700;a++)       //for循环让蜂鸣器发声1秒
//	{    
//		                               
//		BUZ=!BUZ;      
//		for (x=0;x<45;x++);            //45为蜂鸣器发声频率，可调
//	}
//}   