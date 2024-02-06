#include "pch.h" //DLL标准
#include <utility> //DLL标准
#include <limits.h> //DLL标准

#include "Counts.h"

//--------------------------class Counts
void Counts::SetHWNDS(HWND hwnd, int count)
{
	this->hwnds[--count] = hwnd;
}

int Counts::GetHWNDCount()
{
	return this->count;
}

void Counts::AddHWND(HWND hwnd)
{
	this->hwnds.push_back(hwnd);
}

/*
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
*/
HWND Counts::GetHWND(int count) const
{
	return this->hwnds[--count];
}

vector<HWND> Counts::GetHWNDS() const
{
	return this->hwnds;
}
