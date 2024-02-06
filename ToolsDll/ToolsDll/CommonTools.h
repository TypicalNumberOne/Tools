#pragma once
//常用工具
#ifndef _COMMONTOOLS_H
#define _COMMONTOOLS_H

#include "ToolsDll.h"

#include <ShellAPI.h>

//----------------------------------Windows系统操作
namespace WindowsSystemOperation {

	//------------------------------------------------------------------------------显示
	/*设置屏幕分辨率 运行
		* 必看 --> 分辨率(width/height): 一定成比例, 如: 1920 x 1080(16:9), 1280 x 1024(4:3)
		*/
	extern "C" TOOLSDLL_API void SetDisplaySize_Run(int widthValue, int HeightValue);


	//------------------------------------------------------------------------------程序操作
	//打开 应用程序文件
	extern "C" TOOLSDLL_API void startFile(LPCWSTR filePath);

	//获取程序ID
	TOOLSDLL_API DWORD FindProcessIDByName(const std::string & processName);

	//获取程序PID
	extern "C" TOOLSDLL_API long GetProcessIdFromName(const char* name);

	//程序是否正在运行
	extern "C" TOOLSDLL_API bool isProgramRunning(const std::string & program_name);
	
	//是否为管理员权限运行的
	TOOLSDLL_API BOOL IsRunAsAdministrator();

	//现在提升为管理员权限
	TOOLSDLL_API void ElevateNow(); //与 IsRunAsAdministrator函数同时使用

	//获得管理员权限
	TOOLSDLL_API void GainAdminPrivileges(CString strApp); //精简 ElevateNow/IsRunAsAdministrator后的，且可以传入路径指定程序
}

//---------------------------字符处理
namespace StringHandling {

	//------------------------------------------------------------------------------字符转换
	//std::string 转 LPCWSTR
	TOOLSDLL_API LPCWSTR StringToLPCWSTR(std::string orig);

	//std::string 转 Wstring(宽字符)
	TOOLSDLL_API std::wstring StringToWString(const std::string & str);

	//CString 转 LPCWSTR
	TOOLSDLL_API LPCWSTR CStringToLPCWSTR(CString cstr);

	//LPCWSTR 转 std::string
	TOOLSDLL_API std::string LPCWSTRToString(LPCWSTR lpcwszStr);

	//Wchar 转 char
	extern "C" TOOLSDLL_API char* WcharToChar(const wchar_t* szStr);

	//TCHAR 转 String
	TOOLSDLL_API std::string TCHARToString(TCHAR * STR);
	//------------------------------------------------------------------------------编码转换
	//UTF-8 转 GB2312
	TOOLSDLL_API std::string UTF8ToGB2312(const char* str);

	//UTF8 转 GBK
	TOOLSDLL_API std::string UTF8ToGBK(const char* utf8_str);

	//GBK 转 UTF8
	TOOLSDLL_API  std::string GBKToUTF8(const char* gbk_str);

}


//------------------------------------------------------------------------------文件操作
//获取当前目录下的所有文件夹
extern "C" TOOLSDLL_API bool GetAllFolder(std::string path, std::vector<std::string>&folder);

//获取所有的文件名
extern "C" TOOLSDLL_API void GetAllFiles(std::string path, std::vector<std::string>&files);

//获取当前目录下的所有文件夹 return
TOOLSDLL_API std::vector<std::string> GetAllFolderVector(std::string path, std::vector<std::string> folder);

//获取所有的文件名 return
TOOLSDLL_API std::vector<std::string> GetAllFilesVector(std::string path, std::vector<std::string> files);

//创建文件夹
extern "C" TOOLSDLL_API bool CreateFolder(std::string folderPath);

//打开文件夹
extern "C" TOOLSDLL_API void OpenFolder(const std::string& path);

//------------------------------------------------------------------------------其他

//去掉从流中获取到的字符串中的最后一个字符
TOOLSDLL_API std::string subSpace(std::string str);

//------------------------------------------------------------------------------控制台

//移动光标到目标位置
TOOLSDLL_API void MoveCursorLocation(int x, int y);

//------------------------------------------------------------------------------帧率
#ifndef FPS_COUNT
#define FPS_COUNT 60 //Fps 统计的间隔(帧率)
#endif

//获取 FPS
extern "C" TOOLSDLL_API float GetFps();

#endif