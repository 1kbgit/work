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
#include"app.h"

PidStruct Pid;


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
    AdcReadTemp();  //adc读取温度
    ErrValueCount();     //温度差距计算

    if(Pid.ErrValue>=10)     {DutyRatio =Pid.MaxDutyRatio;}  
    else if(Pid.ErrValue>6&&Pid.ErrValue<10)          //如果温差在6-10；
    {
        Pid.KP = 10;             //P系数为10；
        DutyRatio = Pid.KP*Pid.ErrValue;  //占空比 
        if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio=Pid.MaxDutyRatio;}
    }
    else if(Pid.ErrValue>5&&Pid.ErrValue<=6)          //温差在5-6之间，对升温进行采样
    {
        Pid.KP = 10;
        Pid.ErrValueSum =Pid.ErrValueSum + Pid.ErrValue;       //采样和
        DutyRatio = Pid.KP*Pid.ErrValue; 
        if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio =Pid.MaxDutyRatio;}
    }

    else if(Pid.ErrValue>2&&Pid.ErrValue<= 5)      //温差在2-5之间
    {
        Pid.KP = 10;         //P系数为10；
        Pid.times1 ++;              //持续计时，记够一定（400）次数增加占空比
        if(Pid.times1 >= 400 )  {Pid.KI++;Pid.times1 = 0;}
        
        DutyRatio = Pid.KP*Pid.ErrValue + Pid.KI*Pid.ErrValue;
        if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio=Pid.MaxDutyRatio;}
    }
    else if(Pid.ErrValue>0.5&&Pid.ErrValue<=2)
    {
        Pid.KP = 1;             //P系数为1；
        Pid.times1 ++;          //持续计时，记够一定（400）次数增加占空比
        if(Pid.times1 >= 400 )  {Pid.KI ++;Pid.times1 = 0;}
          
        DutyRatio = Pid.KP*Pid.ErrValue + Pid.KI*(Pid.ErrValueSum);
        if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio=Pid.MaxDutyRatio;}
        if(DutyRatio<=0)    {DutyRatio = 1;}
    }
    else if(Pid.ErrValue >= 0&&Pid.ErrValue <= 0.5)
   {
        Pid.KP = 1;             //P系数为1；
        Pid.times1 ++;
        if(Pid.times1 >= 200 )    
        {
            Pid.KI --;          //持续计时，记够一定（400）次数减少占空比
            if(Pid.KI<=0)   {Pid.KI = 1;Pid.times1 = 0;}  //防止占空比为0
        }
        DutyRatio = Pid.KP*Pid.ErrValue + Pid.KI*(Pid.ErrValueSum);
        if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio=Pid.MaxDutyRatio;}
        if(DutyRatio<=0)    {DutyRatio = 1;}
    }
    else if(Pid.ErrValue < 0)       //差距为负值，即温度高于设定温度
    {
        Pid.KP = 1;
        Pid.times1 ++;
        if(Pid.times1 >= 100 )    
        {
            Pid.KI --;
            Pid.times1 = 0;
            if(Pid.KI<=0)    {DutyRatio = 1;}
            DutyRatio = Pid.KP*Pid.ErrValue + Pid.KI*(Pid.ErrValueSum);
            if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio=Pid.MaxDutyRatio;}
            if(DutyRatio<=0)    {DutyRatio = 1;}
        }               
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







    



