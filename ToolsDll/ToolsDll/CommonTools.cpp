#include "pch.h" //DLL标准
#include <utility> //DLL标准
#include <limits.h> //DLL标准

#include "CommonTools.h"

void WindowsSystemOperation::SetDisplaySize_Run(int displayWidth, int displayHeight)
{
	/*
	* ---------------------------------必看
	分辨率(width/height): 一定成比例, 如: 1920 x 1080(16:9), 1280 x 1024(4:3)
	*/


	//初始化
	DEVMODE NewDevMode;
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);

	//第一次修改分辨率: 1920 x 1080
	/*NewDevMode.dmPelsWidth = atoi(ToolsCfgF.vstr[1 - 1].c_str());
	NewDevMode.dmPelsWidth = atoi(ToolsCfgF.vstr[2 - 1].c_str());*/

	//记录修改信息
	NewDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	NewDevMode.dmPelsWidth = displayWidth;
	NewDevMode.dmPelsHeight = displayHeight;

	//根据修改信息 修改屏幕分辨率
	ChangeDisplaySettings(&NewDevMode, 0);

	//修改后的屏幕分辨率信息 提醒
	//MessageBox(NULL, L"1920", L"警告", MB_ICONEXCLAMATION | MB_OK);
}

void WindowsSystemOperation::startFile(LPCWSTR filePath)
{
	ShellExecute(NULL, L"open", filePath, NULL, NULL, SW_SHOW);
}

DWORD WindowsSystemOperation::FindProcessIDByName(const std::string& processName) //0 not found ; other found; processName "processName.exe" 根据名称查找进程ID
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return(0);
	}
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap); // clean the snapshot object 清理快照对象
		return(0);
	}
	DWORD processId = 0;
	do
	{
		if (std::wstring(pe32.szExeFile) == StringHandling::ANSIToUnicode(processName)) //进程名称
		{
			processId = pe32.th32ProcessID; //进程ID
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);
	return(processId);
}

long WindowsSystemOperation::GetProcessIdFromName(const char* name)
{
	HANDLE hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hsnapshot == INVALID_HANDLE_VALUE)
	{
		cout << "Create TlHelp32 Error!" << endl;
		return -1;
	}

	PROCESSENTRY32 processer;
	processer.dwSize = sizeof(PROCESSENTRY32);

	int flag = Process32First(hsnapshot, &processer);
	while (flag != 0)
	{
		_bstr_t processName(processer.szExeFile);  //WCHAR字符串转换成CHAR字符串
		if (strcmp(processName, name) == 0)
		{
			return processer.th32ProcessID;        //返回进程ID
		}
		flag = Process32Next(hsnapshot, &processer);
	}

	CloseHandle(hsnapshot);
	return -2;
}

bool WindowsSystemOperation::isProgramRunning(const std::string& program_name)
{
	bool ret = false;
	HANDLE info_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //拍摄系统中所有进程的快照: TH32CS_SNAPPROCESS
	if (info_handle == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot fail!!\n\n");
		return false;
	}

	PROCESSENTRY32W program_info;
	program_info.dwSize = sizeof(PROCESSENTRY32W);  //设置结构体大小
	int bResult = Process32FirstW(info_handle, &program_info); //获取所有进程中第一个进程的信息
	if (!bResult)
	{
		printf("Process32FirstW fail!!\n\n");
		return false;
	}

	while (bResult)
	{
		char* pro_name = StringHandling::WcharToChar(program_info.szExeFile);
		if (program_name == std::string(pro_name))
		{
			ret = true;
			break;
		}
		//获得下一个进程的进程信息
		bResult = Process32Next(info_handle, &program_info);
	}
	CloseHandle(info_handle);//关闭句柄
	return ret;
}

BOOL WindowsSystemOperation::IsRunAsAdministrator()
{
	BOOL fIsRunAsAdmin = FALSE;
	DWORD dwError = ERROR_SUCCESS;
	PSID pAdministratorsGroup = NULL;

	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	if (!AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&pAdministratorsGroup))
	{
		dwError = GetLastError();
		
		if (pAdministratorsGroup)
		{
			FreeSid(pAdministratorsGroup);
			pAdministratorsGroup = NULL;
		}

		if (ERROR_SUCCESS != dwError)
		{
			throw dwError;
		}

		return fIsRunAsAdmin;
	}

	if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
	{
		dwError = GetLastError();

		if (pAdministratorsGroup)
		{
			FreeSid(pAdministratorsGroup);
			pAdministratorsGroup = NULL;
		}

		if (ERROR_SUCCESS != dwError)
		{
			throw dwError;
		}

		return fIsRunAsAdmin;
	}
}

void WindowsSystemOperation::ElevateNow()
{
	BOOL bAlreadyRunningAsAdministrator = FALSE;
	try
	{
		bAlreadyRunningAsAdministrator = WindowsSystemOperation::IsRunAsAdministrator();
	}
	catch (...)
	{
		MessageBox(NULL, TEXT("管理员权限提升失败！"), TEXT("错误"), NULL);
	}

	if (!bAlreadyRunningAsAdministrator)
	{
		WCHAR szPath[MAX_PATH];
		if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath)))
		{
			SHELLEXECUTEINFO sei = { sizeof(sei) };

			sei.lpVerb = L"runas";
			sei.lpFile = szPath;
			sei.hwnd = NULL;
			sei.nShow = SW_SHOWDEFAULT;

			if (!ShellExecuteEx(&sei))
			{
				DWORD dwError = GetLastError();
				if (dwError == ERROR_CANCELLED)
					//Annoys you to Elevate it LOL: 提升它会惹恼你，哈哈
					CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ElevateNow, 0, 0, 0);
			}
		}
	}
	else
	{
		///Code
	}
}

