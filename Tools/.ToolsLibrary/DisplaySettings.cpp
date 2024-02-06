#include "DisplaySettings.h"

Counts::Counts(int Counts)
{
	this->count = Counts;
}

void Counts::SetHWNDS(HWND hwnd, int count)
{
	hwnds[--count] = hwnd;
}

HWND Counts::GetHWND()
{
	//count计数在范围内
	if (count < this->hwnds.size())
	{
		return this->hwnds[this->count++]; //后加加：先用值，后增值 | 
	}

	//超出范围后
	return *this->hwnds.end();
}
HWND Counts::GetHWND(int count) const
{
	return this->hwnds[--count];
}

vector<HWND> Counts::GetHWNDS() const
{
	return this->hwnds;
}



int WindowSize::GetWindowSizeWidth() const
{
	return this->WindowWidth_Size;
}

int WindowSize::GetWindowSizeHeight() const
{
	return this->WindowHeight_Size;
}

void SetDisplaySize_Run(int displayWidth, int displayHeight)
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

void startFile(HWND hwnd, LPCWSTR filePath)
{
	ShellExecute(hwnd, L"open", filePath, NULL, NULL, SW_SHOW);
}

std::wstring StringHelper::ANSIToUnicode(const std::string& from)
{
	if (from.empty())
	{
		return std::wstring();
	}

	size_t unicodeLen = 0;
	wchar_t* pUnicode = nullptr;
	if (unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, from.c_str(), -1, NULL, 0))
	{
		pUnicode = new wchar_t[unicodeLen + 1];
		memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
		if (!::MultiByteToWideChar(CP_ACP, 0, from.c_str(), -1, (LPWSTR)pUnicode, unicodeLen))
		{
			delete[] pUnicode;//clean up if failed;  
			return std::wstring();
		}
	}
	else
	{
		return std::wstring();
	}
	std::wstring strRet(pUnicode);
	delete[] pUnicode;//clean up if success;

	return std::move(strRet);
}

DWORD FindProcessIDByName(const std::string& processName) //0 not found ; other found; processName "processName.exe" 根据名称查找进程ID
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
		if (std::wstring(pe32.szExeFile) == StringHelper::ANSIToUnicode(processName)) //进程名称
		{
			processId = pe32.th32ProcessID; //进程ID
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));
	CloseHandle(hProcessSnap);
	return(processId);
}

long GetProcessIdFromName(const char* name)
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

bool isProgramRunning(const std::string& program_name)
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
		char* pro_name = Wchar2char(program_info.szExeFile);
		if (program_name == string(pro_name))
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

//class ---------------------------------------------------------------------------------------------------

string ToolsConfigFile::GetToolsCofigFilePath() const
{
	return this->ToolsCofigFilePath;
}

int ToolsConfigFile::GetButtonOptionSum() const
{
	return this->buttonOptionSum;
}

