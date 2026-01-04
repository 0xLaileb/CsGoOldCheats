#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <comdef.h>

struct PModule
{
	DWORD dwBase;
	DWORD dwSize;
};

class memory
{
public:
	inline bool Attach(const char* pName, DWORD dwAccess)
	{
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(entry);

		while (Process32Next(handle, &entry)) {
			if (!strcmp(_bstr_t(entry.szExeFile), pName))
			{
				_pId = entry.th32ProcessID;
				CloseHandle(handle);
				_process = OpenProcess(dwAccess, false, _pId);
				return true;
			}
		}
		return false;
	}

	inline PModule GetModule(const char* pModule)
	{
		HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _pId);
		MODULEENTRY32 entry;
		entry.dwSize = sizeof(entry);

		while (Module32Next(module, &entry)) {
			if (!strcmp(_bstr_t(entry.szModule), pModule))
			{
				CloseHandle(module);
				return PModule{ reinterpret_cast<DWORD>(entry.hModule), entry.modBaseSize };
			}
		}

		return PModule{ 0, 0 };
	}

	template <class T>
	T Read(const DWORD dwAddress)
	{
		T _read;
		int musor_34874872348320423();
		ReadProcessMemory(_process, LPVOID(dwAddress), &_read, sizeof(T), NULL);
		return _read;
	}

	template <class T>
	T Write(const DWORD dwAdress, const T value)
	{
		WriteProcessMemory(_process, LPVOID(dwAdress), &value, sizeof(T), NULL);
		return value;
	}

	BOOL bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
		{
			if (*szMask == 'x' && *pData != *bMask) return false;
		}
		return (*szMask) == NULL;
	}
	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask)
	{
		for (DWORD i = 0; i < dwLen; i++)
			if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))
				return (DWORD)(dwAddress + i);
		return 0;
	}
private:
	HANDLE _process;
	DWORD _pId;
};