#pragma once
#ifndef _STRINGHELPER_H
#define _STRINGHELPER_H

#include "ToolsDll.h"

#include <string>


//×Ö·û´¦Àí
namespace StringHandling
{
#if 0
		static std::string UnicodeToANSI(const std::wstring& from);
		static std::string UnicodeToUTF8(const std::wstring& from);

		static std::wstring UTF8ToUnicode(const std::string& from);
		static std::string UTF8ToANSI(const std::string& from);

		static std::string ANSIToUTF8(const std::string& from);
#endif
		TOOLSDLL_API std::wstring ANSIToUnicode(const std::string& from);
}

#endif