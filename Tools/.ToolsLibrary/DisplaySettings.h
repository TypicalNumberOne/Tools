#ifndef _DISPLAYSETTINGS_H
#define _DISPLAYSETTINGS_H
//-------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <tlhelp32.h>
#include <tchar.h>
#include <comdef.h> 
#include <thread>

#include <vector>
#include <sstream>
#include <list>
#include <map>

#ifdef WIN32
#pragma comment(lib, \
	"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.37.32822\\atlmfc\\lib\\x86\\atls.lib")
#else
#pragma comment(lib, \
	"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.37.32822\\atlmfc\\lib\\x64\\atls.lib")
#endif

#include <atlstr.h>


//#include <afxstr.h>
#include <algorithm>
#include <direct.h>
#include <io.h>

#include "Key.h"
#include "SaveFile.h"


#ifdef STRINGHELPER_EXPORT     
#define STRINGHELPER_API __declspec(dllexport)      
#else     
#define STRINGHELPER_API __declspec(dllimport)      
#endif 


using namespace std;


class STRINGHELPER_API StringHelper
{
public:
#if 0
	static std::string UnicodeToANSI(const std::wstring& from);
	static std::string UnicodeToUTF8(const std::wstring& from);

	static std::wstring UTF8ToUnicode(const std::string& from);
	static std::string UTF8ToANSI(const std::string& from);

	static std::string ANSIToUTF8(const std::string& from);
#endif
	static std::wstring ANSIToUnicode(const std::string& from);
};



struct Counts
{
	//计数
	int count = 0;
	vector<HWND> hwnds; //Button 数量

	//Counts();
	Counts(int Counts);

	//获取hwnd
	HWND GetHWND();
	//获取hwnd
	HWND GetHWND(int count) const;
	//获取vector<hwnd>
	vector<HWND> GetHWNDS() const;
	//设置hwnd
	void SetHWNDS(HWND hwnds, int count = 1);
};



class WindowSize
{
private:
	int WindowWidth_Size;
	int WindowHeight_Size;
public:
	WindowSize()
		: WindowWidth_Size(0), WindowHeight_Size(0) {}
	WindowSize(int WidthSize, int HeightSize)
	{
		WindowWidth_Size = WidthSize;
		WindowHeight_Size = HeightSize;
	}

	//获取 窗口大小 Width
	int GetWindowSizeWidth() const;
	
	//获取 窗口大小 Height
	int GetWindowSizeHeight() const;
};


struct Coordinate
{
	vector<int> Width; //X坐标
	vector<int> Height; //Y坐标
};


class ToolsConfigFile
{
public:

	vector<string> vstr;
	map<string, int> mstrMark;

	//按钮选项总和
	int buttonOptionSum = 0;

	bool isGetConfig = false;

	//程序 全路径
	TCHAR sizePath[MAX_PATH] = { 0 };

public:
	//
	//工具箱程序 路径
	//CString ToolsEXEFilePath = L"C:\\Users\\22793\\source\\repos\\Tools\\Debug\\Tools.exe";
	CString ToolsEXEFilePath = L"";

	//工具箱配置 文件路径
	//string ToolsCofigFilePath = "C:\\Users\\22793\\source\\repos\\Tools\\Debug\\config\\ToolsConfig.ini";
	string ToolsCofigFilePath = "";
	string ToolsCofigFilePathSubAdd = "";
	
	//每日清单 文件路径 "C:\\Users\\22793\\source\\repos\\Tools\\Debug\\config\\DailyList.txt"
	string DailyList;
	string DailyListSubAdd;

	//工具箱配置 后缀
	string addToolsConfigPath = "\\ToolsConfig.ini";
	//每日清单 后缀
	string addDailyList = "\\DailyList.txt";
	//工具箱程序 后缀
	string addToolsPath = "\\Tools.exe";
	//config 文件夹
	string addConfigPath = "\\config";


public:
	ToolsConfigFile(int sum)
	{

		this->buttonOptionSum = sum;

		//获取当前程序的全路径->sizePath
		GetModuleFileName(NULL, this->sizePath, MAX_PATH);
		//工具箱程序路径赋值
		ToolsEXEFilePath = this->sizePath;

		
		int tempToolsPathSize, //Tools.exe全路径长度
			tempAdd, //(string)addToolsPath
			tempSize; //去掉 add 后长度
		//Tools.exe全路径 (C:\\Users\\22793\\source\\repos\\Tools\\Debug\\Tools.exe)
		string tempToolsPath = (string)CT2A(this->sizePath); 

		//长度 (C:\\Users\\22793\\source\\repos\\Tools\\Debug\\Tools.exe)
		tempToolsPathSize = tempToolsPath.size();
		//长度 (\\Tools.exe)
		tempAdd = addToolsPath.size();
		//长度 (C:\\Users\\22793\\source\\repos\\Tools\\Debug)
		tempSize = tempToolsPathSize - tempAdd;

		//临时路径(C:\\Users\\22793\\source\\repos\\Tools\\Debug)
		string temp(tempSize, ' ');
		//替换为: 没有 (string)subToolsPath 的路径
		for (int i = 0; i < tempSize; i++)
		{
			temp[i] = tempToolsPath[i];
		}
		//每日清单路径
		DailyList = temp + addConfigPath + addDailyList;
		DailyListSubAdd = temp + addConfigPath;
		//配置文件路径
		ToolsCofigFilePath = temp + addConfigPath + addToolsConfigPath;
		ToolsCofigFilePathSubAdd = temp + addConfigPath;
	};

