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
*                                标识:wangsw
*
*                                QQ:26033613
*                               QQ群:291235815
*                        论坛:http://bbs.huayusoft.com
*                        淘宝店:http://52edk.taobao.com
*                博客:http://forum.eet-cn.com/BLOG_wangsw317_1268.HTM
********************************************************************************
*文件名   : system.Pid.c
*作用     : 系统应用文件
*创建时间 : 2013.7.21
********************************************************************************
*/


#include"system.h"
#include"pid.h"

PidStruct Pid;



/*****注册传送数据****/
static void Register(AdcChannelEnum channel, ushort * dataPointer)
{
    RegisterPointerBlock[channel] = dataPointer;
}



static void AdcReadTemp(void)   //adc读取温度
{
    float adcData;
    static float TempData = 0;
    adcData = App.Data.Adc.A0;  
    TempData = (TempData * 0.99f) + (adcData * 0.0008f);

    App.Data.PidReadValue = TempData;
}

static void ErrValueCount(void)      //温度差距计算
{
    Pid.ErrValue= App.Data.PidSetValue - App.Data.PidReadValue + 1;   
}

 void PidSystick100(void)
{
     
    System.Device.DO.Config(DoPwm);
    System.Device.DO.Pwm.Open(PwmChannel1);
    System.Device.DO.Pwm.SetParameter(PwmChannel1,Prescaler,Period,DutyRatio);

    System.Device.DO.Pwm.SetDutyRatio (PwmChannel1, DutyRatio);//设置占空比


    AdcReadTemp();      //adc读取温度
    ErrValueCount();    //温度差距计算

    if(Pid.ErrValue>=10)     {DutyRatio =Pid.MaxDutyRatio;}  
    else if 
    {
        DutyRatio = Pid.KP * Pid.ErrValue; 
        if(DutyRatio>=Pid.MaxDutyRatio) {DutyRatio = Pid.MaxDutyRatio;}
        Pid.ErrValueSum = Pid.ErrValue++;
        
        Pid.LastDutyRatio = DutyRatio;
        if(Pid.ErrValue > 1)  {DutyRatio = Pid.KP * Pid.ErrValue + Pid.KI*Pid.ErrValueSum; }
        else if(abs(Pid.ErrValue) <= 1)    {DutyRatio = Pid.LastDutyRatio;}
        else    {DutyRatio = Pid.KP * Pid.ErrValue + Pid.KI*Pid.ErrValueSum;}
    }


    
    

	
}



void InitPid(void)
{
	//Pid.KP = 6;
	//Pid.KI = 0.95;
	
    
	Pid.ErrValue = AppDataPointer->ErrValue;
	Pid.KI = AppDataPointer->KI;
    Pid.KP = AppDataPointer->KP;
    
    System.Device.DO.Pwm.SetParameter(PwmChannel1, 7200, 100, 0);
	System.Device.Systick.Register(Systick100, PidSystick100);
}







    



