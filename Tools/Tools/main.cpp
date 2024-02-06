#include "framework.h"
#include "Tools.h"

//#include "ToolsLibrary.h"
#include "../../ToolsDll/ToolsDll/ToolsDll.h"

#include <windows.h>
#include <ShellAPI.h> //“ShellExecute”: 找不到标识符

//#define test
#define control

LPCWSTR ProjectName = L"工具箱 v0.8";

//计数 初始化句柄数量
Counts CText(2);
Counts CButton(6);
Counts CEdit(1);
Counts Cm_hwnd(1);

//笔记本键盘状态
bool NoteKeyboardState = true;

//应用窗口大小 设置
#ifdef test
WindowSize wSize(1040, 240);
#endif
#ifdef CMD
WindowSize wSize_CMD(540, 310);
#endif

#ifndef CMD
#ifndef test
WindowSize wSize(540, 260);
#endif
#endif
//WindowSize wSize(540, 200 + 55);

//初始化配置数据: 配置数量为 8(-1)
ToolsConfigFile ToolsCfgF(8); //ToolsCfgF.sizePath

//静态文本控件
//Y坐标
int StaticTextControlY = 10;    
#ifdef test
int StaticTextWidth = 500;
#endif
int StaticTextWidth = 240;
int StaticTextHeight = 30;
int PitchStaticCenter = (wSize.GetWindowSizeWidth() / 2) - (StaticTextWidth / 2);

//按键 Button--------------------------------------------------------------------------------------------------------------------
//按键大小
int ButtonWidth = 100; //宽
int ButtonHeight = 40; //高
//按键Y坐标
int ButtonY = 55;

//按键间距
int ButtonPitch = 5;
//间距分配
int PitchButtonCenter = (wSize.GetWindowSizeWidth() / 2) - (ButtonWidth / 2); //中间的按键
int ButtonPitchs = ButtonWidth + ButtonPitch;

//笔记本键盘状态 默认开启
bool NoteBookState = true;

map<string, LPCWSTR> hStatic_case = {
        {"文本-当前设置", L"当前设置:"},
        {"文本-启动状态", L"正在启动:"},
        {"文本-分辨率配置", L"自定义分辨率配置:"},
        {"文本-每日清单配置", L"每日清单配置:"},
        {"文本-工具箱设置", L"工具箱设置:"},
        {"分辨率-1080", L"1920 x 1080"},
        {"分辨率-1024", L"1280 x 1024"},
        {"启动项-steam", L"Steam..."},
        {"文件状态-已打开", L"已打开"},
        {"文件状态-正在打开", L"正在打开"},
        {"文件状态-打开失败", L"打开失败"},
        {"文件-steam", L"steam.exe"}
};

//按钮大小 设置
//MatrixPermutation matrix(100, 40, 5, wSize);

//class BaseWindow---------------------------------------------------------------------------------------------------------------------
template <class DERIVED_TYPE> 
class BaseWindow 
{
protected:

    virtual PCWSTR  ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd;
    HINSTANCE hInst;

public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        DERIVED_TYPE *pThis = NULL;

        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

