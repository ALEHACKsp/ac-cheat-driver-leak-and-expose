
#pragma once
#include <Windows.h>
#include <stdio.h>
#include "communication.hpp"

namespace driver
{
	__int64(__fastcall* NtCompositionInputThread)(void* arg01, void* arg02) = nullptr;

	bool setup()
	{
		LoadLibraryA("user32.dll");
		LoadLibraryA("win32u.dll");

		const HMODULE win32u = GetModuleHandleA("win32u.dll");

		if (!win32u)
			return false;

		*(void**)&NtCompositionInputThread = GetProcAddress(win32u, "NtCompositionInputThread");

		return NtCompositionInputThread;
	}

	bool send_cmd(cmd_t* cmd, void* arg02 = NULL)
	{
		RtlSecureZeroMemory(cmd, 0);
		NtCompositionInputThread(cmd, arg02);
		return cmd->success;
	}
}