void WindowsSystemOperation::GainAdminPrivileges(CString strApp)
{
	SHELLEXECUTEINFO execinfo;
	memset(&execinfo, 0, sizeof(execinfo));
	execinfo.lpFile = strApp;
	execinfo.cbSize = sizeof(execinfo);
	execinfo.lpVerb = _T("runas");
	execinfo.fMask = SEE_MASK_NO_CONSOLE;
	execinfo.nShow = SW_SHOWDEFAULT;

	ShellExecuteEx(&execinfo);
}



LPCWSTR StringHandling::StringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

char* StringHandling::WcharToChar(const wchar_t* szStr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}

std::string StringHandling::TCHARToString(TCHAR* STR)
{
	int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
	char* chRtn = new char[iLen * sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
	std::string str(chRtn);
	delete chRtn;
	return str;
}

LPCWSTR StringHandling::CStringToLPCWSTR(CString cstr)
{
	LPCWSTR lstr;
	return  lstr = cstr.GetBuffer(); //CString 转 LPCWSTR
}

std::string StringHandling::LPCWSTRToString(LPCWSTR lpcwszStr)
{
	std::string str;
	DWORD dwMinSize = 0;
	LPSTR lpszStr = NULL;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);
	if (dwMinSize == 0)
	{
		return 0;
	}
	lpszStr = new char[dwMinSize];
	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwMinSize, NULL, FALSE);
	str = lpszStr;
	delete[] lpszStr;
	return str;
}

std::wstring StringHandling::StringToWString(const std::string& str)
{
	std::wstring wContext = L"";
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	WCHAR* buffer = new WCHAR[len + 1];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';
	wContext.append(buffer);
	delete[] buffer;

	return wContext;
}


std::string StringHandling::UTF8ToGB2312(const char* str)
{
	std::string result;
	WCHAR* strSrc;
	LPSTR szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

std::string StringHandling::UTF8ToGBK(const char* utf8_str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

std::string StringHandling::GBKToUTF8(const char* gbk_str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gbk_str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gbk_str, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	std::string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}

//获取当前目录下的所有文件夹
bool GetAllFolder(std::string path, vector<std::string>& folder) {
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t folderInfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &folderInfo)) != -1) {
		do {
			if ((folderInfo.attrib & _A_SUBDIR)) {
				if (strcmp(folderInfo.name, ".") != 0 && strcmp(folderInfo.name, "..") != 0) {
					folder.push_back(p.assign(path).append("\\").append(folderInfo.name));
				}
			}
			else {
				std::cout << "not a folder!\n";
			}
		} while (_findnext(hFile, &folderInfo) == 0);
		_findclose(hFile); //结束查找 
	}
	return true;
}

//获取所有的文件名
void GetAllFiles(std::string path, vector<std::string>& files)
{
	intptr_t hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					GetAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}

/*
vector<std::string> GetAllFolderVector(std::string path, vector<std::string> folder)
{
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t folderInfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &folderInfo)) != -1) {
		do {
			if ((folderInfo.attrib & _A_SUBDIR)) {
				if (strcmp(folderInfo.name, ".") != 0 && strcmp(folderInfo.name, "..") != 0) {
					folder.push_back(p.assign(path).append("\\").append(folderInfo.name));
				}
			}
			else {
				std::cout << "not a folder!\n";
			}
		} while (_findnext(hFile, &folderInfo) == 0);
		_findclose(hFile); //结束查找
	}

	return folder;
}

vector<std::string> GetAllFilesVector(std::string path, vector<std::string> files)
{
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					GetAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}

	return files;
}
*/

bool CreateFolder(std::string folderPath)
{
	//属性不为目录时
	if (GetFileAttributesA(folderPath.c_str()) != FILE_ATTRIBUTE_DIRECTORY)
	{
		//创建目录
		if (CreateDirectory(StringHandling::StringToLPCWSTR(folderPath), NULL))
		{
			return true;
		}
	}

	return false;
}

void OpenFolder(const std::string& path)
{
	//字符集 支持Unicode 和 多字节
#ifdef  _UNICODE
	std::wstring tmp = StringHandling::StringToWString(path);
	LPCWSTR dir = tmp.c_str();
	ShellExecute(NULL, NULL, dir, NULL, NULL, SW_SHOWNORMAL);
#elif _MBCS
	LPCSTR dir = path.c_str();
	ShellExecute(NULL, NULL, dir, NULL, NULL, SW_SHOWNORMAL);
#endif 
}

std::string subSpace(std::string str) {
	char* tempCharArray = new char[str.length() + 1];

	// str.length() -1 == str 索引大小
	// str.length() -2 == 去掉最后一个字符
	for (size_t i = 0; i < str.length() - 1 - 1; ++i) { //循环 String对象索引大小的次数
		tempCharArray[i] = str[i]; //将字符串中最后的回车去掉
	}

	std::string tempString = tempCharArray;

	delete tempCharArray;
	return tempString;
}

void MoveCursorLocation(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

float GetFps()
{
	//临时统计
	static int tempCount = 0;
	static Timers timer; //时间
	static float fps; //帧率
	timer.Initial();

	if (tempCount > FPS_COUNT)
	{
		//将时间节点拓展到两个
		if (timer.GetTimerContainer().size() < 2)
			timer.AddNewTimer();

		tempCount = 0;
		timer.SetTimer(2, timer.GetTime());
		float tempTime = timer.FirstAndEndCompare();
		fps = FPS_COUNT / (tempTime / 1000.0f); //获取的系统时间为毫秒数
		timer.SetTimer(1, timer.GetTime());
	}

	tempCount++;
	return fps;
}