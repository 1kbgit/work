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
*                                ��ʶ:wangsw
*
*                                QQ:26033613
*                               QQȺ:291235815
*                        ��̳:http://bbs.huayusoft.com
*                        �Ա���:http://52edk.taobao.com
*                ����:http://forum.eet-cn.com/BLOG_wangsw317_1268.HTM
********************************************************************************
*�ļ���   : system.Pid.c
*����     : ϵͳӦ���ļ�
*����ʱ�� : 2013.7.21
********************************************************************************
*/


#include"system.h"
#include"pid.h"

PidStruct Pid;



/*****ע�ᴫ������****/
static void Register(AdcChannelEnum channel, ushort * dataPointer)
{
    RegisterPointerBlock[channel] = dataPointer;
}



static void AdcReadTemp(void)   //adc��ȡ�¶�
{
    float adcData;
    static float TempData = 0;
    adcData = App.Data.Adc.A0;  
    TempData = (TempData * 0.99f) + (adcData * 0.0008f);

    App.Data.PidReadValue = TempData;
}

static void ErrValueCount(void)      //�¶Ȳ�����
{
    Pid.ErrValue= App.Data.PidSetValue - App.Data.PidReadValue + 1;   
}

 void PidSystick100(void)
{
     
    System.Device.DO.Config(DoPwm);
    System.Device.DO.Pwm.Open(PwmChannel1);
    System.Device.DO.Pwm.SetParameter(PwmChannel1,Prescaler,Period,DutyRatio);

    System.Device.DO.Pwm.SetDutyRatio (PwmChannel1, DutyRatio);//����ռ�ձ�


    AdcReadTemp();      //adc��ȡ�¶�
    ErrValueCount();    //�¶Ȳ�����

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







    



