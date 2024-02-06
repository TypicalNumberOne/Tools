#if 0
#include <windows.h>
#include <stdio.h>//printf
#include <string>
using namespace std;//注意一定要写这句

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    bool can_close=false;//程序退出前能否退出标志
    static int cxClient,cyClient;
    HDC hdc;
    PAINTSTRUCT ps ;    
    switch (message)
    {
        case WM_CREATE://    0x0001    应用程序创建一个窗口
        {
            printf("句柄：%d,窗口正在创建中.....！\n",hwnd);
            break;
        }

        case WM_PAINT://    0x000F    要求一个窗口重绘自己
        {
        
            EndPaint (hwnd, &ps) ;
            hdc=BeginPaint(hwnd,&ps);    //获取要重画的窗口的设备描述表句柄            
                //在这里画上你想画的内容 
                string temp;//引用#include <string>
                temp="哈哈，这是想要显示的内容！";
                TextOut(hdc,10,10,temp.c_str(),temp.size());
            EndPaint(hwnd,&ps);        //结束重画
            return 0;
        }
        case WM_CONTEXTMENU://右键菜单//cd
        {
                    //Win32创建弹出菜单
                        POINT point;
                        ::GetCursorPos(&point);//得到鼠标的当前位置
                        HMENU hMenuPopup = CreatePopupMenu () ;
                            HMENU hMenuPopup1 = CreatePopupMenu () ;
                            AppendMenu(hMenuPopup1, MF_STRING, 101, "MF_STRING");
                            AppendMenu(hMenuPopup1, MF_SEPARATOR, 0, NULL) ;
                            AppendMenu(hMenuPopup1, MF_CHECKED, 102, "MF_CHECKED");
                        
                        AppendMenu(hMenuPopup, MF_STRING, 1, "MF_STRING");
                        AppendMenu(hMenuPopup, MF_SEPARATOR, 0, NULL) ;
                        AppendMenu(hMenuPopup, MF_CHECKED, 2, "MF_CHECKED");
                        AppendMenu(hMenuPopup, MF_DISABLED, 3, "MF_DISABLED");
                        AppendMenu(hMenuPopup, MF_ENABLED, 4, "MF_ENABLED");
                        AppendMenu(hMenuPopup, MF_GRAYED, 5, "MF_GRAYED");
                        AppendMenu(hMenuPopup, MF_MENUBARBREAK, 6, "MF_MENUBARBREAK");
                        AppendMenu(hMenuPopup, MF_STRING, 7, "MF_STRING");
                        AppendMenu(hMenuPopup, MF_STRING, 8, "MF_STRING");
                        AppendMenu(hMenuPopup, MF_MENUBREAK, 9, "MF_MENUBREAK");
                        AppendMenu(hMenuPopup, MF_POPUP,(LONG)hMenuPopup1, "MF_POPUP");
                        

                        TrackPopupMenu (hMenuPopup, TPM_RIGHTBUTTON, point.x, point.y, 0, hwnd, NULL) ;
                        DestroyMenu (hMenuPopup1);
                        DestroyMenu (hMenuPopup);
                    return 0;
        }        
        case WM_SYSCOMMAND://    0x0112    选择窗口菜单项或选择最大化或最小化时，发送此消息给该窗口
        {
            switch(wParam)
            {
                case SC_MINIMIZE://　　最小化窗口
                {
                    printf("句柄：%d,窗口已被最小化！\n",hwnd);
                    break;//交由系统处理该条消息
                    //return 0;//如果不想被最小化，则直接return 0; 告诉系统该条消息已被处理
                }
                case SC_MAXIMIZE://最大化窗口
                {
                    printf("句柄：%d,窗口已被最大化！\n",hwnd);
                    break;//交由系统处理该条消息
                    //return 0;//如果不想被最小化，则直接return 0; 告诉系统该条消息已被处理
                }                
            }
            break;
        }
        
        case WM_SIZE://窗口尺寸发生改变
        {
            cxClient = LOWORD (lParam) ; //得到客户区宽度
            cyClient = HIWORD (lParam) ; //得到客户区高度
            printf("句柄：%d,当前窗口宽和度:%d,%d\n",hwnd,cxClient,cyClient);
            return 0;
        }
        
        //击键消息
        case WM_KEYDOWN://按下键
        {
            printf("句柄：%d,按下的键值:%d\n",hwnd,wParam);//需引用库文件：#include <stdio.h>
            if (GetAsyncKeyState(VK_CONTROL)&& wParam ==72)//CTRL+h 
                printf("你同时按下CTRL+H键\n");
            break;
        }
        case WM_KEYUP://弹起键
        {
            printf("句柄：%d,弹起的键值:%d\n",hwnd,wParam);//需引用库文件：#include <stdio.h>
            break;
        }
        case WM_CHAR:
        {
            printf("句柄：%d,键ASCII码:%d\n",hwnd,wParam);
            break;
        }
        //鼠标消息
        case WM_LBUTTONDBLCLK://    0x0203    双击鼠标左键 在注册窗口类的时候在WNDCLASS的style成员加上CS_DBLCLKS风格
        {
            POINT p;
            p.x=LOWORD(lParam);
            p.y=HIWORD(lParam);
            printf("句柄：%d,双击鼠标左键:%d，%d\n",hwnd,p.x,p.y);
            break;            
        }            
        case WM_LBUTTONDOWN://按下鼠标左键
        {
            POINT p;
            p.x=LOWORD(lParam);
            p.y=HIWORD(lParam);
            printf("句柄：%d,按下鼠标左键:%d，%d\n",hwnd,p.x,p.y);
            break;
        }
        case WM_LBUTTONUP://弹起鼠标左键
        {
            POINT p;
            p.x=LOWORD(lParam);
            p.y=HIWORD(lParam);
            printf("句柄：%d,弹起鼠标左键:%d，%d\n",hwnd,p.x,p.y);
            break;
        }    
        case WM_RBUTTONDBLCLK://    0x0206    双击鼠标右键
        {
            POINT p;
            p.x=LOWORD(lParam);
            p.y=HIWORD(lParam);
            printf("句柄：%d,双击鼠标右键:%d，%d\n",hwnd,p.x,p.y);
            break;            
        }
        case WM_RBUTTONDOWN://按下鼠标右键
        {
            POINT p;
            p.x=LOWORD(lParam);
            p.y=HIWORD(lParam);
            printf("句柄：%d,按下鼠标右键:%d，%d\n",hwnd,p.x,p.y);
            break;
        }
        case WM_RBUTTONUP://弹起鼠标右键
        {
            POINT p;
            p.x=LOWORD(lParam);
            p.y=HIWORD(lParam);
            printf("句柄：%d,弹起鼠标右键:%d，%d\n",hwnd,p.x,p.y);
            break;
        }        
        case WM_MBUTTONDBLCLK://    0x0206    双击鼠标中键
        {
            POINT p;
            p.x=LOWORD(lParam);
            p.y=HIWORD(lParam);
            printf("句柄：%d,双击鼠标中键:%d，%d\n",hwnd,p.x,p.y);
            break;            
        }
        case WM_MBUTTONDOWN://按下鼠标中键
        {
            POINT p;
            p.x=LOWORD(lParam);
            p.y=HIWORD(lParam);
            printf("句柄：%d,按下鼠标中键:%d，%d\n",hwnd,p.x,p.y);
            break;
        }
        case WM_MBUTTONUP://弹起鼠标中键
        {
            POINT p;
            p.x=LOWORD(lParam);
            p.y=HIWORD(lParam);
            printf("句柄：%d,弹起鼠标中键:%d，%d\n",hwnd,p.x,p.y);
            break;
        }    
        case WM_MOUSEMOVE://正在移动鼠标
        {
            POINT p;
            p.x=LOWORD(lParam);
            p.y=HIWORD(lParam);
            printf("句柄：%d,正在移动鼠标:%d，%d\n",hwnd,p.x,p.y);        
            break;
        }
//win32应用程序的完整退出过程：点击窗口右上角的关闭按钮，发送WM_CLOSE消息。此消息处理中调用DestroyWindow函数，发送WM_DESTROY消息。此消息处理中调用PostQuitMessage(0)函数，发送WM_QUIT消息到消息队列中。GetMessage捕获到WM_QUIT，返回0，退出循环(应用程序真正退出)。        
        case WM_CLOSE://关闭应用程序窗口
        {
            if (MessageBox(hwnd, "真的要退出吗？", "提示", MB_YESNO|MB_ICONQUESTION)==IDYES)//关闭程序前询问是否真的要退出
            {
                can_close=true;
            }else
            {
                can_close=false;
            }
        }
        case WM_DESTROY://关闭应用程序
        {
            if (can_close)//如果允许关闭，则发送关闭消息
                PostQuitMessage (0) ;
            return 0 ;
        }
        case WM_QUIT://关闭消息循环
        {
            //按照上述正常流程，WM_QUIT是不会到达窗口过程的。(因为在GetMessage截获了WM_QUIT消息之后，程序已经彻底退出了！)
            MessageBox(hwnd,"我要关闭消息循环啦！","提示",0);
            return 0;
        }
    }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR szCmdLine, int iCmdShow)
{
    static char szAppName[] = "HelloWin" ;
    HWND   hwnd ;
    MSG    msg ;
    WNDCLASS wndclass ;

    wndclass.style        = CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS ;
    wndclass.cbClsExtra   = 0 ;
    wndclass.cbWndExtra   = 0 ;
    wndclass.hInstance    = hInstance ;
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION) ;
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName= szAppName ;
    wndclass.lpfnWndProc  = WndProc ;
    if (!RegisterClass (&wndclass))
    {
            MessageBox (  NULL, TEXT ("This program requires Windows NT!"),
                                  szAppName, MB_ICONERROR) ;
            return 0 ;
    }
        
    hwnd = CreateWindow( szAppName,              // window class name
                        "窗口消息演示",       // window caption
                        //WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX, //正常窗口显示
                        //WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX, //只显示标题文字菜单、关闭、最小化按钮
                        //WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU, //只显示标题文字菜单、关闭按钮
                        //WS_OVERLAPPED, //只显示标题文字，不显示其他按钮
                        //WS_OVERLAPPEDWINDOW&~WS_CAPTION, //正常窗口显示
                        //WS_OVERLAPPEDWINDOW&~WS_THICKFRAME, //正常窗口显示
                        //WS_OVERLAPPEDWINDOW&~WS_SYSMENU, //只显示标题文字，不显示其他按钮
                        //WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX, //去掉最大最小化窗口 
                        WS_OVERLAPPEDWINDOW,  //正常窗口显示  
                        //WS_POPUP, //无边框无标题窗口
                        CW_USEDEFAULT,            // initial x position
                        CW_USEDEFAULT,            // initial y position
                        CW_USEDEFAULT,            // initial x size
                        CW_USEDEFAULT,            // initial y size
                        NULL,                     // parent window handle
                        NULL,                    // window menu handle
                        hInstance,               // program instance handle
                        NULL) ;                  // creation parameters
        
    ShowWindow (hwnd, iCmdShow) ;
    UpdateWindow (hwnd) ;
        
    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }
        
    return msg.wParam ;
}
        
        
        
