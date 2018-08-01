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
    ErrValue= App.Data.PidSetValue - App.Data.PidReadValue + 1;   
}

 void Pid(void)
{
     
    System.Device.DO.Config(DoPwm);
            System.Device.DO.Pwm.Open(PwmChannel1);
            System.Device.DO.Pwm.SetParameter(PwmChannel1,Prescaler,Period,DutyRatio);

    System.Device.DO.Pwm.SetDutyRatio (PwmChannel1, DutyRatio);//����ռ�ձ�
    AdcReadTemp();  //adc��ȡ�¶�
    ErrValueCount();     //�¶Ȳ�����

    if(ErrValue>=10)     {DutyRatio = 100;}  //����²����100����ռ�ձȰٷְ�
    else if(ErrValue>6&&ErrValue<10)          //����²���6-10��
    {
        KP = 10;             //Pϵ��Ϊ10��
        DutyRatio = KP*ErrValue;  //ռ�ձ�ΪPϵ�����Բ��    
        if(DutyRatio>=100)  {DutyRatio = 100;}   //�ж�ռ�ձ��Ƿ񳬹�100�����Ϊ����
    }
    else if(ErrValue>5&&ErrValue<=6)          //�²���5-6֮�䣬�����½��в���
    {
        KP = 10;
        ErrValueSum =ErrValueSum + ErrValue;       //��������֮��
        times ++;                   //��������

        DutyRatio = KP*ErrValue;  //����ռ�ձ�  
        if(DutyRatio>=100)  {DutyRatio = 100;}
    }

    else if(ErrValue>2&&ErrValue<= 5)      //�²���2-5֮��
    {
        KP = 10;         //Pϵ��Ϊ10��
        times1 ++;              //������ʱ���ǹ�һ����400����������ռ�ձ�
        if(times1 >= 400 )  {KI++;times1 = 0;}
        
        DutyRatio = KP*ErrValue + KI*(ErrValue/times);
        if(DutyRatio>=100)  {DutyRatio = 100;}
    }
    else if(ErrValue>0.5&&ErrValue<=2)
    {
        KP = 1;          //Pϵ��Ϊ1��
        times1 ++;              //������ʱ���ǹ�һ����400����������ռ�ձ�
        if(times1 >= 400 )  {KI ++;times1 = 0;}
          
        DutyRatio = KP*ErrValue + KI*(ErrValueSum/times);
        if(DutyRatio>=100)  {DutyRatio = 100;}
        if(DutyRatio<=0)    {DutyRatio = 1;}
    }
    else if(ErrValue >= 0&&ErrValue <= 0.5)
   {
        KP = 1;          //Pϵ��Ϊ1��
        times1 ++;
        if(times1 >= 200 )    
        {
            KI --;   //������ʱ���ǹ�һ����400����������ռ�ձ�
            if(KI<=0)   {KI = 1;times1 = 0;}  //��ֹռ�ձ�Ϊ0
        }
        DutyRatio = KP*ErrValue + KI*(ErrValueSum/times);
        if(DutyRatio>=100)  {DutyRatio = 100;}
        if(DutyRatio<=0)    {DutyRatio = 1;}
    }
    else if(ErrValue < 0)       //���Ϊ��ֵ�����¶ȸ����趨�¶�
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










    



