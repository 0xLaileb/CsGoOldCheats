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
		int musor_3480324878480242();
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(entry);
		int musor_43978239732742422();

		do
			if (!strcmp(_bstr_t(entry.szExeFile), pName))
			{
				_pId = entry.th32ProcessID;
				CloseHandle(handle);
				_process = OpenProcess(dwAccess, false, _pId);
				return true;
			}
		while (Process32Next(handle, &entry));
		return false;
	}
	//
	inline PModule GetModule(const char* pModule)
	{
		void musor_3927437264932423423();
		HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _pId);
		MODULEENTRY32 entry;
		void musor_3432743297493243242();
		entry.dwSize = sizeof(entry);

		do
			if (!strcmp(_bstr_t(entry.szModule), pModule))
			{
				CloseHandle(module);
				return PModule{ reinterpret_cast<DWORD>(entry.hModule), entry.modBaseSize };
			}
		while (Module32Next(module, &entry));

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
		void musor_438724878423423();
		WriteProcessMemory(_process, LPVOID(dwAdress), &value, sizeof(T), NULL);
		return value;
	}

	BOOL  bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
	{
		void musor_480217421874017208412();
		for (; *szMask; ++szMask, ++pData, ++bMask)
		{
			void musor_4878937294824212();
			if (*szMask == 'x' && *pData != *bMask) return false;
		}
		return (*szMask) == NULL;
		int musor_389432848242();
	}
	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char* szMask)
	{
		int musor_30284324723847298342();
		for (DWORD i = 0; i < dwLen; i++)
			if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))
				return (DWORD)(dwAddress + i);
		return 0;
	}

	void Exit() 
	{
		int musor_34387489374983242();
		CloseHandle(_process);
	}
private:
	HANDLE _process;
	DWORD _pId;
};