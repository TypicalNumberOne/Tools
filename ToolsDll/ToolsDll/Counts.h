#pragma once
#ifndef _COUNTS_H
#define _COUNTS_H

#include "ToolsDll.h"

class TOOLSDLL_API Counts
{
public:
	//计数
	int count = 0;
	vector<HWND> hwnds; //Button 数量

	//Counts();
	Counts(int Counts) {
		this->count = Counts;
	};

	//添加hwnd
	void AddHWND(HWND hwnd);
	//获取hwnd
	//HWND GetHWND();
	//获取hwnd:根据元素位置
	HWND GetHWND(int count) const;
	//获取vector<hwnd>
	vector<HWND> GetHWNDS() const;
	//设置hwnd(有问题，待修改)
	void SetHWNDS(HWND hwnds, int count = 1);
	//获取 hwnds 的元素数量
	int GetHWNDCount();
};

#endif