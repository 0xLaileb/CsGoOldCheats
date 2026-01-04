#include <thread>
#include <iostream>
#include <Windows.h>
#include <string>
#include <process.h> 
#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>
#include "Memory.h"
using namespace std;

memory memorys;
PModule DLL_Client;
PModule DLL_Engine;
bool wh = false;
bool wh_battle_royale = false;
bool autoshot = false;

DWORD m_iHealth = 0x100;
DWORD m_iTeamNum = 0xF4;
DWORD m_iCrosshairId = 0xB3AC;
DWORD dwLocalPlayer = 0xCFAA3C;
DWORD dwGlowObjectManager = 0x524D518;
DWORD dwEntityList = 0x4D0D0A4;

void Checker()
{
	unsigned int drive_type = GetDriveType(NULL);
	char VolumeNameBuffer[256];
	char FileSystemNameBuffer[256];
	unsigned long drive_sn;
	GetVolumeInformationA((LPCSTR)"C:\\", VolumeNameBuffer, 256, &drive_sn, NULL, NULL, FileSystemNameBuffer, 256);
	if (drive_sn != 1447520546) return; //ЪЫоз
	while (true)
	{
		Sleep(500);

		if (GetAsyncKeyState(VK_NUMPAD1)) {
			wh = !wh;
			wh_battle_royale = false;
		}
		if (GetAsyncKeyState(VK_NUMPAD2)) {
			wh_battle_royale = !wh_battle_royale;
			wh = false;
		}
		if (GetAsyncKeyState(VK_NUMPAD3)) {
			autoshot = !autoshot;
		}
		if (GetAsyncKeyState(VK_NUMPAD0)) {
			break;
		}
	}
}

void Wh()
{
	typedef struct GOD_t {
		float r;
		float g;
		float b;
		float a;
		uint8_t unk[16];
		bool m_bRenderWhenOccluded;
		bool m_bRenderWhenUnoccluded;
		bool m_bFullBloom;
		int GlowStyle;
		uint8_t unk2[10];
	} GOD_t;

	unsigned int drive_type = GetDriveType(NULL);
	char VolumeNameBuffer[256];
	char FileSystemNameBuffer[256];
	unsigned long drive_sn;
	GetVolumeInformationA((LPCSTR)"C:\\", VolumeNameBuffer, 256, &drive_sn, NULL, NULL, FileSystemNameBuffer, 256);
	if (drive_sn != 1447520546) return; //ЪЫоз
	while (true)
	{
		if (!wh && !wh_battle_royale) {
			Sleep(500);
			continue;
		}
		else {
			Sleep(3);
		}

		DWORD play_BASE = memorys.Read<DWORD>(DLL_Client.dwBase + dwLocalPlayer);
		if (!play_BASE) continue;

		int play_HP = memorys.Read<int>(play_BASE + m_iHealth);
		if (!play_HP) continue;

		int play_TEAM = memorys.Read<int>(play_BASE + m_iTeamNum);
		if (!play_TEAM) continue;

		int glow = memorys.Read<int>(DLL_Client.dwBase + dwGlowObjectManager);
		if (!glow) continue;

		int glowCount = memorys.Read<int>(DLL_Client.dwBase + dwGlowObjectManager + 0x4);
		if (!glowCount) continue;

		for (int i = 0; i < glowCount; i++)
		{
			if (!wh && !wh_battle_royale) break;
			DWORD gEntity = memorys.Read<DWORD>(glow + 0x38 * i);
			if (!gEntity) continue;

			int Ent_Hp = memorys.Read<int>(gEntity + m_iHealth);
			if (!Ent_Hp) continue;

			int Ent_Team = memorys.Read<int>(gEntity + m_iTeamNum);
			if (!Ent_Team) continue;

			if (!wh_battle_royale)
				if (Ent_Team == play_TEAM) continue;

			static GOD_t Glow = memorys.Read<GOD_t>(glow + (i * 0x38) + 0x4);

			if (Ent_Team == 3) {
				if (!wh_battle_royale) {
					Glow.r = 255;
					Glow.g = 0;
					Glow.b = 0;
					Glow.a = 1;
				}
				else {
					Glow.r = 255;
					Glow.g = 100;
					Glow.b = 0;
					Glow.a = 1;
				}
			}
			else if (Ent_Team == 2) {
				if (!wh_battle_royale) {
					Glow.r = 255;
					Glow.g = 0;
					Glow.b = 0;
					Glow.a = 1;
				}
				else {
					Glow.r = 255;
					Glow.g = 100;
					Glow.b = 0;
					Glow.a = 1;
				}
			}

			if (Ent_Team == 3 || Ent_Team == 2) {
				Glow.m_bRenderWhenOccluded = true;
				Glow.m_bRenderWhenUnoccluded = false;

				memorys.Write<GOD_t>(glow + (i * 0x38) + 0x4, Glow);//38
			}
		}
	}
}

void AutoShot()
{
	unsigned int drive_type = GetDriveType(NULL);
	char VolumeNameBuffer[256];
	char FileSystemNameBuffer[256];
	unsigned long drive_sn;
	GetVolumeInformationA((LPCSTR)"C:\\", VolumeNameBuffer, 256, &drive_sn, NULL, NULL, FileSystemNameBuffer, 256);
	if (drive_sn != 1447520546) return; //ЪЫоз
	while (1)
	{
		if (!autoshot) {
			Sleep(500);
			continue;
		}
		else {
			Sleep(15);
		}

		DWORD pLocal = memorys.Read<DWORD>(DLL_Client.dwBase + dwLocalPlayer);
		DWORD lHealth = memorys.Read<DWORD>(pLocal + m_iHealth);
		if (!lHealth || lHealth < 0) continue;
		DWORD lTeamNum = memorys.Read<DWORD>(pLocal + m_iTeamNum);

		DWORD lCrosshairId = memorys.Read<DWORD>(pLocal + m_iCrosshairId);
		if (!lCrosshairId || lCrosshairId > 64) continue;

		DWORD play_BASE = memorys.Read<int>(DLL_Client.dwBase + dwEntityList + (lCrosshairId - 1) * 0x10);
		if (!play_BASE) continue;

		int play_HP = memorys.Read<int>(play_BASE + m_iHealth);
		if (!play_HP || play_HP < 0) continue;

		int play_TEAM = memorys.Read<int>(play_BASE + m_iTeamNum);
		if (!play_TEAM || play_TEAM == lTeamNum) continue;

		Sleep(6);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(30);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
}

int main()
{
	MoveWindow(GetConsoleWindow(), 0, 0, 0, 0, TRUE);
	SetConsoleTitle("");
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	unsigned int drive_type = GetDriveType(NULL);
	char VolumeNameBuffer[256];
	char FileSystemNameBuffer[256];
	unsigned long drive_sn;
	GetVolumeInformationA((LPCSTR)"C:\\", VolumeNameBuffer, 256, &drive_sn, NULL, NULL, FileSystemNameBuffer, 256);
	if (drive_sn != 1447520546) return 0; //ЪЫоз

	setlocale(0, "rus");
	while (!memorys.Attach("csgo.exe", PROCESS_ALL_ACCESS))
	{
		Sleep(1000);
	}
	DLL_Client = memorys.GetModule("client_panorama.dll");
	DLL_Engine = memorys.GetModule("engine.dll");

	thread(Wh).detach();
	Sleep(5);
	thread(AutoShot).detach();
	Sleep(5);
	Checker();
	Sleep(5);

	return 0;
}