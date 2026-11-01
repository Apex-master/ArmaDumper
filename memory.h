#pragma once

#include "includes.h"

class memory
{
private:
	DWORD GetProcessID();

public:
	uintptr_t game_base_address;
	HANDLE game_handle;
	HWND game_window;
	DWORD game_pid;

	bool Initialize();
}; inline memory mem;



template<typename type>
inline type Read(uintptr_t address)
{
	type data = {};
	if (ReadProcessMemory(mem.game_handle, reinterpret_cast<LPCVOID>(address), &data, sizeof(type), nullptr))
	{
		return data;
	}
	else
	{
		return type{}; 
	}
}

template <typename T>
inline bool ReadBuffer(uintptr_t address, T* buffer, SIZE_T size)
{
	return ReadProcessMemory(mem.game_handle, reinterpret_cast<LPCVOID>(address), buffer, size, nullptr) != 0;
}

template<typename type>
inline bool Write(uintptr_t address, type value)
{
	return WriteProcessMemory(mem.game_handle, reinterpret_cast<LPVOID>(address), &value, sizeof(type), nullptr) != 0;
}