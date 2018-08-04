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
*文件名     : menu.c
*作用       : 界面设计
*原理       : 例子程序中包含五个窗体Form，每一个窗体可以加载BackText背景文字、
*           : Chart表、Label标签、TextBox文本四类控件，采用Add方法加载之后，
*           : 需要初始化值。
********************************************************************************
*版本     作者            日期            说明
*V0.1    Wangsw        2013/07/21       初始版本
********************************************************************************
*/

#include "system.h"
#include "app.h"




static void InitLogoForm(void)
{
    System.Gui.Form.Init(&App.Menu.LogoForm);
    App.Menu.LogoForm.BackTextPointer = "    雨滴科技    "
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
    static const string PidOnOffString[] = {"关", "开"};
   
    System.Gui.Form.Init(&App.Menu.PidForm);
    App.Menu.PidForm.BackTextPointer = "PID   目标    度"
                                       "P:    占空比   %"
                                       "I:    当前    度"
                                       "      差距      ";

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
* 函数名	: MenuTask
* 描述	    : MenuTask任务，必须为最低优先级任务，解析窗体Form内的各个控件用于显示
* 输入参数  : 无
* 返回参数  : 无
********************************************************************************
*版本     作者            日期            说明
*V0.1    Wangsw        2013/12/16       修改版本
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

