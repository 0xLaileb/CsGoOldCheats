using namespace std;
memory memorys;
PModule DLL_Client;
int rvuh32hiru2 = 3234;
PModule DLL_Engine;

void setViewAngle(DWORD EngineBase, Vector angle) {
	ClampAngles(angle);
	void m_4tbi4jtot4i3oi33b34b();
	NormalizeAngles(angle);

	memorys.Write(EngineBase + dwClientState_ViewAngles, angle);
}
//
Vector getBonePos(int pTargetIn, int bone) {
	Sleep(1);
	void m_34b3ti4job34obi43oji34();
	const int matrix = memorys.Read<int>(pTargetIn + m_dwBoneMatrix);
	void musor_3489743987432423423();
	return Vector
	{
		memorys.Read<float>(matrix + 0x30 * bone + 0xC),
		memorys.Read<float>(matrix + 0x30 * bone + 0x1C),
		memorys.Read<float>(matrix + 0x30 * bone + 0x2C)
	};
	void m_34tbt43ijbuo3h34b33();
}
//
Vector AngelToTarget(int pLocal, int pTargetIn, int boneIndex) {
	Sleep(1);
	void m_bt43jiobo34ji34b4t34();
	const Vector position = memorys.Read<Vector>(pLocal + m_vecOrigin);
	const Vector vecView = memorys.Read<Vector>(pLocal + m_vecViewOffset);
	void m_43tbtijo4ojb43b3b34b3();
	const Vector myView = position + vecView;
	const Vector aimView = getBonePos(pTargetIn, boneIndex);
	void m_34bt43oijbt3jo4boj34b3();
	Vector dst = CalcAngle(myView, aimView).ToVector();

	void m_34tijt4obo4ub3b();
	NormalizeAngles(dst);

	return dst;
}
//
int getTarget(int pLocal, int clientState) {
	Sleep(1);
	int currentTarget = -1;
	float misDist = 360.f;
	void m_43b4iboib4t3jbo3b34t43();

	Vector _viewAngels = memorys.Read<Vector>(clientState + dwClientState_ViewAngles);
	void m_bijobu4h3iub3b343();
	const int playerTeam = memorys.Read<int>(pLocal + m_iTeamNum);

	for (int i = 0; i <= 64; i++)
	{
		void m_bi2jobijo23oi2b2();
		const int target = memorys.Read<int>(DLL_Client.dwBase + dwEntityList + (i - 1) * 0x10);
		if (!target || target < 0) continue;

		const int targetHealth = memorys.Read<int>(target + m_iHealth);
		if (!targetHealth || targetHealth < 0) continue;
		void m_b4i2bi2jii2ob();
		const int targetTeam = memorys.Read<int>(target + m_iTeamNum);

		if (!wh_battle_royale) {
			if (!targetTeam || targetTeam == playerTeam) continue;
		}
		void m_4bt4ijoboij2bjoi2();

		const bool targetDormant = memorys.Read<bool>(target + m_bDormant);
		if (targetDormant) continue;

		Vector angeToTarget = AngelToTarget(pLocal, target, 8/*head index - head_0*/);
		float fov = GetFov(_viewAngels.ToQAngle(), angeToTarget.ToQAngle());
		void m_4b4jioibobi2b2();
		if (fov < misDist && fov <= 20) {
			misDist = fov;
			currentTarget = target;
		}
	}
	return currentTarget;
}
//
void Aim()
{
	while (1)
	{
		void m_34tuojb43buubhbuot34tb3();
		if (!aim) {
			Sleep(350);
			continue;
		}
		else {
			Sleep(30);
		}
		if (!GetAsyncKeyState(VK_CAPITAL)) continue;
		void m_23bojbo2bo2b2oi();
		int pLocal = memorys.Read<int>(DLL_Client.dwBase + dwLocalPlayer);
		if (!pLocal) continue;

		if (!memorys.Read<int>(pLocal + m_iHealth)) continue;
		void m_bk23ibj2ob2jo2b();
		int pEngine = memorys.Read<int>(DLL_Engine.dwBase + dwClientState);
		if (!pEngine) continue;
		void m_bioj4jio2b2();
		int target = getTarget(pLocal, pEngine);
		if (target == -1) continue;

		setViewAngle(pEngine, AngelToTarget(pLocal, target, bone_aim));//8 OR 4
	}
}
//
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
	void m_32bjo23u2u3objbio2();
	while (1)
	{
		void m_2boiju2ob2bo2bb2b();
		if (!wh && !wh_battle_royale) {
			Sleep(350);
			continue;
		}
		else {
			Sleep(10);
		}

		DWORD play_BASE = memorys.Read<DWORD>(DLL_Client.dwBase + dwLocalPlayer);
		if (!play_BASE) continue;

		void m_3bio32jb23oiboib2();
		int play_HP = memorys.Read<int>(play_BASE + m_iHealth);
		if (!play_HP) continue;

		int play_TEAM = memorys.Read<int>(play_BASE + m_iTeamNum);
		if (!play_TEAM) continue;

		void m_23bioj23b3oiboi2bb();
		int glow = memorys.Read<int>(DLL_Client.dwBase + dwGlowObjectManager);
		if (!glow) continue;

		int glowCount = memorys.Read<int>(DLL_Client.dwBase + dwGlowObjectManager + 0x4);
		if (!glowCount) continue;

		for (int i = 0; i < glowCount; i++)
		{
			//Sleep(1);
			if (!wh && !wh_battle_royale) break;
			void m_4bij4bio2jio2b2();
			DWORD gEntity = memorys.Read<DWORD>(glow + 0x38 * i);
			if (!gEntity) continue;

			void m_4tbki4tj4bho43oi33();
			int Ent_Hp = memorys.Read<int>(gEntity + m_iHealth);
			if (!Ent_Hp) continue;

			void m_32bijo32bio2joibjiob();
			int Ent_Team = memorys.Read<int>(gEntity + m_iTeamNum);
			if (!Ent_Team) continue;

			if (!wh_battle_royale)
				if (Ent_Team == play_TEAM) continue;

			void m_4b4ji4ji34jib434();
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
				void m_b4ipj4jbi42bj2ib2();
				Glow.m_bRenderWhenUnoccluded = false;

				memorys.Write<GOD_t>(glow + (i * 0x38) + 0x4, Glow);//38
			}
		}
	}
}
//
void AutoShot() 
{
	while (1)
	{
		void m_3bioj23ijobijo2ibo2();
		if (!autoshot) {
			Sleep(500);
			continue;
		}
		else {
			Sleep(100);
		}

		DWORD pLocal = memorys.Read<DWORD>(DLL_Client.dwBase + dwLocalPlayer);
		void m_32iojubuhor2bhub2hu();
		DWORD lHealth = memorys.Read<DWORD>(pLocal + m_iHealth);
		if (!lHealth || lHealth < 0) continue;
		void m_3bij2jibijo2bijo2();
		DWORD lTeamNum = memorys.Read<DWORD>(pLocal + m_iTeamNum);

		DWORD lCrosshairId = memorys.Read<DWORD>(pLocal + m_iCrosshairId);
		if (!lCrosshairId || lCrosshairId > 64) continue;

		void m_34ij4tbji34toijb();
		DWORD play_BASE = memorys.Read<int>(DLL_Client.dwBase + dwEntityList + (lCrosshairId - 1) * 0x10);
		if (!play_BASE) continue;

		int play_HP = memorys.Read<int>(play_BASE + m_iHealth);
		if (!play_HP || play_HP < 0) continue;

		void m_4b4ijb4ibbiojoibj34();
		int play_TEAM = memorys.Read<int>(play_BASE + m_iTeamNum);
		if (!play_TEAM || play_TEAM == lTeamNum) continue;

		Sleep(5);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		void m_jibiobio3iob3t43();
		Sleep(25);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
}
//
void BunnyHop()
{
	while (1)
	{
		if (!bunnyhop) {
			Sleep(500);
			void musor_3476326478943242();
			continue;
		}
		else {
			Sleep(25);
		}
		void musor_3743980783924709384232();
		DWORD dwMe = memorys.Read<DWORD>(DLL_Client.dwBase + dwLocalPlayer);
		if (GetAsyncKeyState(VK_SPACE) && (memorys.Read<DWORD>(dwMe + m_fFlags) & 0x1 == true)) {
			void musor_32978423949236432();
			memorys.Write<int>(DLL_Client.dwBase + dwForceJump, 5); // прыгаем в игре
			Sleep(50);
			void musor_348632845328();
			memorys.Write<int>(DLL_Client.dwBase + dwForceJump, 4);
		}
	}
}
//
void Start() 
{
	void m_43jbio43uht34ou4tb343tb();
	setlocale(0, "rus");
	while (!memorys.Attach("csgo.exe", PROCESS_ALL_ACCESS))
	{
		void m_4opkb43p3b3jip34();
		Sleep(5);
		system("color 4");
		cout << "{FREE} -> [Cat-X]" << endl;
		cout << "___________________________________" << endl;
		cout << "CS:GO <- ЖДУ ЗАПУСКА!" << endl;
		cout << "___________________________________" << endl;
		void m_bpijt3jib43ib3t3();
		Sleep(1000);
		system("cls");
	}
	DLL_Client = memorys.GetModule("client_panorama.dll");
	void m_4b34jiot43oi4noi3n();
	void musor_48474783248978942342();
	DLL_Engine = memorys.GetModule("engine.dll");
	void m_eibewiobiowebfweb();
	thread(Checker).detach();
	void musor_3428743874324234();
	Sleep(20);
	thread(Aim).detach();
	void m_weijwebijebiwjbb();
	Sleep(20);
	thread(Wh).detach();
	Sleep(20);
	void m_rokpbi3j4jin3();
	thread(AutoShot).detach();
	Sleep(20);
	void m_rokpbi3j4jin3();
	thread(BunnyHop).detach();
	Sleep(20);

	Write_Text();
	void m_b4io3jbjoi43b();
}