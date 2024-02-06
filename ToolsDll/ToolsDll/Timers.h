//Timers.h 计时器

#pragma once
#ifndef _TIMERS_H_
#define _TIMERS_H_

#include "ToolsDll.h"

//计时器
class TOOLSDLL_API Timers
{
private:
	float InitialTime = 0; //初始的时间
	/*
	int NewTime; //新的时间
	int PastTime; //过去的时间
	*/
	int TempTime = 0; //临时的时间

	std::vector<float> TimerContainer; //计时器 集合(Container)


public:
	Timers()
	{
		//初始化
		InitialTime = GetTime();
		TimerContainer.push_back(InitialTime);
	}
	Timers(int& Timer)
	{
		//初始化
		InitialTime = Timer;
		TimerContainer.push_back(InitialTime);
	}

	//固定初始化: 有且只运行一次
	void Initial();

	/* 增加 指定数量的计时节点(当前时间)：默认为 0
	* 不传入值时：添加一个节点
	* 传入值时：根据 传入值int 将节点扩充到指定个数
	*/
	void AddNewTimer(int elementCout = 1);

	//更新 时间(当前时间)
	float GetTime();

	//更新 时间节点元素(Element)
	void SetTimer(int TimerElement);
	//更新 时间节点元素(Element)
	void SetTimer(int TimerElement, float Time);
	//更新 时间节点元素(Element)::iterator
	//void SetTimer(std::vector<float>::iterator TimerVecIter, float Time);

	//获取 计时节点元素(Element)
	void GetTimer(int& Timer, int TimerElement);
	//获取 计时节点元素(Element): return int
	int GetTimer(int TimerElement);

	//Timer 的间隔(差值): ms
	void ComputeTimerDistance(float PastTime, float NewTime, float& Distance);
	//计算 Timer 的间隔(差值): ms
	float ComputeTimerDistance(float PastTime, float NewTime);

	//毫秒(ms) 转 秒(s)
	void MsecToSecond(float Msec, int& Time);
	//毫秒(ms) 转 秒(s)
	int MsecToSecond(float Msec);

	//首时间节点 与 尾时间节点 比较
	void FirstAndEndCompare(float& Time);
	//首时间节点 与 尾时间节点 比较
	float FirstAndEndCompare();


public:
	//获取计时器集合
	std::vector<float> GetTimerContainer();


public:
	//毫秒(ms) 转 秒(s)
	static void MsecToSecond_S(float Msec, int& Second);
	//毫秒(ms) 转 秒(s)
	static int MsecToSecond_S(float Msec);

	//更新 时间(当前时间)
	static float GetTime_S();

	Timers operator=(const Timers& Other);
	bool operator==(const Timers& other);
};


/*
Tool
*/


#endif