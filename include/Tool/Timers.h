﻿#pragma once

//Timers.h 计时器
#ifndef _TIMERS_H_
#define _TIMERS_H_

#include "Tools_Tool.h"
#include "Log.h"

#include <vector>
#include <chrono>
#include <thread> // 用于模拟延迟

namespace Tools_Tool {

	enum TimeMeasure
	{
		sec, //秒级
		ms, //毫秒级
		us, //微秒级
		ns  //纳秒级
	};
	typedef TimeMeasure tms;
#define 时间计量单位 TimeMeasure

	//计时器
	class TOOLS_TOOL_API Timers
	{
	private:
		std::chrono::system_clock::time_point InitTime; //初始的时间
		std::chrono::steady_clock::time_point InitTime_s; //初始的时间
		std::chrono::system_clock::time_point TempTime; //临时的时间
		std::chrono::steady_clock::time_point TempTime_s; //临时的时间

		bool isHighPrecision = false;
		TimeMeasure timeMeasure;

		std::vector<std::chrono::system_clock::time_point> TimerContainer; //计时器 集合(Container)
		std::vector<std::chrono::steady_clock::time_point> TimerContainer_s; //计时器 集合(Container)

	public:
		Timers(TimeMeasure tms = tms::sec)
		{
			if (tms != tms::sec) { //高精度
				InitTime_s = GetTime_s();
				TimerContainer_s.push_back(InitTime_s);
				isHighPrecision = true;
				this->timeMeasure = tms;
			}
			else {
				InitTime = GetTime();
				TimerContainer.push_back(InitTime);
				this->timeMeasure = tms;
			}
		}

	public:
		static std::chrono::system_clock::time_point GetTime();
#define 获取时间 GetTime
	
		void AddTimer();
		void AddTimer(std::chrono::system_clock::time_point& time);
		void AddTimer(std::chrono::system_clock::time_point&& time);
#define 添加时间戳 AddTimer

		void SetTimer(std::chrono::system_clock::time_point& time, int Location);
		void SetTimer(std::chrono::system_clock::time_point&& time, int Location);
#define 设置时间戳 SetTimer
		
		std::chrono::system_clock::time_point GetTimer(int Location);
#define 获取时间戳 GetTimer

	public:
		std::chrono::steady_clock::time_point GetTime_s();
#define 获取时间_高精度 GetTime_s

		void AddTimer_s();
		void AddTimer_s(std::chrono::steady_clock::time_point& time);
		void AddTimer_s(std::chrono::steady_clock::time_point&& time);
#define 添加时间戳_高精度 AddTimer_s

		void SetTimer_s(std::chrono::steady_clock::time_point& time, int Location);
		void SetTimer_s(std::chrono::steady_clock::time_point&& time, int Location);
#define 设置时间戳_高精度 SetTimer_s

		std::chrono::steady_clock::time_point GetTimer_s(int Location);
#define 获取时间戳_高精度 GetTimer_s
	
	public:
		long long ComputationFirstToEndInterval();
		long long ComputationFrontToBackInterval();
		long long ComputationInterval(int LocationBegin, int LocationEnd);
#define 计算前后间隔 ComputationFrontToBackInterval
#define 计算首尾间隔 ComputationFirstToEndInterval
#define 计算间隔 ComputationInterval

		// tms: 时间计量 / time: 时间 / transformLaterTms: 转换后的时间计量
		// return 转换后的时间
		static long long TransformTimes(long long& time, bool& isSucceed, TimeMeasure tms = tms::sec, TimeMeasure transformLaterTms = tms::ms);
		static long long TransformTimes(long long&& time, bool& isSucceed, TimeMeasure tms = tms::sec, TimeMeasure transformLaterTms = tms::ms);
		static long long TransformTime(long long& time, TimeMeasure tms = tms::sec, TimeMeasure transformLaterTms = tms::ms);
		static long long TransformTime(long long&& time, TimeMeasure tms = tms::sec, TimeMeasure transformLaterTms = tms::ms);
		static bool TransformTimes(long long& time, TimeMeasure tms = tms::sec, TimeMeasure transformLaterTms = tms::ms);
#define 时间转换 TransformTime
#define 时间转换_s TransformTime_s
		
		static void sleep_s(long long ms);
		static void sleep(long long sec);
#define 延迟_毫秒 sleep_s
#define 延迟_秒 sleep

	public:
		std::vector<std::chrono::system_clock::time_point> GetTimerContainer();
		std::vector<std::chrono::steady_clock::time_point> GetTimerContainer_s();
		int GetTimerSize();
		int GetTimerSize_s();

	};
}
/*
Tool
*/

#endif