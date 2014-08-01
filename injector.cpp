#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	DWORD pid;
	HWND hwnd;
	//Search for the RS window
	hwnd = FindWindow(NULL, L"Rocksmith 2014");
	
	if (!hwnd)
	{	
		cout << "Window not found!\n";
		cin.get();
	}
	else
	{
		GetWindowThreadProcessId(hwnd, &pid);
		//Get the appropriate PID
		HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
		if (!phandle)
		{
			cout << "Could not get handle!\n";
			cin.get();
		}
		else
		{
			//55 8B EC 83 EC 08 8B 47 14 <-- ORIGINAL!
			//B0 01 C3 90 EC 08 RB 47 17 <-- HACKED!
			
			cout << "Ok, now let's try that signature stuff... \n";
			DWORD sigAddr = 0x0054B5C0;	//Initial RAM Address TODO: Search for the HEX string
			byte sig[4] = { 0xB0, 0X01, 0XC3, 0X90 };
			DWORD newdatasize = sizeof(sig[0]);

			for (int i = 0; i < 4; i++)
			{
				if (WriteProcessMemory(phandle, (void*)(sigAddr + i), &sig[i], newdatasize, NULL))
					cout << "GOOD SIGN " << i << endl;
				else
				{
					cout << "Frak! Something went wrong! \n";
					break;
				}
			}

			system("pause");
			return 0;
		}
	}
}