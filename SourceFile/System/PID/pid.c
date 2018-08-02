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
#include"app.h"

PidStruct Pid;


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
    AdcReadTemp();  //adc��ȡ�¶�
    ErrValueCount();     //�¶Ȳ�����

    if(Pid.ErrValue>=10)     {DutyRatio =Pid.MaxDutyRatio;}  
    else if(Pid.ErrValue>6&&Pid.ErrValue<10)          //����²���6-10��
    {
        Pid.KP = 10;             //Pϵ��Ϊ10��
        DutyRatio = Pid.KP*Pid.ErrValue;  //ռ�ձ� 
        if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio=Pid.MaxDutyRatio;}
    }
    else if(Pid.ErrValue>5&&Pid.ErrValue<=6)          //�²���5-6֮�䣬�����½��в���
    {
        Pid.KP = 10;
        Pid.ErrValueSum =Pid.ErrValueSum + Pid.ErrValue;       //������
        DutyRatio = Pid.KP*Pid.ErrValue; 
        if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio =Pid.MaxDutyRatio;}
    }

    else if(Pid.ErrValue>2&&Pid.ErrValue<= 5)      //�²���2-5֮��
    {
        Pid.KP = 10;         //Pϵ��Ϊ10��
        Pid.times1 ++;              //������ʱ���ǹ�һ����400����������ռ�ձ�
        if(Pid.times1 >= 400 )  {Pid.KI++;Pid.times1 = 0;}
        
        DutyRatio = Pid.KP*Pid.ErrValue + Pid.KI*Pid.ErrValue;
        if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio=Pid.MaxDutyRatio;}
    }
    else if(Pid.ErrValue>0.5&&Pid.ErrValue<=2)
    {
        Pid.KP = 1;             //Pϵ��Ϊ1��
        Pid.times1 ++;          //������ʱ���ǹ�һ����400����������ռ�ձ�
        if(Pid.times1 >= 400 )  {Pid.KI ++;Pid.times1 = 0;}
          
        DutyRatio = Pid.KP*Pid.ErrValue + Pid.KI*(Pid.ErrValueSum);
        if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio=Pid.MaxDutyRatio;}
        if(DutyRatio<=0)    {DutyRatio = 1;}
    }
    else if(Pid.ErrValue >= 0&&Pid.ErrValue <= 0.5)
   {
        Pid.KP = 1;             //Pϵ��Ϊ1��
        Pid.times1 ++;
        if(Pid.times1 >= 200 )    
        {
            Pid.KI --;          //������ʱ���ǹ�һ����400����������ռ�ձ�
            if(Pid.KI<=0)   {Pid.KI = 1;Pid.times1 = 0;}  //��ֹռ�ձ�Ϊ0
        }
        DutyRatio = Pid.KP*Pid.ErrValue + Pid.KI*(Pid.ErrValueSum);
        if(DutyRatio>=Pid.MaxDutyRatio)  {DutyRatio=Pid.MaxDutyRatio;}
        if(DutyRatio<=0)    {DutyRatio = 1;}
    }
    else if(Pid.ErrValue < 0)       //���Ϊ��ֵ�����¶ȸ����趨�¶�
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







    



