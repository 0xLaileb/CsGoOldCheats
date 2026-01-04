DWORD m_iHealth;
DWORD m_iTeamNum;
DWORD dwLocalPlayer;
DWORD dwGlowObjectManager;
DWORD m_iCrosshairId;
DWORD dwEntityList;

bool Load_Classes() {
	m_iHealth = 0x100;
	m_iTeamNum = 0xF4;

	//client_panorama.dll
	dwLocalPlayer = memorys.FindPattern(
		DLL_Client.dwBase, 
		DLL_Client.dwSize, 
		(PBYTE)"\x8D\x34\x85\x00\x00\x00\x00\x89\x15\x00\x00\x00\x00\x8B\x41\x08\x8B\x48\x04\x83\xF9\xFF", 
		(const char*)"xxx????xx????xxxxxxxxx");//0xCFAA3C;

	//client_panorama.dll
	dwGlowObjectManager = memorys.FindPattern(
		DLL_Client.dwBase,
		DLL_Client.dwSize,
		(PBYTE)"\xA1\x00\x00\x00\x00\xA8\x01\x75\x4B",
		(const char*)"x????xxxx");//0x524D518;
	m_iCrosshairId = 0xB3AC;

	//client_panorama.dll
	dwEntityList = memorys.FindPattern(
		DLL_Client.dwBase,
		DLL_Client.dwSize,
		(PBYTE)"\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8",
		(const char*)"x????xxxxx????xx");//0x4D0D0A4;
	DWORD m_iHealth;
	DWORD m_iTeamNum;
	DWORD dwLocalPlayer;
	DWORD dwGlowObjectManager;
	DWORD m_iCrosshairId;
	DWORD dwEntityList;
	if (m_iHealth && m_iTeamNum && dwLocalPlayer && dwGlowObjectManager && m_iCrosshairId && dwEntityList)
		return true;
	else {
		return false;
	}
}