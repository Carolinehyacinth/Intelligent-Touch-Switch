#ifndef _PROTECT_H_
#define _PROTECT_H_
#include "MYTYPE.H"

void buzzer_on(void);    //蜂鸣器
void warn_up(void);//警报开启标志位控制
void warn_buzzer(void);    //警报蜂鸣器控制
void protect_up(void);//开启过热保护标志
void protection(void);    //过热保
void ventilate_auto_up(void);//取暖关闭自动开启换气
void ventilate_auto(void);//开启换气

#endif