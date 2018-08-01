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
    ErrValue= App.Data.PidSetValue - App.Data.PidReadValue + 1;   
}

 void Pid(void)
{
     
    System.Device.DO.Config(DoPwm);
            System.Device.DO.Pwm.Open(PwmChannel1);
            System.Device.DO.Pwm.SetParameter(PwmChannel1,Prescaler,Period,DutyRatio);

    System.Device.DO.Pwm.SetDutyRatio (PwmChannel1, DutyRatio);//设置占空比
    AdcReadTemp();  //adc读取温度
    ErrValueCount();     //温度差距计算

    if(ErrValue>=10)     {DutyRatio = 100;}  //如果温差大于100；则占空比百分百
    else if(ErrValue>6&&ErrValue<10)          //如果温差在6-10；
    {
        KP = 10;             //P系数为10；
        DutyRatio = KP*ErrValue;  //占空比为P系数乘以差距    
        if(DutyRatio>=100)  {DutyRatio = 100;}   //判断占空比是否超过100，最大为满载
    }
    else if(ErrValue>5&&ErrValue<=6)          //温差在5-6之间，对升温进行采样
    {
        KP = 10;
        ErrValueSum =ErrValueSum + ErrValue;       //采样升温之和
        times ++;                   //采样次数

        DutyRatio = KP*ErrValue;  //计算占空比  
        if(DutyRatio>=100)  {DutyRatio = 100;}
    }

    else if(ErrValue>2&&ErrValue<= 5)      //温差在2-5之间
    {
        KP = 10;         //P系数为10；
        times1 ++;              //持续计时，记够一定（400）次数增加占空比
        if(times1 >= 400 )  {KI++;times1 = 0;}
        
        DutyRatio = KP*ErrValue + KI*(ErrValue/times);
        if(DutyRatio>=100)  {DutyRatio = 100;}
    }
    else if(ErrValue>0.5&&ErrValue<=2)
    {
        KP = 1;          //P系数为1；
        times1 ++;              //持续计时，记够一定（400）次数增加占空比
        if(times1 >= 400 )  {KI ++;times1 = 0;}
          
        DutyRatio = KP*ErrValue + KI*(ErrValueSum/times);
        if(DutyRatio>=100)  {DutyRatio = 100;}
        if(DutyRatio<=0)    {DutyRatio = 1;}
    }
    else if(ErrValue >= 0&&ErrValue <= 0.5)
   {
        KP = 1;          //P系数为1；
        times1 ++;
        if(times1 >= 200 )    
        {
            KI --;   //持续计时，记够一定（400）次数减少占空比
            if(KI<=0)   {KI = 1;times1 = 0;}  //防止占空比为0
        }
        DutyRatio = KP*ErrValue + KI*(ErrValueSum/times);
        if(DutyRatio>=100)  {DutyRatio = 100;}
        if(DutyRatio<=0)    {DutyRatio = 1;}
    }
    else if(ErrValue < 0)       //差距为负值，即温度高于设定温度
    {
        KP = 1;
        times1 ++;
        if(times1 >= 100 )    
        {
            KI --;
            times1 = 0;
            if(KI<=0)    {DutyRatio = 1;}
            DutyRatio = KP*ErrValue + KI*(ErrValueSum/times);
            if(DutyRatio>=100)  {DutyRatio = 100;}
            if(DutyRatio<=0)    {DutyRatio = 1;}
        }               
    }  

	
}










    



