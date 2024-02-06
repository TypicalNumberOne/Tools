#include "pch.h" //DLL标准
#include <utility> //DLL标准
#include <limits.h> //DLL标准

#include "CommonTools.h"

#include "ToolsConfigFile.h"

using StringHandling::StringToLPCWSTR;
using StringHandling::CharHandleOfConfigFile;

//----------------------------- class ToolsConfigFile

std::string ToolsConfigFile::GetToolsCofigFilePath() const
{
	return this->ToolsCofigFilePath;
}

int ToolsConfigFile::GetButtonOptionSum() const
{
	return this->buttonOptionSum;
}

bool ToolsConfigFile::OpenConfigFile(bool openFile)
{
#ifndef test
	//先创建文件夹(否则后面的文件不能创建)
	CreateFolder(
		this->ToolsCofigFilePathSubAdd);
#endif

#ifdef test
	//先创建文件夹(否则后面的文件不能创建)
	if (!CreateFolder(
		this->ToolsCofigFilePathSubAdd))
	{
		//MessageBox(NULL, L"文件夹 config 创建失败!", L"警告", MB_ICONEXCLAMATION | MB_OK);
	}
#endif

	//打开工具箱配置文件
	if (!isFileExists(this->ToolsCofigFilePath)) //文件不存在
	{
		//顺便创建 DailyList.txt(每日清单)
		this->OpenDailyList();

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
			WindowsSystemOperation::startFile(StringToLPCWSTR(this->ToolsCofigFilePath));
		}

		return true;
	}
	else //文件存在
	{
		ifstream ifs;

		ifs.open(this->ToolsCofigFilePath.c_str());
		if (!ifs.fail())
		{
			vstr = GetConfigFileData_map(ifs);
			//isGetConfig = true;
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
			WindowsSystemOperation::startFile(StringToLPCWSTR(this->ToolsCofigFilePath));
		}

		return true;
	}
}


bool ToolsConfigFile::OpenDailyList(bool openFile)
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
			WindowsSystemOperation::startFile(StringToLPCWSTR(this->DailyList));
		}

		return true;
	}
	else //文件存在
	{
		//在 windos 中打开文件
		if (openFile)
		{
			WindowsSystemOperation::startFile(StringToLPCWSTR(this->DailyList));
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
	//vector
	//分辨率
	//存入1-2 选项一
	vstrFirst.push_back("ScreenResolution1-1=");
	vstr.push_back("1920");
	vstrFirst.push_back("ScreenResolution1-2=");
	vstr.push_back("1080");
	//存入3-4 选项二
	vstrFirst.push_back("ScreenResolution2-1=");
	vstr.push_back("1280");
	vstrFirst.push_back("ScreenResolution2-2=");
	vstr.push_back("1024");

	//存入5 steam 路径
	vstrFirst.push_back("steam=");
	vstr.push_back("D:\\game\\Steam\\steam.exe");

	//存入6 每日清单路径 
	vstrFirst.push_back("DailyList=");
	vstr.push_back(DailyList);

	//存入7 配置文件路径
	vstrFirst.push_back("ToolsConfig=");
	vstr.push_back(ToolsCofigFilePath);

	//存入8 雷神加速器 路径
	vstrFirst.push_back("leigod=");
	vstr.push_back("D:\\game\\Accelerator\\LeiGod_Acc\\leigod.exe");

	//存入9 Repos文件夹路径
	vstrFirst.push_back("Repos=");
	vstr.push_back("C:\\Users\\22793\\Source\\Repos");

	//存入10 笔记本键盘开关状态：关
	vstrFirst.push_back("NoteKeyboardOff=");
	vstr.push_back(ToolsCofigFilePathSubAdd + "\\NoteKeyboardOff.bat - 快捷方式");
	//存入11 笔记本键盘开关状态：开
	vstrFirst.push_back("NoteKeyboardOn=");
	vstr.push_back(ToolsCofigFilePathSubAdd + "\\NoteKeyboardOn.bat - 快捷方式");

	//写入文件并为每行字符串尾添加 '\n'换行
	std::string tempStr;
	for (int i = 0;
		i != vstr.size();
		++i) //使用当前的 begin, 下一循环距离 +1
	{
		tempStr = vstrFirst[i] + vstr[i] + '\n';
		out << tempStr; //写入, 例: 1920\n (\n:换行)
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
	//int it = 0;

	for (int i = 0; i < buttonOptionSum; i++)
	{
		getline(ifs, str);
		v_str.push_back(str);
		//++it;
	}
	//count = it;

	return v_str;
}

vector<string> ToolsConfigFile::GetConfigFileData_map(ifstream& ifs)
{
	vector<string> v_str;
	string str;
	//int it = 0;

	//根据按钮数量获取配置信息
	for (int i = 0; i < vstrCount; i++)
	{
		getline(ifs, str);

		//使用配置文件的字符处理类
		CharHandleOfConfigFile CharHandleOfConfigFile;
		CharHandleOfConfigFile.StringParsing_Equalsign(str);
		//每次使用后递增迭代器
		std::pair<std::string, std::string> temp_pair = *CharHandleOfConfigFile.GetMapString().cbegin()++;
		v_str.push_back(temp_pair.first);
	}
	//count = it;

	return v_str;
}