/*
********************************************************************************
*                                Ƕ��ʽ΢ϵͳ
*                                   msOS
*
*                            Ӳ��ƽ̨:msPLC DEMO
*                          ��оƬ:STM32F103R8T6/RBT6
*                           ��������οƼ����޹�˾
*
*                                ����:����ΰ
*                                ����:������
*                                ��ʶ:Wangsw
*
*                                QQ:26033613
*                               QQȺ:291235815
*                        ��̳:http://bbs.huayusoft.com
*                        �Ա���:http://52edk.taobao.com
*                ����:http://forum.eet-cn.com/BLOG_wangsw317_1268.HTM
********************************************************************************
*�ļ���     : pid.h
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/09/13       ��ʼ�汾
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

