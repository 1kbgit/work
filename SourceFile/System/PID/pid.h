/*
********************************************************************************
*                                嵌入式微系统
*                                   msOS
*
*                            硬件平台:msPLC DEMO
*                          主芯片:STM32F103R8T6/RBT6
*                           深圳市雨滴科技有限公司
*
*                                作者:王绍伟
*                                网名:凤舞天
*                                标识:Wangsw
*
*                                QQ:26033613
*                               QQ群:291235815
*                        论坛:http://bbs.huayusoft.com
*                        淘宝店:http://52edk.taobao.com
*                博客:http://forum.eet-cn.com/BLOG_wangsw317_1268.HTM
********************************************************************************
*文件名     : pid.h
********************************************************************************
*版本     作者            日期            说明
*V0.1    Wangsw        2013/09/13       初始版本
********************************************************************************
*/

#ifndef __PID_H
#define __PID_H



#define Prescaler   App.Data.Prescaler
#define Period      App.Data.Period 
#define DutyRatio   App.Data.DutyRatio

static float ErrValue;
static float ErrValueSum = 0;
static int times = 0;
static int times1 = 0;
static int KI = 0;
static int KP = 1;




extern void Pid(void);


    
#endif 