            pThis->m_hwnd = hwnd;
        }
        else
        {
            pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }
        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    BaseWindow() : m_hwnd(NULL) { } //构造函数 默认m_hwnd为NULL

    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
        )
    {
        WNDCLASS wc = {0};

        wc.lpfnWndProc   = DERIVED_TYPE::WindowProc;
        wc.hInstance     = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();

        RegisterClass(&wc);

        m_hwnd = CreateWindowEx(
            dwExStyle, 
            ClassName(), 
            lpWindowName, 
            dwStyle, 
            x,
            y,
            wSize.GetWindowSizeWidth(),
            wSize.GetWindowSizeHeight(),
            hWndParent, 
            hMenu, 
            GetModuleHandle(NULL), 
            this
            );

//创建逻辑字体-----------------------------------------------------------------------------------------------------
        //创建逻辑字体
        HFONT hFont = CreateFont(
            -16/*高*/, -7/*宽*/, 0, 0, 400 /*一般这个值设为400*/,
            FALSE/*斜体?*/, FALSE/*下划线?*/, FALSE/*删除线?*/, DEFAULT_CHARSET,
            OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
            FF_DONTCARE, TEXT("微软雅黑")
        );

#ifdef control
//静态文本控件------------------------------------------------------------------------------------------------------
        //创建静态文本控件
        HWND hStatic1 = CreateWindow(
            TEXT("STATIC"),  //静态文本框的类名
            TEXT("未操作"),  //控件的文本
            WS_CHILD /*子窗口 */ | WS_VISIBLE /*创建时显示*/ | SS_CENTER/*文本居中*/ | SS_ENDELLIPSIS /*如果字符串的末尾不适合矩形，则会将其截断并添加省略号。*/,
            PitchStaticCenter - (StaticTextWidth / 2) - 10,    //X坐标
            StaticTextControlY,      //Y坐标
            StaticTextWidth,    //宽度
            StaticTextHeight,     //高度
            m_hwnd, //父窗口句柄
            (HMENU)101,  //为控件指定一个唯一标识符
            hInst,     //当前实例句柄
            NULL);     //不需要指针.
        //存储句柄
        if (!hStatic1 == NULL)
            CText.AddHWND(hStatic1);

        //创建静态文本控件
        HWND hStatic2 = CreateWindow(
            TEXT("STATIC"),  //静态文本框的类名
            TEXT("未操作"),  //控件的文本
            WS_CHILD /*子窗口 */ | WS_VISIBLE /*创建时显示*/ | SS_CENTER/*文本居中*/ | SS_ENDELLIPSIS /*如果字符串的末尾不适合矩形，则会将其截断并添加省略号。*/,
            PitchStaticCenter + (StaticTextWidth / 2),    //X坐标
            StaticTextControlY,      //Y坐标
            StaticTextWidth,    //宽度
            StaticTextHeight,     //高度
            m_hwnd, //父窗口句柄
            (HMENU)102,  //为控件指定一个唯一标识符
            hInst,     //当前实例句柄
            NULL);     //不需要指针.
        //存储句柄
        if (!hStatic2 == NULL)
            CText.AddHWND(hStatic2);

#ifdef CMD
        //创建静态文本控件
        HWND hStatic3 = CreateWindow(
            TEXT("STATIC"),  //静态文本框的类名
            TEXT("cmd: "),  //控件的文本
            WS_CHILD /*子窗口 */ | WS_VISIBLE /*创建时显示*/ | SS_CENTER/*文本居中*/ | SS_ENDELLIPSIS /*如果字符串的末尾不适合矩形，则会将其截断并添加省略号。*/,
            PitchStaticCenter - (StaticTextWidth / 2) - 10,    //X坐标
            ButtonY * 4,      //Y坐标
            60,    //宽度
            30,     //高度
            m_hwnd, //父窗口句柄
            (HMENU)103,  //为控件指定一个唯一标识符
            hInst,     //当前实例句柄
            NULL);     //不需要指针.
        //存储句柄
        if (!hStatic3 == NULL)
            CText.AddHWND(hStatic3);
#endif

//按键------------------------------------------------------------------------------------------------------

        HWND hwndButton1 = CreateWindow(
            L"BUTTON",  //静态文本框的类名 
            TEXT("未操作"),  //控件的文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  //窗口样式 
            PitchButtonCenter - ButtonPitchs,    //X坐标
            ButtonY,     //Y坐标
            ButtonWidth,    //按键宽度
            ButtonHeight,     //按键高度
            m_hwnd, //父窗口句柄
            (HMENU)1,   //为控件指定一个唯一标识符
            hInst,    //当前实例句柄
            NULL);  //不需要指针.
        //存储句柄
        if (!hwndButton1 == NULL)
            CButton.AddHWND(hwndButton1);

        HWND hwndButton2 = CreateWindow(
            L"BUTTON",  //静态文本框的类名 
            TEXT("未操作"),  //控件的文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  //窗口样式 
            PitchButtonCenter,    //X坐标
            ButtonY,     //Y坐标
            ButtonWidth,    //按键宽度
            ButtonHeight,     //按键高度
            m_hwnd, //父窗口句柄
            (HMENU)2,   //为控件指定一个唯一标识符
            hInst,    //当前实例句柄
            NULL);  //不需要指针.
        //存储句柄
        if (!hwndButton2 == NULL)
            CButton.AddHWND(hwndButton2);

        HWND hwndButton3 = CreateWindow(
            L"BUTTON",  //静态文本框的类名 
            L"启动Steam",  //控件的文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  //窗口样式 
            PitchButtonCenter + ButtonPitchs,    //X坐标
            ButtonY,     //Y坐标
            ButtonWidth,    //按键宽度
            ButtonHeight,     //按键高度
            m_hwnd, //父窗口句柄
            (HMENU)3,   //为控件指定一个唯一标识符
            hInst,    //当前实例句柄
            NULL);  //不需要指针.
        //存储句柄
        if (!hwndButton3 == NULL)
            CButton.AddHWND(hwndButton3);

        HWND hwndButton4 = CreateWindow(
            L"BUTTON",  //静态文本框的类名 
            L"Repos",  //控件的文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  //窗口样式 
            PitchButtonCenter - ButtonPitchs,    //X坐标
            ButtonY * 2,     //Y坐标
            ButtonWidth,    //按键宽度
            ButtonHeight,     //按键高度
            m_hwnd, //父窗口句柄
            (HMENU)4,   //为控件指定一个唯一标识符
            hInst,    //当前实例句柄
            NULL);  //不需要指针.
        //存储句柄
        if (!hwndButton4 == NULL)
            CButton.AddHWND(hwndButton4);

        HWND hwndButton5 = CreateWindow(
            L"BUTTON",  //静态文本框的类名 
            L"每日清单",  //控件的文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  //窗口样式 
            PitchButtonCenter,    //X坐标
            ButtonY * 2,     //Y坐标
            ButtonWidth,    //按键宽度
            ButtonHeight,     //按键高度
            m_hwnd, //父窗口句柄
            (HMENU)5,   //为控件指定一个唯一标识符
            hInst,    //当前实例句柄
            NULL);  //不需要指针.
        //存储句柄
        if (!hwndButton5 == NULL)
            CButton.AddHWND(hwndButton5);

        HWND hwndButton6 = CreateWindow(
            L"BUTTON",  //静态文本框的类名 
            L"工具箱设置",  //控件的文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  //窗口样式 
            PitchButtonCenter + ButtonPitchs,    //X坐标
            ButtonY * 2,     //Y坐标
            ButtonWidth,    //按键宽度
            ButtonHeight,     //按键高度
            m_hwnd, //父窗口句柄
            (HMENU)6,   //为控件指定一个唯一标识符
            hInst,    //当前实例句柄
            NULL);  //不需要指针.  
        //存储句柄
        if (!hwndButton6 == NULL)
            CButton.AddHWND(hwndButton6);

        HWND hwndButton7 = CreateWindow(
            L"BUTTON",  //静态文本框的类名 
            L"雷神加速器",  //控件的文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  //窗口样式 
            PitchButtonCenter - ButtonPitchs,    //X坐标
            ButtonY * 3,     //Y坐标
            ButtonWidth,    //按键宽度
            ButtonHeight,     //按键高度
            m_hwnd, //父窗口句柄
            (HMENU)7,   //为控件指定一个唯一标识符
            hInst,    //当前实例句柄
            NULL);  //不需要指针.  
        //存储句柄
        if (!hwndButton7 == NULL)
            CButton.AddHWND(hwndButton7);

        HWND hwndButton8 = CreateWindow(
            L"BUTTON",  //静态文本框的类名 
            L"确定",  //控件的文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  //窗口样式 
            PitchButtonCenter + ButtonPitchs * 2,    //X坐标
            ButtonY * 4,     //Y坐标
            ButtonWidth - 20,    //按键宽度
            ButtonHeight,     //按键高度
            m_hwnd, //父窗口句柄
            (HMENU)8,   //为控件指定一个唯一标识符
            hInst,    //当前实例句柄
            NULL);  //不需要指针.  
        //存储句柄
        if (!hwndButton8 == NULL)
            CButton.AddHWND(hwndButton8);

        HWND hwndButton9 = CreateWindow(
            L"BUTTON",  //静态文本框的类名 
            L"开/关 键盘",  //控件的文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  //窗口样式 
            PitchButtonCenter,    //X坐标
            ButtonY * 3,     //Y坐标
            ButtonWidth,    //按键宽度
            ButtonHeight,     //按键高度
            m_hwnd, //父窗口句柄
            (HMENU)9,   //为控件指定一个唯一标识符
            hInst,    //当前实例句柄
            NULL);  //不需要指针.
        //存储句柄
        if (!hwndButton9 == NULL)
            CButton.AddHWND(hwndButton9);

//编辑框----------------------------------------------------------------------------------
#ifdef CMD
        HWND hwndEdit = CreateWindow(
            L"edit",  //静态文本框的类名 
            L"",  //控件的文本
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_BORDER /*边框*/ | ES_AUTOHSCROLL /*水平滚动*/,  //窗口样式 
            PitchButtonCenter - 20 - ButtonPitchs,    //X坐标
            ButtonY * 4,     //Y坐标
            ButtonWidth + 220,    //按键宽度
            ButtonHeight,     //按键高度
            m_hwnd, //父窗口句柄
            (HMENU)201,   //为控件指定一个唯一标识符
            hInst,    //当前实例句柄
            NULL);  //不需要指针.  
        //存储句柄
        if (!hwndEdit == NULL)
            CEdit.AddHWND(hwndEdit);
#endif

#ifdef control
        //获取字体
        //HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT); //已创建逻辑字体

        //静态文本
        for (HWND hwndText : CText.hwnds)
        {
            ::SendMessage(hwndText, WM_SETFONT, (WPARAM)hFont, 1);  //设置控件字体
        }
        //按钮
        for (HWND hwndButton : CButton.hwnds)
        {
            ::SendMessage(hwndButton, WM_SETFONT, (WPARAM)hFont, 1);  //设置控件字体
        }
        //编辑框
#ifdef CMD
        for (HWND hwndEdit : CEdit.hwnds)
        {
            ::SendMessage(hwndEdit, WM_SETFONT, (WPARAM)hFont, 1);  //设置控件字体
        }
#endif
#endif
#endif
        return (m_hwnd ? TRUE : FALSE);
    }

    HWND Window() const { return m_hwnd; }
};

