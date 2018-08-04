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
*�ļ���     : menu.c
*����       : �������
*ԭ��       : ���ӳ����а����������Form��ÿһ��������Լ���BackText�������֡�
*           : Chart��Label��ǩ��TextBox�ı�����ؼ�������Add��������֮��
*           : ��Ҫ��ʼ��ֵ��
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/07/21       ��ʼ�汾
********************************************************************************
*/

#include "system.h"
#include "app.h"




static void InitLogoForm(void)
{
    System.Gui.Form.Init(&App.Menu.LogoForm);
    App.Menu.LogoForm.BackTextPointer = "    ��οƼ�    "
                                        "      msOS      "
                                        "     V1.4.0     "
                                        "   2017.12.01   ";
}

static void InitPidForm(void)
{
    static TextBox SetValueTextBox;
    static TextBox DutyRatioTextBox;
    static Label ReadValueLabel;
    static Label KPLabel;
    static Label KILabel;
    static Label ErrValueLabel;

    static Label PidOnOffLabel;
    static const string PidOnOffString[] = {"��", "��"};
   
    System.Gui.Form.Init(&App.Menu.PidForm);
    App.Menu.PidForm.BackTextPointer = "PID   Ŀ��    ��"
                                       "P:    ռ�ձ�   %"
                                       "I:    ��ǰ    ��"
                                       "      ���      ";

    System.Gui.Form.AddTextBox(&App.Menu.PidForm, &SetValueTextBox);
    SetValueTextBox.DataPointer = (void *)(&App.Data.PidSetValue);
    SetValueTextBox.Type = GuiDataTypeIntDec;
    SetValueTextBox.DataMax = 1000;
    SetValueTextBox.DataMin = 0;
    SetValueTextBox.DataBigStep = 5;
    SetValueTextBox.DataStep = 1;
    SetValueTextBox.X = 13;
    SetValueTextBox.Y = 0;
    
    System.Gui.Form.AddTextBox(&App.Menu.PidForm, &DutyRatioTextBox);
    DutyRatioTextBox.DataPointer = (void *)(&App.Data.DutyRatio);
    DutyRatioTextBox.Type = GuiDataTypeIntDec;
    DutyRatioTextBox.DataMax = 100;
    DutyRatioTextBox.DataMin = 0;
    DutyRatioTextBox.DataBigStep = 10;
    DutyRatioTextBox.DataStep = 1;
    DutyRatioTextBox.X = 14;
    DutyRatioTextBox.Y = 1;


    System.Gui.Form.AddLabel(&App.Menu.PidForm, &ReadValueLabel);
    ReadValueLabel.DataPointer = (void *)(&App.Data.PidReadValue);
    ReadValueLabel.Type = GuiDataTypeFloatDec;
    ReadValueLabel.Digits = 2;
    ReadValueLabel.X = 13;
    ReadValueLabel.Y = 2;

    System.Gui.Form.AddLabel(&App.Menu.PidForm, &KPLabel);
    KPLabel.DataPointer = (void *)(&App.Data.KP);
    KPLabel.Type = GuiDataTypeIntDec;
    KPLabel.Digits = 2;
    KPLabel.X = 5;
    KPLabel.Y = 1;

    System.Gui.Form.AddLabel(&App.Menu.PidForm, &KILabel);
    KILabel.DataPointer = (void *)(&App.Data.KI);
    KILabel.Type = GuiDataTypeIntDec;
    KILabel.Digits = 2;
    KILabel.X = 5;
    KILabel.Y = 2;

    System.Gui.Form.AddLabel(&App.Menu.PidForm, &ErrValueLabel);
    ErrValueLabel.DataPointer = (void *)(&App.Data.ErrValue);
    ErrValueLabel.Type = GuiDataTypeIntDec;
    ErrValueLabel.Digits = 2;
    ErrValueLabel.X = 13;
    ErrValueLabel.Y = 3;

    System.Gui.Form.AddLabel(&App.Menu.PidForm, &PidOnOffLabel);
    PidOnOffLabel.DataPointer = (void *)(&App.Data.PidOnOff);
    PidOnOffLabel.Type = GuiDataTypeSnString;
    PidOnOffLabel.Align = GuiDataAlignRight;
    PidOnOffLabel.StringBlockPointer = PidOnOffString;
    PidOnOffLabel.X = 3;
    PidOnOffLabel.Y = 3;
    
}


void InitMenu(void)
{
    InitLogoForm();
    InitPidForm();

}
/*******************************************************************************
* ������	: MenuTask
* ����	    : MenuTask���񣬱���Ϊ������ȼ����񣬽�������Form�ڵĸ����ؼ�������ʾ
* �������  : ��
* ���ز���  : ��
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/12/16       �޸İ汾
*******************************************************************************/
void MenuTask (void)
{
    static uint MenuSystick; 
    
    InitMenu();
    MenuSystick = App.Data.Systick1000 + 100;
    while(true)             
    {
        if (App.Data.Systick1000 >= MenuSystick)
        {
            MenuSystick = App.Data.Systick1000 + 100;
            System.Gui.Parse(App.Menu.FocusFormPointer);
        }
    }
}

