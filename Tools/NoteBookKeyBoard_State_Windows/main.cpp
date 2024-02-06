#include <iostream>

//#include "ToolsLibrary.h"
#include "../../ToolsDll/ToolsDll/ToolsDll.h"

int main()
{
	//提升为管理员权限
	WCHAR path[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, path, MAX_PATH);
	WindowsSystemOperation::GainAdminPrivileges(path);

	char tempState;

	std::cout << "打开/关闭 笔记本键盘(Y/N): " << std::endl;

	std::cin >> tempState;
	
	//打开
	if (tempState == 'y' || tempState == 'Y')
	{
		system("sc config i8042prt start = auto");
	}
	//关闭
	//else if (-32767 == GetAsyncKeyState('N'))
	else if (tempState == 'n' || tempState == 'N')
	{
		system("sc config i8042prt start = disabled");
	}

	std::cout << "请重启电脑！！！" << std::endl;
	std::cout << "请重启电脑！！！" << std::endl;
	std::cout << "请重启电脑！！！(Enter 确认知晓)" << std::endl;

	std::cin.get();

	return 0;
}