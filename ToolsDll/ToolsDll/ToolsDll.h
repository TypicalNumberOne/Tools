//ToolsDll.h 工具容器
#ifndef _TOOLSDLL_H
#define _TOOLSDLL_H
#pragma once

#ifdef _EXPORTNG //导出
	#define TOOLSDLL_API __declspec(dllimport)
#else
	#define TOOLSDLL_API __declspec(dllexport) //导出
	#define _EXPORTNG //并定义
#endif

//---------------------------
#include <Windows.h>
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


//---------------------------atls.lib静态库 版本 DLL不适用
//#pragma comment(lib, "atls.lib")
#include <atlstr.h>

#include <algorithm>
#include <direct.h>
#include <io.h>

#include "Key.h"
#include "SaveFile.h"
#include "CharHandleOfConfigFile.h"
#include "StringConversion.h"
#include "ToolsConfigFile.h"
#include "Collishion.h"
#include "ShowDraw.h"
#include "Timers.h"
#include "WindowSize.h"
#include "Counts.h"
#include "CommonTools.h"

//---------------------------------------------------------------------------------------------------------------------------
#endif