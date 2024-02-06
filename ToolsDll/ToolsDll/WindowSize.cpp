#include "pch.h" //DLL标准
#include <utility> //DLL标准
#include <limits.h> //DLL标准

#include "WindowSize.h"

int WindowSize::GetWindowSizeWidth() const
{
	return this->WindowWidth_Size;
}

int WindowSize::GetWindowSizeHeight() const
{
	return this->WindowHeight_Size;
}