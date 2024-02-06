#pragma once
#ifndef _CHARHANDLEOFCONFIGFILE_H
#define _CHARHANDLEOFCONFIGFILE_H

#include <string>
#include <map>
#include <set>
#include <vector>

#include "ToolsDll.h"

namespace StringHandling
{
	//配置文件的字符处理
	class TOOLSDLL_API CharHandleOfConfigFile
	{
	private:
		//区域设置的总数
		int RegionCount = 0;

		//字符"=" 前/后字符串
		std::map<std::string, std::string> mapStr;

		/*[ConfigName] ：区域设置项名称
		* "[]"
		*/
		std::string RegionConfigItemNameStr;
		//[ConfigName]：区域设置项名称注释
		std::string RegionConfigItemName_AnnotationStr;
		//[ConfigName] 区域设置项中所有 strConfig 字符串的容器
		std::map<std::string, std::map<std::string, std::string>> vecStrContainer;
		//空字符串 位置
		std::set<int> vecStrNullRegionLocation;

	public:
		CharHandleOfConfigFile()
			: mapStr(),
			RegionConfigItemNameStr(""), RegionConfigItemName_AnnotationStr(""),
			vecStrContainer()
		{
			//Initialize();
		}

		/* 未完成
		* 保证有且只有一次初始化，返回 执行成功与否
		*/
		//bool Initialize();

		/* 区域设置 等号字符串分离
		* 传入一条配置字符串
		*/
		bool StringParsing_Equalsign(std::string& str);

		/* 区域设置 中括号字符串分离
		* 传入一个区域的字符串
		*/
		bool StringParsing_BracketVec(std::vector<std::string>& vecStr);

	public:
		/* 获取 mStr(First) : 字符"=" 前 / 后的字符串
		* 前置 StringParsing_Equalsign(string)
		*/
		std::map<std::string, std::string> GetMapString() const;

		//获取 vecStrContainer 集合: [ConfigName] 区域中所有 str的容器
		std::map<std::string, std::map<std::string, std::string>> GetStringContainer() const;
		//获取 strConfigName 设置名称
		std::string GetRegionConfigItemNameStr() const;
		//获取 strConfigNameAnnotation 设置名称注释
		std::string GetRegionConfigItemName_AnnotationStr() const;
		//获取 区域设置项
		std::string GetRegionConfigItemName() const;

	public:
		/*  写入区域设置项
		* 传入区域设置项和详细配置的字符串
		*/
		bool WriteConfigItem(std::map<std::string, std::string>& RegionConfigItem, std::vector<std::string>& vecStr);
		/*  写入区域设置项
		* 传入区域设置项和详细配置的字符串
		*/
		bool WriteConfigItem(std::map<std::string, std::string>& RegionConfigItem, 
			std::map<std::string, std::map<std::string, std::string>>& setStr);

		/* 向指定区域设置添加配置
		* 传入区域设置项的字符串
		*/
		bool AddWriteConfig(std::string& strRegionItem, std::string& strConfigItem);

		//区域识别
		bool RegionRecognition(std::vector<std::string>& vecStr);
	};

}

#endif _CHARHANDLEOFCONFIGFILE_H