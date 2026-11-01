#include "memory.h"

bool memory::Initialize()
{
	while (!GetProcessID())
	{
		printf("[+] Waiting for Arma's PID\n");
		Sleep(1000);
	}

	game_pid = GetProcessID();
	printf("[+] Got Armas PID: %i\n", game_pid);

	game_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, game_pid);

	if (!game_handle)
	{
		printf("[-] Failed to get Arma's handle..\n");
		return false;
	}

	HMODULE hModule;
	DWORD cbNeeded;
	if (EnumProcessModules(game_handle, &hModule, sizeof(hModule), &cbNeeded)) {
		MODULEINFO moduleInfo;
		if (GetModuleInformation(game_handle, hModule, &moduleInfo, sizeof(moduleInfo))) {
			game_base_address = reinterpret_cast<uintptr_t>(moduleInfo.lpBaseOfDll);
		}
	}

	printf("[+] Memory initialized\n");

	return true;
}

int GetProcessThreadNumByID(DWORD dwPID)
{
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return 0;

	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(pe32);
	BOOL bRet = ::Process32First(hProcessSnap, &pe32);;
	while (bRet)
	{
		if (pe32.th32ProcessID == dwPID)
		{
			::CloseHandle(hProcessSnap);
			return pe32.cntThreads;
		}
		bRet = ::Process32Next(hProcessSnap, &pe32);
	}
	return 0;
}

DWORD memory::GetProcessID()
{
	DWORD dwRet = 0;
	DWORD dwThreadCountMax = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe32);
	do
	{
		if (wcscmp(pe32.szExeFile, L"arma3_x64.exe") == 0)

		{
			DWORD dwTmpThreadCount = GetProcessThreadNumByID(pe32.th32ProcessID);

			if (dwTmpThreadCount > dwThreadCountMax)
			{
				dwThreadCountMax = dwTmpThreadCount;
				dwRet = pe32.th32ProcessID;
			}
		}
	} while (Process32Next(hSnapshot, &pe32));
	CloseHandle(hSnapshot);
	return dwRet;
}