/*
Windows 常用消息及含义


消息范围    说明
0 ～ WM_USER – 1    系统消息
WM_USER ～ 0x7FFF    自定义窗口类整数消息
WM_APP ～ 0xBFFF    应用程序自定义消息
0xC000 ～ 0xFFFF    应用程序字符串消息
> 0xFFFF    为以后系统应用保留


消息名称
值
含义
WM_NULL    0x0000    空消息，此消息将被接收窗口忽略
WM_CREATE    0x0001    应用程序创建一个窗口
WM_DESTROY    0x0002    一个窗口被销毁
WM_MOVE    0x0003    移动一个窗口
WM_SIZE    0x0005    改变一个窗口的大小
WM_ACTIVATE    0x0006    一个窗口被激活或失去激活状态
WM_SETFOCUS    0x0007    获得焦点后
WM_KILLFOCUS    0x0008    失去焦点
WM_ENABLE    0x000A    应用程序 Enable 状态改变时产生
WM_SETREDRAW    0x000B    设置窗口是否能重画
WM_SETTEXT    0x000C    应用程序发送此消息来设置一个窗口的文本
WM_GETTEXT    0x000D    应用程序发送此消息来复制对应窗口的文本到缓冲区
WM_GETTEXTLENGTH    0x000E    得到与一个窗口有关的文本的长度（不包含空字符）
WM_PAINT    0x000F    要求一个窗口重绘自己
WM_CLOSE    0x0010    当一个窗口或应用程序要关闭时发送一个信号
WM_QUERYENDSESSION    0x0011    用户选择结束对话框或应用程序自己调用 ExitWindows 函数
WM_QUIT    0x0012    用来结束程序运行或应用程序调用 Postquitmessage 函数来产生此消息
WM_QUERYOPEN    0x0013    当用户窗口恢复以前的大小位置时，把此消息发送给某个图标
WM_ERASEBKGND    0x0014    当窗口背景必须被擦除时（例如在窗口改变大小时）
WM_SYSCOLORCHANGE    0x0015    当系统颜色改变时，发送此消息给所有顶级窗口
WM_ENDSESSION    0x0016    当系统进程发出 WM_QUERYENDSESSION 消息后，此消息发送给应用程序
WM_SHOWWINDOW    0x0018    当隐藏或显示窗口是发送此消息给这个窗口
WM_ACTIVATEAPP    0x001C    当某个窗口将被激活时，将被激活窗口和当前活动（即将失去激活）窗口会收到此消息，发此消息给应用程序哪个窗口是激活的，哪个是非激活的
WM_FONTCHANGE    0x001D    当系统的字体资源库变化时发送此消息给所有顶级窗口
WM_TIMECHANGE    0x001E    当系统的时间变化时发送此消息给所有顶级窗口
WM_CANCELMODE    0x001F    发送此消息来取消某种正在进行的操作
WM_SETCURSOR    0x0020    如果鼠标引起光标在某个窗口中移动且鼠标输入没有被捕获时，发消息给该窗口
WM_MOUSEACTIVATE    0x0021    当光标在某个非激活的窗口中而用户正按着鼠标的某个键发送此消息给当前窗口
WM_CHILDACTIVATE    0x0022    发送此消息给 MDI 子窗口当用户点击此窗口的标题栏，或当窗口被激活、移动、改变大小
WM_QUEUESYNC    0x0023    此消息由基于计算机的训练程序发送，通过 WH_JOURNALPALYBACK 的 Hook 程序分离出用户输入消息
WM_GETMINMAXINFO    0x0024    当窗口要将要改变大小或位置时，发送此消息给该窗口
WM_PAINTICON    0x0026    当窗口图标将要被重绘时，发送此消息给该窗口
WM_ICONERASEBKGND    0x0027    在一个最小化窗口的图标在重绘前，当图标背景必须被重绘时，发送此消息给该窗口
WM_NEXTDLGCTL    0x0028    发送此消息给一个对话框程序以更改焦点位置
WM_SPOOLERSTATUS    0x002A    当打印管理列队增加或减少一条作业时发出此消息
WM_DRAWITEM    0x002B    当 Button，ComboBox，Listbox，Menu 控件的外观改变时，发送此消息给这些控件的所有者
WM_MEASUREITEM    0x002C    当 Button，ComboBox，list box，ListView，Menu 项被创建时，发送此消息给控件的所有者
WM_DELETEITEM    0x002D    当 ListBox 或 ComboBox 被销毁或当某些项通过发送 LB_DELETESTRING、LB_RESETCONTENT、  CB_DELETESTRING、CB_RESETCONTENT 消息被删除时，发送此消息给控件的所有者
WM_VKEYTOITEM    0x002E    一个具有 LBS_WANTKEYBOARDINPUT 风格的 ListBox 控件发送此消息给它的所有者，以此来响应 WM_KEYDOWN 消息
WM_CHARTOITEM    0x002F    一个具有 LBS_WANTKEYBOARDINPUT 风格的 ListBox 控件发送此消息给它的所有者，以此来响应 WM_CHAR 消息
WM_SETFONT    0x0030    应用程序绘制控件时，发送此消息得到以何种字体绘制控件中的文本
WM_GETFONT    0x0031    应用程序发送此消息得到当前控件绘制文本的字体
WM_SETHOTKEY    0x0032    应用程序发送此消息让一个窗口与一个热键相关联
WM_GETHOTKEY    0x0033    应用程序发送此消息来判断热键与某个窗口是否有关联
WM_QUERYDRAGICON    0x0037    此消息发送给最小化窗口，当此窗口将要被拖放而它的类中没有定义图标，应用程序就返回一个图标或光标的句柄，当用户拖放图标时系统显示这个图标或光标
WM_COMPAREITEM    0x0039    发送此消息来判定 ComboBox 或 ListBox 新增加的项的相对位置
WM_COMPACTING    0x0041    显示内存已经很少了
WM_WINDOWPOSCHANGING    0x0046    当调用 SetWindowPos 函数改变窗口的大小和位置后，发送此消息给该窗口
WM_POWER    0x0048    当系统将进入挂起状态时发送此消息给所有进程
WM_COPYDATA    0x004A    当一个应用程序传递数据给另一个应用程序时发送此消息
WM_CANCELJOURNAL    0x004B    当某个用户取消程序日志激活状态，发送此消息给应用程序
WM_NOTIFY    0x004E    当某个控件的某个事件已经发生或这个控件需要得到一些信息时，发送此消息给它的父窗口
WM_INPUTLANGCHANGEREQUEST    0x0050    当用户选择某种输入语言，或输入语言的热键改变
WM_INPUTLANGCHANGE    0x0051    当应用程序输入语言改变后发送此消息给受影响的最顶级窗口
WM_TCARD    0x0052    当应用程序已经初始化 Windows 帮助例程时发送此消息给应用程序
WM_HELP    0x0053    当用户按下了 F1，如果某个菜单是激活的，就发送此消息给此窗口关联的菜单，否则就发送给有焦点的窗口，如果当前都没有焦点，就把此消息发送给当前激活的窗口
WM_USERCHANGED    0x0054    当用户已经登录或退出后发送此消息给所有的窗口，当用户登录或退出时系统更新用户的具体设置信息，在用户更新设置时系统马上发送此消息
WM_NOTIFYFORMAT    0x0055    公用控件和它们的父窗口通过此消息来判断在 WM_NOTIFY 消息中是使用 ANSI 还是 UNICODE 形式的结构，使用此控件能使某个控件与它的父控件进行相互通信
WM_CONTEXTMENU    0x007B    当用户在某个窗口中点击右键，则发送此消息给该窗口
WM_STYLECHANGING    0x007C    当将要调用 SetWindowLong 函数窗口的一个或多个风格时，发送此消息给该窗口
WM_STYLECHANGED    0x007D    当调用 SetWindowLong 函数改变了窗口的一个或多个风格后，发送此消息给该窗口
WM_DISPLAYCHANGE    0x007E    当显示器的分辨率改变后发送此消息给所有的窗口
WM_GETICON    0x007F    发送此消息给某个窗口，返回与某个窗口有关联的大图标或小图标的句柄
WM_SETICON    0x0080    应用程序发送此消息让一个新的大图标或小图标与某个窗口关联
WM_NCCREATE    0x0081    当某个窗口第一次被创建时，此消息在 WM_CREATE 消息被发送前发送
WM_NCDESTROY    0x0082    此消息通知某个窗口，正在销毁非客户区
WM_NCCALCSIZE    0x0083    当计算某个窗口的客户区大小和位置时发送此消息
WM_NCHITTEST    0x0084    移动鼠标，按住或释放鼠标时产生此消息
WM_NCPAINT    0x0085    当某个窗口的框架必须被绘制时，应用程序发送此消息给该窗口
WM_NCACTIVATE    0x0086    通过改变某个窗口的非客户区来表示窗口是处于激活还是非激活状态时，此消息被发送给该窗口
WM_NCMOUSEMOVE    0x00A0    当光标在窗口的非客户区（窗口标题栏及边框）内移动时发送此消息给该窗口
WM_NCLBUTTONDOWN    0x00A1    当光标在窗口的非客户区并按下鼠标左键时发送此消息
WM_NCLBUTTONUP    0x00A2    当光标在窗口的非客户区并释放鼠标左键时发送此消息
WM_NCLBUTTONDBLCLK    0x00A3    当光标在窗口的非客户区并双击鼠标左键时发送此消息
WM_NCRBUTTONDOWN    0x00A4    当光标在窗口的非客户区并按下鼠标右键时发送此消息
WM_NCRBUTTONUP    0x00A5    当光标在窗口的非客户区并释放鼠标右键时发送此消息
WM_NCRBUTTONDBLCLK    0x00A6    当光标在窗口的非客户区并双击鼠标右键时发送此消息
WM_NCMBUTTONDOWN    0x00A7    当光标在窗口的非客户区并按下鼠标中键时发送此消息
WM_NCMBUTTONUP    0x00A8    当光标在窗口的非客户区并释放鼠标中键时发送此消息
WM_NCMBUTTONDBLCL    0x00A9    当光标在窗口的非客户区并双击鼠标中键时发送此消息
WM_KEYDOWN    0x0100    按下一个非系统键（按下键时未按下“ALT”键）
WM_KEYUP    0x0101    释放一个非系统键
WM_CHAR    0x0102    按下某键，当 TranslateMessage 转发 WM_KEYDOWN 后发送本消息
WM_DEADCHAR    0x0103    释放某键，当 TranslateMessage 转发 WM_KEYUP 后发送本消息
WM_SYSKEYDOWN    0x0104    当按住 ALT 键同时按下其他键时发送此消息给拥有键盘焦点的窗口
WM_SYSKEYUP    0x0105    当释放一个键同时按住 ALT 键时发送此消息给拥有键盘焦点的窗口
WM_SYSCHAR    0x0106    当 TranslateMessage 函数转发 WM_SYSKEYDOWN 后发送此消息给拥有键盘焦点的窗口
WM_SYSDEADCHAR    0x0107    当 TranslateMessage 函数转发 WM_SYSKEYUP 后发送此消息给拥有键盘焦点的窗口
WM_INITDIALOG    0x0110    在被显示前发送此消息对话框，通常用此消息初始化控件和执行其他任务
WM_COMMAND    0x0111    选择窗口菜单项或某个控件发送一条消息给它的父窗口或按下一个快捷键时产生此消息
WM_SYSCOMMAND    0x0112    选择窗口菜单项或选择最大化或最小化时，发送此消息给该窗口
WM_TIMER    0x0113    发生了定时器事件
WM_HSCROLL    0x0114    当窗口水平滚动条产生一个滚动事件时发送此消息给该窗口和滚动条的所有者
WM_VSCROLL    0x0115    当窗口垂直滚动条产生一个滚动事件时发送此消息给该窗口和滚动条的所有者
WM_INITMENU    0x0116    当一个菜单将要被激活时发送此消息，它发生在按下菜单项或按下菜单快捷键时，它允许程序在显示前更改菜单
WM_INITMENUPOPUP    0x0117    当一个下拉菜单或子菜单将要被激活时发送此消息，它允许显示前在修改菜单而不必更改整个菜单
WM_MENUSELECT    0x011F    选择一条菜单项时发送此消息给菜单的所有者（一般是窗口）
WM_MENUCHAR    0x0120    当菜单已被激活且用户按下了某个键（非快捷键），发送此消息给菜单的所有者
WM_ENTERIDLE    0x0121    当一个有模式对话框或菜单进入空闲状态时发送此消息给它的所有者，空闲状态指在处理完一条或几条先前的消息后，消息列队为空
WM_MENURBUTTONUP    0x0122    当光标位于菜单项上时，释放鼠标右键产生此消息
WM_MENUDRAG    0x0123    当拖动菜单项时，发送此消息给拖放菜单的所有者
WM_MENUGETOBJECT    0x0124    当光标移入菜单项或者从菜单项中心移到菜单项顶部或底部时，发送此消息给拖放菜单的所有者
WM_UNINITMENUPOPUP    0x0125    当下拉菜单或者子菜单被销毁时产生此消息
WM_MENUCOMMAND    0x0126    当用户选择菜单项时产生此消息
WM_CHANGEUISTATE    0x0127    应用程序发送此消息表明用户界面（UI）状态应当被改变
WM_UPDATEUISTATE    0x0128    应用程序发送此消息改变指定窗口及其子窗口的用户界面（UI）状态
WM_QUERYUISTATE    0x0129    应用程序发送此消息得到某个窗口的用户界面（UI）状态
WM_CTLCOLORMSGBOX    0x0132    绘制消息框前发送此消息给它的父窗口，通过响应这条消息，父窗口可以通过使用给定的相关显示设备的句柄来设置消息框的文本和背景颜色
WM_CTLCOLOREDIT    0x0133    绘制编辑型控件前发送此消息给它的父窗口，可用来设置编辑框的文本和背景颜色
WM_CTLCOLORLISTBOX    0x0134    绘制列表框控件前发送此消息给它的父窗口，可用来设置编辑框的文本和背景颜色
WM_CTLCOLORBTN    0x0135    绘制按钮控件前发送此消息给它的父窗口，可用来设置编辑框的文本和背景颜色
WM_CTLCOLORDLG    0x0136    绘制对话框前发送此消息给它的父窗口，可用来设置编辑框的文本和背景颜色
WM_CTLCOLORSCROLLBAR    0x0137    绘制滚动条控件前发送此消息给它的父窗口，可用来设置滚动条控件的文本和背景颜色
WM_CTLCOLORSTATIC    0x0138    绘制静态控件前发送此消息给它的父窗口，可用来设置静态控件的文本和背景颜色
WM_MOUSEMOVE    0x0200    鼠标移动
WM_LBUTTONDOWN    0x0201    按下鼠标左键
WM_LBUTTONUP    0x0202    释放鼠标左键
WM_LBUTTONDBLCLK    0x0203    双击鼠标左键
WM_RBUTTONDOWN    0x0204    按下鼠标右键
WM_RBUTTONUP    0x0205    释放鼠标右键
WM_RBUTTONDBLCLK    0x0206    双击鼠标右键
WM_MBUTTONDOWN    0x0207    按下鼠标中键
WM_MBUTTONUP    0x0208    释放鼠标中键
WM_MBUTTONDBLCLK    0x0209    双击鼠标中键
WM_MOUSEWHEEL    0x020A    当鼠标滚轮转动时发送此消息给当前获得焦点的窗口
WM_PARENTNOTIFY    0x0210    当MDI子窗口被创建或被销毁，或当光标位于子窗口上且用户按了一下鼠标键时，发送此消息给它的父窗口
WM_ENTERMENULOOP    0x0211    发送此消息通知应用程序的主窗口进程已经进入了菜单模式循环
WM_EXITMENULOOP    0x0212    发送此消息通知应用程序的主窗口进程已经退出了菜单模式循环
WM_SIZING    0x0214    调整窗口大小时发送此消息给窗口，通过此消息应用程序可以监视或修改窗口大小和位置
WM_CAPTURECHANGED    0x0215    当窗口设定为不捕获鼠标事件时，发送此消息给该窗口
WM_MOVING    0x0216    移动窗口时发送此消息给窗口，通过此消息应用程序可以监视或修改窗口大小和位置
WM_POWERBROADCAST    0x0218    发送此消息给应用程序通知它有关电源管理事件
WM_DEVICECHANGE    0x0219    当设备的硬件配置改变时发送此消息给应用程序或设备驱动程序
WM_MDICREATE    0x0220    应用程序发送此消息给多文档的客户窗口来创建一个MDI 子窗口
WM_MDIDESTROY    0x0221    应用程序发送此消息给多文档的客户窗口来关闭一个MDI 子窗口
WM_MDIACTIVATE    0x0222    应用程序发送此消息给多文档的客户窗口通知客户窗口激活另一个MDI子窗口，当客户窗口收到此消息后，它发出WM_MDIACTIVE消息给MDI子窗口（未激活）来激活它
WM_MDIRESTORE    0x0223    应用程序发送此消息给 MDI 客户窗口通知子窗口恢复到原来大小
WM_MDINEXT    0x0224    应用程序发送此消息给 MDI 客户窗口激活下一个或前一个窗口
WM_MDIMAXIMIZE    0x0225    应用程序发送此消息给 MDI 客户窗口以最大化一个 MDI 子窗口
WM_MDITILE    0x0226    应用程序发送此消息给 MDI 客户窗口以平铺方式重新排列所有 MDI 子窗口
WM_MDICASCADE    0x0227    应用程序发送此消息给 MDI 客户窗口以层叠方式重新排列所有 MDI 子窗口
WM_MDIICONARRANGE    0x0228    应用程序发送此消息给 MDI 客户窗口重新排列所有最小化的 MDI 子窗口
WM_MDIGETACTIVE    0x0229    应用程序发送此消息给 MDI 客户窗口以找到激活的子窗口的句柄
WM_MDISETMENU    0x0230    应用程序发送此消息给 MDI 客户窗口用 MDI 菜单代替子窗口的菜单
WM_ENTERSIZEMOVE    0x0231    当窗口进入移动或改变大小模式循环时，发送此消息给该窗口
WM_EXITSIZEMOVE    0x0232    当窗口退出移动或改变大小模式循环时，发送此消息给该窗口
WM_DROPFILES    0x0233    当用户在应用程序窗口中拖动某个文件时，产生此消息
WM_MDIREFRESHMENU    0x0234    应用程序发送此消息给 MDI 客户窗口以刷新窗口菜单
WM_MOUSEHOVER    0x02A1    当光标在窗口客户区悬停超过 TrackMouseEvent 函数指定的时间时，发送此消息给该窗口
WM_MOUSELEAVE    0x02A3    当光标离开窗口客户区超过 TrackMouseEvent 函数指定的时间时，发送此消息给该窗口
WM_CUT    0x0300    应用程序发送此消息给一个编辑框或 ComboBox 以删除当前选择的文本
WM_COPY    0x0301    应用程序发送此消息给一个编辑框或 ComboBox 以复制当前选择的文本到剪贴板
WM_PASTE    0x0302    应用程序发送此消息给一个编辑框或 ComboBox 以从剪贴板中得到数据
WM_CLEAR    0x0303    应用程序发送此消息给一个编辑框或 ComboBox 以清除当前选择的内容
WM_UNDO    0x0304    应用程序发送此消息给一个编辑框或 ComboBox 以撤消最后一次操作
WM_DESTROYCLIPBOARD    0x0307    当调用 EmptyClipboard 函数清空剪贴板时，发送此消息给剪贴板所有者
WM_DRAWCLIPBOARD    0x0308    当剪贴板的内容变化时发送此消息给剪贴板观察链中的第一个窗口，它允许用剪贴板观察窗口来显示剪贴板的新内容
WM_PAINTCLIPBOARD    0x0309    当剪贴板包含 CF_OWNERDIPLAY 格式的数据且剪贴板观察窗口的客户区需要重绘时，发送此消息给剪贴板所有者
WM_VSCROLLCLIPBOARD    0x030A    当剪贴板包含 CF_OWNERDIPLAY 格式的数据且剪贴板观察窗口发生垂直滚动条事件时，剪贴板观察窗口发送此消息给剪贴板所有者
WM_SIZECLIPBOARD    0x030B    当剪贴板包含 CF_OWNERDIPLAY 格式的数据且剪贴板观察窗口的客户区域的大小已经改变时，剪贴板观察窗口发送此消息给剪贴板的所有者
WM_ASKCBFORMATNAME    0x030C    剪贴板观察窗口发送此消息给剪贴板所有者以获得 CF_OWNERDISPLAY 剪贴板格式的名字
WM_CHANGECBCHAIN    0x030D    当一个窗口从剪贴板观察链中移去时发送此消息给剪贴板观察链中的第一个窗口
WM_HSCROLLCLIPBOARD    0x030E    当剪贴板包含 CF_OWNERDIPLAY 格式的数据且剪贴板观察窗口发生水平滚动条事件时，剪贴板观察窗口发送此消息给剪贴板所有者
WM_QUERYNEWPALETTE    0x030F    发送此消息给将要获得键盘焦点的窗口，此消息使窗口在获得焦点时同时有机会实现它的逻辑调色板
WM_PALETTEISCHANGING    0x0310    应用程序将要实现它的逻辑调色板时发送此消息通知所有应用程序
WM_PALETTECHANGED    0x0311    获得焦点的窗口实现它的逻辑调色板后发送此消息给所有顶级并重叠的窗口，以此来改变系统调色板
WM_HOTKEY    0x0312    当用户按下由 RegisterHotKey 函数注册的热键时产生此消息
WM_PRINT    0x0317    应用程序发送此消息给窗口，要求窗口在指定设备环境中绘制自己，一般情况下是打印机设备环境
WM_PRINTCLIENT    0x0318    应用程序发送此消息给窗口，要求窗口在指定设备环境中绘制窗口客户区，一般情况下是打印机设备环境
WM_APP    0x8000    帮助用户自定义消息，自定义消息可以为 WM_APP+X，X 为正整数
WM_USER    0x0400    帮助用户自定义消息，自定义消息可以为 WM_USER+X，X 为正整数

======================================================================================
解决WIN32窗口不响应WM_LBUTTONDBLCLK消息
今天在做一个软件时，发现win32创建的窗体不能响应WM_LBUTTONDBLCLK消息。在一番谷歌百度之后，终于找到了解决方法；废话少说，言归正传。
窗体不响应WM_LBUTTONDBLCLK消息，只要在注册窗口类的时候在WNDCLASS的style成员加上CS_DBLCLKS风格就行了。
下面是几种CS风格：
CS_HREDRAW：当窗体的宽度发生变化时，就重新绘制窗口。
CS_VREDRAW：当窗体的高度发生变化时，就重新绘制窗口。
CS_DBLCLKS：能接收用户在窗体总的双击事件。
CS_OWNDC：为该类中的每一个窗口分配各自独立的设备环境。
CS_NOCLOSE：禁用系统菜单中的“关闭”命令。
CS_CLASSDC：为该窗口类的各窗口分配一个共享的设备环境。
CS_PARENTDC：指定子窗口继承其父窗口的设备环境。、
CS_SAVEBITS：把被窗口遮掩的屏幕图像部分作为位图保存起来。当该窗口被移动时，windows使用被保存的位图来重建屏幕图像。
=================================================================================
WM_SYSCOMMAND消息，响应系统命令

WM_SYSCOMMAND
　　当用户从窗口菜单选择一个命令或当用户选择最大化按钮，最小化按钮，复原按钮或关闭按钮时，一个窗口将会接收该消息
　　Syntax
　　WM_SYSCOMMAND
　　WPARAM wParam
　　LPARAM lParam;
　　 参数
　　wParam
　　指定系统命令的类型。该参数可以是下列值之一：
　　SC_CLOSE　　关闭窗口
　　SC_CONTEXTHELP　　将光标改为一个问题标识样式。如果用户之后点击了对话框中的一个控件，该控件会收到一个WM_HELP消息。
　　SC_DEFAULT　　当用户双击窗口菜单时，选择默认的条目。
　　SC_HOTKEY　　以应用程序指定的热键激活窗口。lParam参数标识了所要激活的窗口。
　　SC_HSCROLL　　水平滚动。
　　SC_KEYMENU　　键盘的敲击返回窗口菜单。
　　SC_MAXIMIZE　　最大化窗口
　　SC_MINIMIZE　　最小化窗口
　　SC_MONITORPOWER　　设置显示状态。该命令支持具有节电特性的设备，如电池供电的个人电脑。
　　
lParam参数可以具有下列值：
　　-1 - 显示设备打开
　　1 - 显示设备将要进入节电模式。
　　2 - 显示设备将要被关闭
　　SC_MOUSEMENU　　鼠标单击返回窗口菜单。
　　SC_MOVE　　移动窗口
　　SC_NEXTWINDOW　　移到下一个窗口
　　SC_PREVWINDOW　　移到前一个窗口
　　SC_RESTORE　　将窗口复原到原始的位置和大小。
　　SC_SCREENSAVE　　执行System.ini文件里[boot]部分指定的屏幕保护程序。
　　SC_SIZE　　改变窗口大小。
　　SC_TASKLIST　　激活【开始】菜单。
　　SC_VSCROLL　　垂直滚动。
　　lParam
　　如果一个窗口命令被鼠标选中，低位字指定光标的水平位置。否则该参数不被使用。
　　如果一个窗口命令被鼠标选中，高位字指定光标的垂直位置。如果使用系统加速键选择的命令，则该参数为-1，如果使用助记符的话，则该参数为0.
　　 返回值
　　如果成功处理该消息，则返回值为0.
　　 备注
　　获得屏幕坐标系下的位置坐标，可以使用下面的代码：
　　xPos = GET_X_LPARAM(lParam); // horizontal position
　　yPos = GET_Y_LPARAM(lParam); // vertical position

*/        
#endif