#pragma once
#ifndef _TOOLSCONFIGFILE_H
#define _TOOLSCONFIGFILE_H

#include "ToolsDll.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::map;
using std::ofstream;
using std::ifstream;

//工具箱配置文件
class TOOLSDLL_API ToolsConfigFile
{
public:
	vector<string> vstr;
	vector<string> vstrFirst;
	std::map<std::string, std::string> mStr;

	//按钮选项总和
	int buttonOptionSum = 0;
	//vstr总数
	int vstrCount = 11;

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

	//打开配置文件, openFile: 在 windos 中打开文件
	bool OpenConfigFile(bool openFile = false);

	//打开每日清单文件, openFile: 在 windos 中打开文件
	bool OpenDailyList(bool openFile = false);

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
	//获取配置文件数据(map)
	vector<string> GetConfigFileData_map(ifstream& ifs);

};

#endif