	//获取
	string GetToolsCofigFilePath() const;

	//获取 按键总数
	int GetButtonOptionSum() const;

	/*
	打开配置文件, openFile: 在 windos 中打开文件
	*/
	bool OpenConfigFile(HWND hwnd, bool openFile = false);
	

	/*
	打开每日清单文件, openFile: 在 windos 中打开文件
	*/
	bool OpenDailyList(HWND hwnd, bool openFile = false);

	//文件是否存在(用 ifstream检测)
	bool isFileExists(const std::string& filename);
	//文件是否存在(用 ifstream检测)
	static bool isFileExistsStatic(const std::string& filename);

	//文件是否存在(用 ifstream检测)
	bool isFileExists(const char* filename);
	//文件是否存在(用 ifstream检测)
	static bool isFileExistsStatic(const char* filename);

	//写入默认数据
	void inDefData(ofstream& out);

	//创建文件
	void CreateFiles(const string& FilePath);

	//获取配置文件数据
	vector<string> GetConfigFileData(ifstream& ifs);

	//HWND Map更新
	void HWNDMapUpdate();
};


//------------------------------------------------------------------------------显示
/*设置屏幕分辨率 运行
	* 必看 --> 分辨率(width/height): 一定成比例, 如: 1920 x 1080(16:9), 1280 x 1024(4:3)
	*/
void SetDisplaySize_Run(int widthValue, int HeightValue);


//------------------------------------------------------------------------------程序操作
//打开 应用程序文件
void startFile(HWND hwnd, LPCWSTR filePath);

//获取程序ID
DWORD FindProcessIDByName(const std::string& processName);

//获取程序PID
long GetProcessIdFromName(const char* name);

//程序是否正在运行
bool isProgramRunning(const std::string& program_name);
//------------------------------------------------------------------------------字符转换
//string 转 LPCWSTR
LPCWSTR StringToLPCWSTR(std::string orig);

//string 转 Wstring(宽字符)
std::wstring StringToWString(const std::string& str);

//CString 转 LPCWSTR
LPCWSTR CStringToLPCWSTR(CString cstr);

//LPCWSTR 转 string
string LPCWSTRToString(LPCWSTR lpcwszStr);

std::wstring StringToWString(const std::string& str);

//
char* Wchar2char(const wchar_t* szStr);
//------------------------------------------------------------------------------编码转换
//UTF-8 转 GB2312
string UTF8ToGB2312(const char* str);

//UTF8 转 GBK
string UTF8ToGBK(const char* utf8_str);

//GBK 转 UTF8
string GBKToUTF8(const char* gbk_str);


//------------------------------------------------------------------------------文件操作
//获取当前目录下的所有文件夹
bool GetAllFolder(string path, vector<string>& folder);

//获取所有的文件名
void GetAllFiles(string path, vector<string>& files);

//获取当前目录下的所有文件夹 return
vector<string> GetAllFolderVector(string path, vector<string> folder);

//获取所有的文件名 return
vector<string> GetAllFilesVector(string path, vector<string> files);

//创建文件夹
bool CreateFolder(string folderPath);

//打开文件夹
void OpenFolder(const string& path);

//------------------------------------------------------------------------------其他
//去掉从流中获取到的字符串中的最后一个字符
string subSpace(string str);


/*

class TimeDate {

public:
	LPCWSTR wStr;

public:
	//根据返回的时间设置系统时间
	void setTimeFromTP(ULONG ulTime)
	{
		FILETIME ft;
		SYSTEMTIME st;

		//将基准时间转换成windows文件时间
		st.wYear = 1900;
		st.wMonth = 1;
		st.wDay = 1;
		st.wHour = 0;
		st.wMinute = 0;
		st.wSecond = 0;
		st.wMilliseconds = 0;

		SystemTimeToFileTime(&st, &ft);

		LONGLONG* pLLong = (LONGLONG*)&ft;
		*pLLong += (LONGLONG)10000000 * ulTime;
		FileTimeToSystemTime(&ft, &st);
		::SetSystemTime(&st);
	}

	void Run()
	{
		//CInitSock initSock;
		SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			wStr = L"socket error...";
			return;
		}
		sockaddr_in servAddr = { 0 };
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = ::htons(37);
		servAddr.sin_addr.S_un.S_addr = ::inet_addr("69.25.96.13"); //别用210.72.145.44这个IP， 这是天朝的 常TMD不返回值
		if (SOCKET_ERROR == ::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)))
		{
			wStr = L"connect error..";
			return;
		}

		//接收时间
		ULONG ulTime = 0;
		int nRecv = ::recv(s, (char*)&ulTime, sizeof(ulTime), 0);
		if (nRecv > 0) //收到数据
		{
			ulTime = ::ntohl(ulTime);
			setTimeFromTP(ulTime);
		}
		else
		{
			wStr = L"recv error...";
			return;
		}

		::closesocket(s);
		getchar();
	}
};

*/


//---------------------------------------------------------------------------------------------------------------------------
#endif _DISPLAYSETTINGS_H