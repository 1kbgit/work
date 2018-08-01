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


void InitWorkForm(void)
{
    static TextBox FrequencyTextBox;
    static TextBox PowerPercentTextBox;
    static Label PowerLabel;
    static Label VoltageLabel;
    static Label CurrentLabel;
    static Label TemperatureLabel;
    static Label OnOffLabel;
    static const string OnOffString[] = {"关", "开"};
    
    System.Gui.Form.Init(&App.Menu.WorkForm);
    App.Menu.WorkForm.BackTextPointer = "频率          Hz"
                                        "功率   %       W"
                                        "电压    电流    "
                                        "温度   C        ";

    System.Gui.Form.AddTextBox(&App.Menu.WorkForm, &FrequencyTextBox);
    FrequencyTextBox.DataPointer = (void *)(&App.Data.Frequency);
    FrequencyTextBox.Type = GuiDataTypeIntDec;
    FrequencyTextBox.DataMax = 980000;
    FrequencyTextBox.DataMin = 600000;
    FrequencyTextBox.DataBigStep = 10000;
    FrequencyTextBox.DataStep = 1000;
    FrequencyTextBox.X = 13;
    FrequencyTextBox.Y = 0;
    
    System.Gui.Form.AddTextBox(&App.Menu.WorkForm, &PowerPercentTextBox);
    PowerPercentTextBox.DataPointer = (void *)(&App.Data.PowerPercent);
    PowerPercentTextBox.Type = GuiDataTypeIntDec;
    PowerPercentTextBox.DataMax = 100;
    PowerPercentTextBox.DataMin = 0;
    PowerPercentTextBox.DataBigStep = 10;
    PowerPercentTextBox.DataStep = 1;
    PowerPercentTextBox.X = 6;
    PowerPercentTextBox.Y = 1;
    
    System.Gui.Form.AddLabel(&App.Menu.WorkForm, &PowerLabel);
    PowerLabel.DataPointer = (void *)(&App.Data.Power);
    PowerLabel.Type = GuiDataTypeIntDec;
    PowerLabel.X = 14;
    PowerLabel.Y = 1;
    
    System.Gui.Form.AddLabel(&App.Menu.WorkForm, &VoltageLabel);
    VoltageLabel.DataPointer = (void *)(&App.Data.Voltage);
    VoltageLabel.Type = GuiDataTypeIntDec;
    VoltageLabel.X = 7;
    VoltageLabel.Y = 2;
    
    System.Gui.Form.AddLabel(&App.Menu.WorkForm, &CurrentLabel);
    CurrentLabel.DataPointer = (void *)(&App.Data.Current);
    CurrentLabel.Type = GuiDataTypeIntDec;
    CurrentLabel.X = 15;
    CurrentLabel.Y = 2;
    
    System.Gui.Form.AddLabel(&App.Menu.WorkForm, &TemperatureLabel);
    TemperatureLabel.DataPointer = (void *)(&App.Data.Temperature);
    TemperatureLabel.Type = GuiDataTypeIntDec;
    TemperatureLabel.X = 6;
    TemperatureLabel.Y = 3;

    System.Gui.Form.AddLabel(&App.Menu.WorkForm, &OnOffLabel);
    OnOffLabel.DataPointer = (void *)(&App.Data.OnOff);
    OnOffLabel.Type = GuiDataTypeSnString;
    OnOffLabel.Align = GuiDataAlignRight;
    OnOffLabel.StringBlockPointer = OnOffString;
    OnOffLabel.X = 15;
    OnOffLabel.Y = 3;
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





static void InitPortForm(void)
{
    static Label X0Label;
    static Label X1Label;
    static Label X2Label;
    static Label X3Label;

    static TextBox Y0TextBox;
    static TextBox Y1TextBox;
    static TextBox Y2TextBox;
    static TextBox Y3TextBox;
    static TextBox Y4TextBox;
    static TextBox Y5TextBox;

    static Label Adc0Label;
    static Label Adc1Label;
    static Label Adc2Label;
    static Label Adc3Label;

    System.Gui.Form.Init(&App.Menu.PortForm);
    App.Menu.PortForm.BackTextPointer = "X   :   Y       "
                                        "A0:     A1:     "
                                        "A2:     A3:     "
                                        "                ";
    System.Gui.Form.AddLabel(&App.Menu.PortForm, &X0Label);
    X0Label.DataPointer = (void *)(App.Data.DI.pX0);
    X0Label.Type = GuiDataTypeByteDec;
    X0Label.X = 2;
    X0Label.Y = 0; 
    
    System.Gui.Form.AddLabel(&App.Menu.PortForm, &X1Label);
    X1Label.DataPointer = (void *)(App.Data.DI.pX1);
    X1Label.Type = GuiDataTypeByteDec;
    X1Label.X = 3;
    X1Label.Y = 0; 

    System.Gui.Form.AddLabel(&App.Menu.PortForm, &X2Label);
    X2Label.DataPointer = (void *)(App.Data.DI.pX2);
    X2Label.Type = GuiDataTypeByteDec;
    X2Label.X = 4;
    X2Label.Y = 0; 
    
    System.Gui.Form.AddLabel(&App.Menu.PortForm, &X3Label);
    X3Label.DataPointer = (void *)(App.Data.DI.pX3);
    X3Label.Type = GuiDataTypeByteDec;
    X3Label.X = 5;
    X3Label.Y = 0; 
    /***********************************************/
    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y0TextBox);
    Y0TextBox.DataPointer = (void *)(&App.Data.DO.Y0);
    Y0TextBox.Type = GuiDataTypeByteDec;
    Y0TextBox.X = 10;
    Y0TextBox.Y = 0;
    Y0TextBox.DataMax = 1;
    Y0TextBox.DataMin = 0;
    Y0TextBox.DataBigStep = 1;
    Y0TextBox.DataStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y1TextBox);
    Y1TextBox.DataPointer = (void *)(&App.Data.DO.Y1);
    Y1TextBox.Type = GuiDataTypeByteDec;
    Y1TextBox.X = 11;
    Y1TextBox.Y = 0;
    Y1TextBox.DataMax = 1;
    Y1TextBox.DataMin = 0;
    Y1TextBox.DataBigStep = 1;
    Y1TextBox.DataStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y2TextBox);
    Y2TextBox.DataPointer = (void *)(&App.Data.DO.Y2);
    Y2TextBox.Type = GuiDataTypeByteDec;
    Y2TextBox.X = 12;
    Y2TextBox.Y = 0;
    Y2TextBox.DataMax = 1;
    Y2TextBox.DataMin = 0;
    Y2TextBox.DataBigStep = 1;
    Y2TextBox.DataStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y3TextBox);
    Y3TextBox.DataPointer = (void *)(&App.Data.DO.Y3);
    Y3TextBox.Type = GuiDataTypeByteDec;
    Y3TextBox.X = 13;
    Y3TextBox.Y = 0;
    Y3TextBox.DataMax = 1;
    Y3TextBox.DataMin = 0;
    Y3TextBox.DataBigStep = 1;
    Y3TextBox.DataStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y4TextBox);
    Y4TextBox.DataPointer = (void *)(&App.Data.DO.Y4);
    Y4TextBox.Type = GuiDataTypeByteDec;
    Y4TextBox.X = 14;
    Y4TextBox.Y = 0;
    Y4TextBox.DataMax = 1;
    Y4TextBox.DataMin = 0;
    Y4TextBox.DataBigStep = 1;
    Y4TextBox.DataStep = 1;

    System.Gui.Form.AddTextBox(&App.Menu.PortForm, &Y5TextBox);
    Y5TextBox.DataPointer = (void *)(&App.Data.DO.Y5);
    Y5TextBox.Type = GuiDataTypeByteDec;
    Y5TextBox.X = 15;
    Y5TextBox.Y = 0;
    Y5TextBox.DataMax = 1;
    Y5TextBox.DataMin = 0;
    Y5TextBox.DataBigStep = 1;
    Y5TextBox.DataStep = 1;
    /***********************************************/
    System.Gui.Form.AddLabel(&App.Menu.PortForm, &Adc0Label);
    Adc0Label.DataPointer = (void *)(App.Data.Adc.pA0);
    Adc0Label.Type = GuiDataTypeUshortDec;
    Adc0Label.X = 6;
    Adc0Label.Y = 1;   

    System.Gui.Form.AddLabel(&App.Menu.PortForm, &Adc1Label);
    Adc1Label.DataPointer = (void *)(App.Data.Adc.pA1);
    Adc1Label.Type = GuiDataTypeUshortDec;
    Adc1Label.X = 15;
    Adc1Label.Y = 1;   

    System.Gui.Form.AddLabel(&App.Menu.PortForm, &Adc2Label);
    Adc2Label.DataPointer = (void *)(App.Data.Adc.pA2);
    Adc2Label.Type = GuiDataTypeUshortDec;
    Adc2Label.X = 6;
    Adc2Label.Y = 2;   

    System.Gui.Form.AddLabel(&App.Menu.PortForm, &Adc3Label);
    Adc3Label.DataPointer = (void *)(App.Data.Adc.pA3);
    Adc3Label.Type = GuiDataTypeUshortDec;
    Adc3Label.X = 15;
    Adc3Label.Y = 2;  
}


void InitMenu(void)
{
    InitLogoForm();
    InitWorkForm();
    InitPidForm();
    InitPortForm();
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

