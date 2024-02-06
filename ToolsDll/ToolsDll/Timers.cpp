#include "pch.h" //DLL标准
#include <utility> //DLL标准
#include <limits.h> //DLL标准

#include "Timers.h"

void Timers::Initial()
{
	if (this->InitialTime == 0)
	{
		this->TimerContainer[0] = GetTime();
	}
}

void Timers::AddNewTimer(int elementCout)
{
	std::cout << this->TimerContainer.size() << std::endl;
	//传入值时：根据 elementCout 将节点扩充到指定个数
	for (int tempInt = this->TimerContainer.size();
		tempInt < elementCout; tempInt++)
	{
		this->TimerContainer.push_back(GetTime());
	}

	if (elementCout == 1)
	{
		//不传入值时：一次添加一个节点
		this->TimerContainer.push_back(GetTime());
	}
}

float Timers::GetTime()
{
	return GetTickCount64();
}

void Timers::SetTimer(int TimerElement)
{
	this->TimerContainer[--TimerElement] = GetTime();
}

void Timers::SetTimer(int TimerElement, float Time)
{
	this->TimerContainer[--TimerElement] = Time;
}

void Timers::GetTimer(int& Timer, int TimerElement)
{
	Timer = this->TimerContainer[--TimerElement];
}

int Timers::GetTimer(int TimerElement)
{
	return this->TimerContainer[--TimerElement];
}


void Timers::ComputeTimerDistance(float PastTime, float NewTime, float& Distance)
{
	Distance = PastTime - NewTime;
}

float Timers::ComputeTimerDistance(float PastTime, float NewTime)
{
	return PastTime - NewTime;
}

void Timers::MsecToSecond(float Msec, int& Time)
{
	Time = Msec / 1000.f;
}

int Timers::MsecToSecond(float Msec)
{
	return Msec / 1000.f;
}

void Timers::FirstAndEndCompare(float& Time)
{
	Time = *(--this->TimerContainer.end()) - *this->TimerContainer.begin();
}

float Timers::FirstAndEndCompare()
{
	return *(--this->TimerContainer.end()) - *this->TimerContainer.begin();
}

std::vector<float> Timers::GetTimerContainer()
{
	return this->TimerContainer;
}

void Timers::MsecToSecond_S(float Msec, int& Time)
{
	Time = Msec / 1000.f;
}

int Timers::MsecToSecond_S(float Msec)
{
	return Msec / 1000.f;
}

float Timers::GetTime_S()
{
	return GetTickCount64();
}

Timers Timers::operator=(const Timers& other)
{
	this->InitialTime = other.InitialTime;
	this->TempTime = other.TempTime;
	this->TimerContainer = other.TimerContainer;

	return *this;
}

bool Timers::operator==(const Timers& other)
{
	if (this->InitialTime == other.InitialTime && \
		this->TempTime == other.TempTime && \
		this->TimerContainer == other.TimerContainer)
	{
		return true;
	}
	else
		return false;
}

/*
Tool
*/
