#pragma once
#ifndef _WINDOWSIZE_H
#define _WINDOWSIZE_H

#include "ToolsDll.h"

//窗口大小
class TOOLSDLL_API WindowSize
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

#endif