class MainWindow : public BaseWindow<MainWindow>
{
public:
    PCWSTR  ClassName() const { return L"ToolsWindow"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    //如果程序正常启动, 获取到程序ID
    //启动时有程序实例, 则退出当前程序, 维持单一程序实例
    if (WindowsSystemOperation::isProgramRunning("Tools.exe"))
    {
#ifdef _DEBUG1
        MessageBox(NULL, L"已有实例正在运行!", L"警告", MB_ICONEXCLAMATION | MB_OK);
        return 0;
#endif
        return 0;
    }


    MainWindow win;
    
    if (!win.Create(ProjectName, WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);

    //打开每日清单.txt 文件
    if (ToolsCfgF.OpenConfigFile())
    {
        SetWindowText(CButton.GetHWND(1), StringHandling::StringToLPCWSTR(ToolsCfgF.vstr[1 - 1] + " x " + ToolsCfgF.vstr[2 - 1]));
        SetWindowText(CButton.GetHWND(2), StringHandling::StringToLPCWSTR(ToolsCfgF.vstr[3 - 1] + " x " + ToolsCfgF.vstr[4 - 1]));

        //修改静态文本
        //SetWindowText(CText.GetHWND(1), L"文件存在, 获取配置成功");

#ifdef test
        SetWindowText(CText.GetHWND(1), ToolsCfgF.sizePath);
        SetWindowText(CText.GetHWND(2), StringHandling::StringToLPCWSTR(ToolsCfgF.ToolsCofigFilePath));
#endif
}

    //HWND tempHwnd = GetTopWindow(NULL);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;

    //定义缓冲区
    TCHAR szText[100];

    //vector<thread> VecButtonThread((int)CButton.GetHWNDS().size());
    //string tamp = ToolsCfgF.vstr[1 - 1].c_str();

    //DWORD dwordTest = NULL;

    switch (uMsg)
    {
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        switch (wmId)
        {
        case 1:
        {
            /*
            VecButtonThread[1] = thread(SetDisplaySize_Run,
                atoi(ToolsCfgF.vstr[1 - 1].c_str()),
                atoi(ToolsCfgF.vstr[2 - 1].c_str())
            );
            VecButtonThread[1].join();
            */
            WindowsSystemOperation::SetDisplaySize_Run(
                atoi(ToolsCfgF.vstr[1 - 1].c_str()),
                atoi(ToolsCfgF.vstr[2 - 1].c_str())
            );

            string tempDPI = ToolsCfgF.vstr[1 - 1] + " x " + ToolsCfgF.vstr[2 - 1];

            //修改静态文本字符
            //默认:
            //当前设置: 1920 x 1080
            SetWindowText(CText.GetHWND(1), hStatic_case["文本-当前设置"]);
            SetWindowText(CButton.GetHWND(1), StringHandling::StringToLPCWSTR(tempDPI));
            //SetWindowText(CButton.GetHWND(1), StringHandling::StringToLPCWSTR(LPCWSTRToString(hStatic_case["文本-当前设置"]) + tempDPI));

            break;
        }
        case 2:
        {
            /*
            VecButtonThread[2] = thread(SetDisplaySize_Run,
                atoi(ToolsCfgF.vstr[3 - 1].c_str()),
                atoi(ToolsCfgF.vstr[4 - 1].c_str())
            );
            VecButtonThread[2].join();
            */
            WindowsSystemOperation::SetDisplaySize_Run(
                atoi(ToolsCfgF.vstr[3 - 1].c_str()),
                atoi(ToolsCfgF.vstr[4 - 1].c_str())
            );

            string tempDPI = (string)ToolsCfgF.vstr[3 - 1] + " x " + ToolsCfgF.vstr[4 - 1];

            //修改静态文本字符
            //默认:
            //当前设置: 1280 x 1024
            SetWindowText(CText.GetHWND(1), hStatic_case["文本-当前设置"]);
            SetWindowText(CButton.GetHWND(2), StringHandling::StringToLPCWSTR(tempDPI));


            break;
        }
        case 3:
        {
            /*
            VecButtonThread[3] = thread(startFile,
                MainWindow::Window(),
                StringHandling::StringToLPCWSTR(ToolsCfgF.vstr[5 - 1])
            );
            VecButtonThread[3].join();
            */
            WindowsSystemOperation::startFile(StringHandling::StringToLPCWSTR(ToolsCfgF.vstr[5 - 1]));

            SetWindowText(CText.GetHWND(1), hStatic_case["文本-启动状态"]);
            SetWindowText(CText.GetHWND(2), hStatic_case["文件状态-已打开"]);
#ifdef test
            //如果程序正常启动, 获取到程序ID
            if (dwordTest = FindProcessIDByName(
                LPCWSTRToString(hStatic_case["文件-steam"])
            ) != NULL)
            {
                //程序 ID不为空时
                //修改静态文本字符
                SetWindowText(CText.GetHWND(1), hStatic_case["文本-启动状态"]);
                SetWindowText(CText.GetHWND(2), hStatic_case["文件状态-已打开"]);

                break;
            }
            else
            {
                //程序 ID为空时
                //修改静态文本字符
                SetWindowText(CText.GetHWND(1), hStatic_case["文本-启动状态"]);
                SetWindowText(CText.GetHWND(2), hStatic_case["文件状态-打开失败"]);

                break;
            }
#endif

            break;
        }
        case 4:
        {
            /*
            VecButtonThread[4] = thread(OpenFolder,
                "C:\\Users\\22793\\Source\\Repos"
            );
            VecButtonThread[4].join();
            */
            OpenFolder(ToolsCfgF.vstr[9 - 1]);

            SetWindowText(CText.GetHWND(1), L"repos...");
            SetWindowText(CText.GetHWND(2), hStatic_case["文件状态-已打开"]);

            /*
            //设置时间
            TimeDate TimeDate;
            TimeDate.Run();

            break;
            SetWindowText(CText.GetHWND(2), TimeDate.wStr);
            */

            break;
        }
        case 5:
        {
            //打开文件
            //ShellExecute(this->m_hwnd, "open", ToolsCfgF.ToolsCofigFilePath, NULL, NULL, SW_SHOW);

            //OpenDailyList() 中已包含 startFile()
            //startFile(MainWindow::Window(), StringHandling::StringToLPCWSTR(ToolsCfgF.vstr[6 - 1])); 

            //修改静态文本字符
            SetWindowText(CText.GetHWND(1), hStatic_case["文本-每日清单配置"]);
            SetWindowText(CText.GetHWND(2), hStatic_case["文件状态-已打开"]);

            //打开 DailyList.txt 文件
            ToolsCfgF.OpenDailyList(true);

            break;
        }
        case 6:
        {
            //修改静态文本字符
            SetWindowText(CText.GetHWND(1), hStatic_case["文本-工具箱设置"]);
            SetWindowText(CText.GetHWND(2), hStatic_case["文件状态-已打开"]);

            //打开 ToolsConfig.ini 文件
            ToolsCfgF.OpenConfigFile(true);

            break;
        }
        case 7:
        {
            //修改静态文本字符
            SetWindowText(CText.GetHWND(1), hStatic_case["文本-工具箱设置"]);
            SetWindowText(CText.GetHWND(2), hStatic_case["文件状态-已打开"]);

            //启动雷神加速器
            WindowsSystemOperation::startFile(StringHandling::StringToLPCWSTR(ToolsCfgF.vstr[8 - 1]));

            break;
        }
#ifdef CMD
        case 8:
        {
            //CEdit 获取 字符
            GetWindowText(CEdit.GetHWND(1), szText, 100);
            string tempStr = TCHARToString(szText);
            
            system(tempStr.c_str());
            //修改静态文本字符
            SetWindowText(CText.GetHWND(1), TEXT("cmd..."));
        }
#endif
        case 9:
        {
#ifdef old
            //关闭
            LPCWSTR tempStrDisabled = L"sc config i8042prt start= disabled";
            //开启
            LPCWSTR tempStrAuto = L"sc config i8042prt start= auto";

            //PVOID oldValue = NULL; //应用重定向
            //tempStrDisabled = tempStrDisabled + " >> " + ToolsCfgF.vstr[7 - 1];
            //tempStrAuto = tempStrAuto + " >> " + ToolsCfgF.vstr[7 - 1];

            if (NoteBookState) //开启时，关闭
            {
                /*
                if (Wow64DisableWow64FsRedirection(&oldValue))
                {
                    //ShellExecute(NULL, "runas", "cmd", "/c winsat disk >> D:\\disk.txt", NULL, SW_SHOWNORMAL);
                    //执行cmd命令
                    SHELLEXECUTEINFO ShExecInfo = { 0 };
                    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
                    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
                    ShExecInfo.hwnd = NULL;
                    ShExecInfo.lpVerb = L"runas";
                    ShExecInfo.lpFile = L"cmd";
                    ShExecInfo.lpParameters = StringHandling::StringToLPCWSTR(tempStrDisabled);
                    ShExecInfo.lpDirectory = NULL;
                    ShExecInfo.nShow = SW_SHOWNORMAL;
                    ShExecInfo.hInstApp = NULL;
                    ShellExecuteEx(&ShExecInfo);
                    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
                }
                Wow64RevertWow64FsRedirection(oldValue); //开启重定向
                */

                ShellExecute(NULL, L"runas", L"cmd", tempStrDisabled, NULL, SW_SHOWNORMAL);
                NoteBookState = false;
                //修改静态文本字符
                SetWindowText(CButton.GetHWND(9), TEXT("键盘已关闭"));
            }
            else //关闭时，开启
            {
                /*
                if (Wow64DisableWow64FsRedirection(&oldValue))
                {
                    //ShellExecute(NULL, "runas", "cmd", "/c winsat disk >> D:\\disk.txt", NULL, SW_SHOWNORMAL);
                    //执行cmd命令
                    SHELLEXECUTEINFO ShExecInfo = { 0 };
                    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
                    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
                    ShExecInfo.hwnd = NULL;
                    ShExecInfo.lpVerb = L"runas";
                    ShExecInfo.lpFile = L"cmd";
                    ShExecInfo.lpParameters = StringHandling::StringToLPCWSTR(tempStrAuto);
                    ShExecInfo.lpDirectory = NULL;
                    ShExecInfo.nShow = SW_SHOWNORMAL;
                    ShExecInfo.hInstApp = NULL;
                    ShellExecuteEx(&ShExecInfo);
                    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
                }
                Wow64RevertWow64FsRedirection(oldValue); //开启重定向
                */

                ShellExecute(NULL, L"runas", L"cmd", tempStrAuto, NULL, SW_SHOWNORMAL);
                NoteBookState = true;
                //修改静态文本字符
                SetWindowText(CButton.GetHWND(9), TEXT("键盘已开启"));
#endif
                //修改静态文本字符
                //SetWindowText(CText.GetHWND(1), TEXT("键盘当前状态："));

                //没写修改配置文件中的设置属性
                if (NoteKeyboardState) //笔记本状态: 开
                {

                    //设置为: 关
                    //L"runas"
                    //ShellExecute(NULL, L"runas", StringHandling::StringToLPCWSTR(ToolsCfgF.vstr[10 - 1]), NULL, NULL, SW_SHOWNORMAL);
                    ShellExecute(NULL, L"runas", L"C:\\NoteKeyboardState\\NoteKeyboardOff.bat - 快捷方式", NULL, NULL, SW_SHOWNORMAL);
                    
                    //修改静态文本字符
                    //SetWindowText(CText.GetHWND(2), TEXT("键盘已关闭"));

                    NoteKeyboardState = false;
                }
                else //笔记本状态: 关
                {
                    //设置为: 开
                    //ShellExecute(NULL, L"runas", StringHandling::StringToLPCWSTR(ToolsCfgF.vstr[11 - 1]), NULL, NULL, SW_SHOWNORMAL);
                    ShellExecute(NULL, L"runas", L"C:\\NoteKeyboardState\\NoteKeyboardOn.bat - 快捷方式", NULL, NULL, SW_SHOWNORMAL);

                    //修改静态文本字符
                    //SetWindowText(CText.GetHWND(2), TEXT("键盘已开启"));

                    NoteKeyboardState = true;
                }
        }

        default:
            return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        }

        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            EndPaint(m_hwnd, &ps);
        }
        return 0;
    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
};