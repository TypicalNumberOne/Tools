#pragma once

#ifndef _SETTING_H
#define _SETTING_H

#include "resource.h"

#include "libTypical\Tool.h"

using namespace Typical_Tool;
using namespace Typical_Tool::WindowsSystem;
using namespace Typical_Tool::StringManage;
using Typical_Tool::WindowsSystem::WindowHost;

class Settings {
public:
#define WM_TRAY WM_USER + 1
	//窗口参数
	HINSTANCE hIns;
	HWND hWnd_Tray;

	HMENU hMenu;
	LPTSTR Icon;
	NOTIFYICONDATA Nid = { 0 };
	UINT WM_TASKBARCREATED;

#ifdef _DEBUG
	Tstr ExeName = Tx("Tools_DEBUG"); //程序名
#else
	Tstr ExeName = Tx("Tools"); //程序名
#endif
	Tstr ExeCurrentPath; //当前程序的路径
	Tstr ExeConfigFilePath; //当前程序的配置文件路径
	Tstr ToolsWindowClassName = Tx("Typical_Tools"); //程序窗口类名

	int SettingWindowWidth = 540;
	int SettingWindowHeight = 800;
	
	Tstr ExeTrayName = Tx("典型一号的工具箱"); //程序托盘名
	Tstr ExeTitleName = Tx("典型一号的工具箱 v1.1"); //程序标题栏名

	//窗口操作
	Win::WindowHost WindowHost;
	WindowShell WindowShell;

	//设置
	FileSystem FileSystem;
	ConfigFileTextManage ConfigFile; //配置文件
	std::map<Tstr, Tstr> BaseConfigItem; //[基本设置] 配置项
	std::map<Tstr, std::map<Tstr, Tstr>> ConfigFile_AllConfig; //配置文件 全内容
	std::vector<ShellConfig> ShellConfig; //[Shell] 配置项

	bool SetScreenResolution = false; //修改屏幕分辨率

	//菜单句柄
	int ID_Help; //帮助
	int ID_Quit; //退出
	int ID_ToolsConfig; //工具箱配置
	int ID_SetScreenResolution; //修改屏幕分辨率

public:
	Settings() {}
};
inline Settings Tools;

//更新ConfigFile内容
void UpdateConfig();

/*Windows程序启动项
* 单实例程序
* 设置DPI
* 保存进程句柄
*/
int WindowsExeAutoRunItem();
//Windows窗口类注册
void WindowsWindowClassRegister();
//Windows窗口创建
void WindowsWindowCreate();

//[Shell] 加载配置: 初始化/载入
void LoadShellConfig();
//[基本设置] 加载配置: 初始化/载入
void LoadBaseConfig(bool _bReLoad = false);

//加载菜单: 初始化/载入
void LoadToolsMenu(HMENU 菜单);
//菜单选择
void SelectMenu(int 菜单选项ID);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif