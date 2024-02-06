#pragma once

#ifndef _SAVEFILE_H
#define _SAVEFILE_H
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "DisplaySettings.h"

using namespace std;

//---------------------------------------------------------------基本操作 BasicOperation-----------------------------------------------------------
//清空字符串
string emptyString(string& text);

//模板 输出文本(默认0 不换行
template<typename T>
void output(T value, const int& i = 0);

//修改字符串中指定字符(char: ASCLL)
string completeString(string& text, char& charNumbers);

//执行 传入的控制台命令
void consoleCommand(string text);
//---------------------------------------------------------------文件操作 FileOperations-----------------------------------------------------------

class FileOperations
{
private:
    CString program_Path; //程序路径·····
    CString project_Path; //项目路径

    //文件路径名
    CString file_PathAndName; //配置文件路径

    //文件后缀
    CString file_Suffix; //FileOperations-config.txt 配置文件

public:
    FileOperations()
        : program_Path('\0'), project_Path('\0'), file_PathAndName(""), file_Suffix("FileOperations-config.txt")
    { }

    //转移steam.exe位置
    int copyFileSteam(CString path, CString project_Path, CString program_Suffix);

    //还原steam.exe位置
    int copyFileSteamReduction(CString path, CString project_Path, CString program_Suffix);

    //从配置文件中获取 steam.exe 文件的位置
    void GetFilePath();

    //获取 项目程序路径
    void GetProgramPath(class ToolsConfigFile ToolsCfgF);

    //复制文件
    int copyFile(char* SourceFile, char* NewFile, void (*CerrPrint)());

    //复制文件
    int copyFile(char* SourceFile, char* NewFile);

    //执行复制文件操作
    void copyFile_Run();

    //删除文件
    void deleteFile();

    //保存数据
    void saveData(string& filepath, string& filaName, string& fileSuffixConfig); //未完成

};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif _SAVEFILE_H