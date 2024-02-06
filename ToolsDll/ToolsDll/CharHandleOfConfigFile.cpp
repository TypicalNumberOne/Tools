#include "pch.h" //DLL标准
#include <utility> //DLL标准
#include <limits.h> //DLL标准

#include "CharHandleOfConfigFile.h"
/*
bool StringHandling::CharHandleOfConfigFile::Initialize()
{
	return false;
};
*/

bool StringHandling::CharHandleOfConfigFile::StringParsing_Equalsign(std::string& str)
{
	//传入 str 不为空时
	if (!str.empty())
	{
		//根据传入 str 元素个数对临时变量 tempStrFirst/tempStrSecond初始化
		int tempFirst = str.find("="); //找到 "=" 号的元素位置
		int tempSecond = str.length() - 1 - tempFirst; //去掉 "="号后剩余的元素个数
		std::string tempStrFirst(tempFirst, ' '); //初始化
		std::string tempStrSecond(tempSecond, ' '); //初始化

		//保存 "="号之 前的字符
		for (int i = 0; i < tempFirst; i++)
		{
			//一对一保存
			tempStrFirst[i] = str[i];
		}
		//保存 "="号之 后的字符
		for (int i = tempFirst + 1; i < str.length(); i++) //到 end 前一位
		{
			//从0开始保存, str从"="之后的元素
			//i - tempFirst = 1
			//i - tempFirst - 1 = 0
			tempStrSecond[i - tempFirst - 1] = str[i];
		}

		//保存到 map
		this->mapStr.insert(make_pair(tempStrFirst, tempStrSecond));

		return true;
	}

	return false;
}

bool StringHandling::CharHandleOfConfigFile::StringParsing_BracketVec(std::vector<std::string>& vecStr)
{
	//vector 不为空时
	if (!vecStr.empty())
	{
		//初始化
		int vecStrNotNullCount = 0; //vecStr 中非空的统计
		std::set<int> temp_mapStrNullRegionLocation; //vecStr 中空字符的位置
		for (int temp_Int = 0; temp_Int < vecStr.size(); temp_Int++)
		{
			//字符串非空时，递增统计
			if (!vecStr[temp_Int].empty())
			{
				vecStrNotNullCount++;
			}
			else //字符串为空时
			{
				temp_mapStrNullRegionLocation.insert(temp_Int); //记录空字符串位置
			}
		}
		//保存 空字符串位置
		this->vecStrNullRegionLocation = temp_mapStrNullRegionLocation;

		//初始化
		std::string temp_StrFirst = *vecStr.cbegin(); //区域配置的首字符串
		int temp_StrLeftBracketLocation = temp_StrFirst.find('['); //左括号的元素位置
		int temp_StrRigthBracketLocation = temp_StrFirst.find(']'); //右括号的元素位置
		int temp_StrColonLocation = temp_StrFirst.find(':'); //冒号的元素位置

		//解析 [ConfigName]: 设置名称
		//保存ConfigNmae
		std::string temp_StrRegionConfigItemName = ""; //临时 区域设置项名称
		for (int temp_Int = temp_StrLeftBracketLocation;
			temp_Int < temp_StrRigthBracketLocation; temp_Int++)
		{
			temp_StrRegionConfigItemName[temp_Int] = temp_StrFirst[temp_Int];
		}
		this->RegionConfigItemNameStr = temp_StrRegionConfigItemName; //保存 区域设置项名称
		//保存 注解
		std::string temp_StrRegionConfigItemName_Annotation = ""; //临时 区域设置项名称注释
		for (int temp_Int = temp_StrColonLocation;
			temp_Int < temp_StrFirst.size(); temp_Int++)
		{
			temp_StrRegionConfigItemName_Annotation[temp_Int] = temp_StrFirst[temp_Int];
		}
		this->RegionConfigItemName_AnnotationStr = temp_StrRegionConfigItemName_Annotation;

		//解析 除首字符串外 的所有字符串
		for (int temp_Int = 1; temp_Int < vecStr.size(); temp_Int++)
		{
			//不解析空字符串
			if (!this->vecStrNullRegionLocation.count(temp_Int))
			{
				//解析 "="字符串
				StringParsing_Equalsign(vecStr[temp_Int]);

				//查找对应顺序的 strConfig 配置字符串
				//将需要处理的 "="字符串保存到 vecStrContainer 区域设置容器中
				std::map<std::string, std::string> temp_mapContainer =
					((*this->GetStringContainer().find(std::to_string(temp_Int))).first,
					(*this->GetStringContainer().find(std::to_string(temp_Int))).second);
				this->vecStrContainer.insert(
					make_pair(GetRegionConfigItemName(), temp_mapContainer)
				);
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

std::map<std::string, std::string> StringHandling::CharHandleOfConfigFile::GetMapString() const
{
	return this->mapStr;
}

std::map<std::string, std::map<std::string, std::string>> StringHandling::CharHandleOfConfigFile::GetStringContainer() const
{
	return this->vecStrContainer;
}

std::string StringHandling::CharHandleOfConfigFile::GetRegionConfigItemNameStr() const
{
	return this->RegionConfigItemNameStr;
}

std::string StringHandling::CharHandleOfConfigFile::GetRegionConfigItemName_AnnotationStr() const
{
	return this->RegionConfigItemName_AnnotationStr;
}

std::string StringHandling::CharHandleOfConfigFile::GetRegionConfigItemName() const
{
	return "[" + this->RegionConfigItemNameStr + "]: " + this->RegionConfigItemName_AnnotationStr;
}

bool StringHandling::CharHandleOfConfigFile::WriteConfigItem(std::map<std::string, std::string>& RegionConfigItem, std::vector<std::string>& vecStr)
{
	return false;
}

bool StringHandling::CharHandleOfConfigFile::WriteConfigItem(std::map<std::string, std::string>& RegionConfigItem, std::map<std::string, std::map<std::string, std::string>>& setStr)
{
	return false;
}

bool StringHandling::CharHandleOfConfigFile::AddWriteConfig(std::string& strRegionItem, std::string& strConfigItem)
{
	return false;
}