bool ToolsConfigFile::OpenConfigFile(HWND hwnd, bool openFile)
{
#ifdef test
	//先创建文件夹(否则后面的文件不能创建)
	CreateFolder(
		this->ToolsCofigFilePath.substr(
			0, (this->ToolsCofigFilePath.size() - addToolsConfigPath.size()))
		+ addConfigPath + addToolsConfigPath);
#endif

	//先创建文件夹(否则后面的文件不能创建)
	if (!CreateFolder(
		this->ToolsCofigFilePathSubAdd))
	{
#ifndef _DEBUG
		MessageBox(NULL, L"文件夹 config 创建失败!", L"警告", MB_ICONEXCLAMATION | MB_OK);
#endif
	}

	//打开工具箱配置文件
	if (!isFileExists(this->ToolsCofigFilePath)) //文件不存在
	{
		//顺便创建 DailyList.txt(每日清单)
		this->OpenDailyList(hwnd);

		ofstream ofs;
		ofs.open(this->ToolsCofigFilePath.c_str());
		if (!ofs.fail())
		{
			inDefData(ofs); //向新建文件中写入数据
		}
		else
		{
			MessageBox(NULL, L"文件 ToolsConfig.ini 写入失败!", L"警告", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		ofs.close();

		//在 windos 中打开文件
		if (openFile)
		{
			startFile(hwnd, StringToLPCWSTR(this->ToolsCofigFilePath));
		}

		return true;
	}
	else //文件存在
	{
		ifstream ifs;

		ifs.open(this->ToolsCofigFilePath.c_str());
		if (!ifs.fail())
		{
			vstr = GetConfigFileData(ifs);
			isGetConfig = true;
		}
		else
		{
			MessageBox(NULL, L"文件 ToolsConfig.ini 打开失败!", L"警告", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		ifs.close();

		//在 windos 中打开文件
		if (openFile)
		{
			startFile(hwnd, StringToLPCWSTR(this->ToolsCofigFilePath));
		}

		return true;
	}
}


bool ToolsConfigFile::OpenDailyList(HWND hwnd, bool openFile)
{
#ifdef test
	//先创建文件夹(否则后面的文件不能创建)
	CreateFolder(this->DailyList.substr(0, this->DailyList.size() - addDailyList.size())
		+ addConfigPath + addDailyList);
#endif
	
	//打开工具箱配置文件
	if (!isFileExists(this->DailyList)) //文件不存在
	{
		ofstream ofs;
		ofs.open(this->DailyList.c_str());
		if (!ofs.fail()) {}
		else 
		{
			MessageBox(NULL, L"文件 DailyList.txt 创建失败!", L"警告", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		ofs.close();

		//在 windos 中打开文件
		if (openFile)
		{
			startFile(hwnd, StringToLPCWSTR(this->DailyList));
		}

		return true;
	}
	else //文件存在
	{
		//在 windos 中打开文件
		if (openFile)
		{
			startFile(hwnd, StringToLPCWSTR(this->DailyList));
		}
		
		return true;
	}
}


bool ToolsConfigFile::isFileExists(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	return file.good();
}

bool ToolsConfigFile::isFileExists(const char* filename)
{
	std::ifstream file(filename);
	return file.good();
}

bool ToolsConfigFile::isFileExistsStatic(const std::string& filename)
{
	std::ifstream file(filename);
	return file.good();
}

bool ToolsConfigFile::isFileExistsStatic(const char* filename)
{
	std::ifstream file(filename);
	return file.good();
}

void ToolsConfigFile::inDefData(ofstream& out)
{
	//分辨率
	//存入 选项一
	vstr.push_back("1920");
	vstr.push_back("1080");
	//存入 选项二
	vstr.push_back("1280");
	vstr.push_back("1024");

	//存入 steam 路径
	vstr.push_back("D:\\steam\\steam.exe");
	
	//存入 每日清单路径 
	vstr.push_back(DailyList);

	//存入 配置文件路径
	vstr.push_back(ToolsCofigFilePath);

	vstr.push_back("D:\\game\\Accelerator\\LeiGod_Acc\\FixNetWork.exe");

	for (auto begin = vstr.begin();
		begin != vstr.end();
		++begin) //使用当前的 begin, 下一循环距离 +1
	{
		out << *begin + '\n'; //写入, 例: 1920\n (\n:换行)
	}

	//中文版 每日清单
	//out << dailyList.c_str();
	//out << UTF8ToGB(dailyList.c_str());
}

void ToolsConfigFile::CreateFiles(const string& FilePath)
{
	string command;
	command = "mkdir -p " + FilePath;
	system(command.c_str());
}

vector<string> ToolsConfigFile::GetConfigFileData(ifstream& ifs)
{
	vector<string> v_str;
	string str;
	int it = 0;

	for (int i = 0; i < buttonOptionSum; i++)
	{
		getline(ifs, str);
		v_str.push_back(str);
		++it;
	}
	//count = it;

	return v_str;
}

void ToolsConfigFile::HWNDMapUpdate()
{
	mstrMark.insert(pair<string, int>(this->vstr[0], 1)); //默认取值 1920
	mstrMark.insert(pair<string, int>(this->vstr[1], 2)); //默认取值 1280
	mstrMark.insert(pair<string, int>("steam", 3));
	mstrMark.insert(pair<string, int>("resolution", 4));
	mstrMark.insert(pair<string, int>("inventory", 5));
	mstrMark.insert(pair<string, int>("toolcfg", 6));
}

LPCWSTR StringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

std::wstring StringToWString(const std::string& str)
{
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
	std::wstring w_str(wide);
	delete[] wide;
	return w_str;
}

char* Wchar2char(const wchar_t* szStr)
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

LPCWSTR CStringToLPCWSTR(CString cstr)
{
	LPCWSTR lstr;
	return  lstr = cstr.GetBuffer(); //CString 转 LPCWSTR
}

string LPCWSTRToString(LPCWSTR lpcwszStr)
{
	string str;
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

std::wstring StringToWString2(const std::string& str)
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


string UTF8ToGB2312(const char* str)
{
	string result;
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

string UTF8ToGBK(const char* utf8_str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

string GBKToUTF8(const char* gbk_str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gbk_str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gbk_str, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}

//获取当前目录下的所有文件夹
bool GetAllFolder(string path, vector<string>& folder) {
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t folderInfo;
	string p;
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
void GetAllFiles(string path, vector<string>& files)
{
	intptr_t hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
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
vector<string> GetAllFolderVector(string path, vector<string> folder)
{
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t folderInfo;
	string p;
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

vector<string> GetAllFilesVector(string path, vector<string> files)
{
	intptr_t hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
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

bool CreateFolder(string folderPath)
{
	//属性不为目录时
	if (GetFileAttributesA(folderPath.c_str()) != FILE_ATTRIBUTE_DIRECTORY)
	{
		//创建目录
		if (CreateDirectory(StringToLPCWSTR(folderPath), NULL))
		{
			return true;
		}
	}

	return false;
}

void OpenFolder(const string& path)
{
	//字符集 支持Unicode 和 多字节
#ifdef  _UNICODE
	std::wstring tmp = StringToWString2(path);
	LPCWSTR dir = tmp.c_str();
	ShellExecute(NULL, NULL, dir, NULL, NULL, SW_SHOWNORMAL);
#elif _MBCS
	LPCSTR dir = path.c_str();
	ShellExecute(NULL, NULL, dir, NULL, NULL, SW_SHOWNORMAL);
#endif 
}

string subSpace(string str) {
	char* tempCharArray = new char[str.length() + 1];

	// str.length() -1 == str 索引大小
	// str.length() -2 == 去掉最后一个字符
	for (size_t i = 0; i < str.length() - 1 - 1; ++i) { //循环 String对象索引大小的次数
		tempCharArray[i] = str[i]; //将字符串中最后的回车去掉
	}

	string tempString = tempCharArray;

	delete tempCharArray;
	return tempString;
}
