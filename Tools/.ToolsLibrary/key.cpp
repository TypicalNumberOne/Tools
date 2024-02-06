#include "key.h"

using namespace std;

void Key::keys(BYTE bVk)
{
	keybd_event(bVk, 0, 0, 0);
	Sleep(50);
	keybd_event(bVk, 0, KEYEVENTF_KEYUP, 0);
}

bool Key::GetTypingStatus(int i, void(*func)())
{
	if (-32767 == GetAsyncKeyState(i))
	{
		func();
		return true;
	}
	else
		return false;
}

void Key::ExitProcedure(int i, const char* c)
{
	if (-32767 == GetAsyncKeyState(i))
	{
		string str = "taskkill -f -im ";
		string str2 = c;
		string str3 = ".exe";
		string strCount = str + str2 + str3;
		cout << strCount << endl;
		system(strCount.c_str());
	}
}


void Key::keyJudge_Mouse(int i, int i2, int i3)
{
	// (int)MOUSEEVENTF_RIGHTDOWN = 1
	// (int)MOUSEEVENTF_LEFTDOWN = 2
	// (int)MOUSEEVENTF_RIGHTUP = 3
	// (int)MOUSEEVENTF_LEFTUP = 4
	mouse_event(i, 0, 0, 0, 0); 
	Sleep(i3);
	mouse_event(i2, 0, 0, 0, 0); 
	Sleep(i3);
}
