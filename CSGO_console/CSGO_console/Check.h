using namespace std;

bool aim = false;
bool wh = false;
bool wh_battle_royale = false;
bool autoshot = false;
bool bunnyhop = false;
int bone_aim = 0;

void Checker()
{
	void musor_8973793921938312();
	for (;;)
	{
		Sleep(30);

		if (GetAsyncKeyState(VK_NUMPAD0)) {
			aim = !aim;
			void musor_344423423243();
			Sleep(250);
		}
		else if (GetAsyncKeyState(VK_NUMPAD1)) {
			wh = !wh;
			wh_battle_royale = false;
			void musor_793247634267432432();
			Sleep(250);
		}
		else if (GetAsyncKeyState(VK_NUMPAD2)) {
			wh_battle_royale = !wh_battle_royale;
			void musor_3796342764237423();
			wh = false;
			Sleep(250);
		}
		else if (GetAsyncKeyState(VK_NUMPAD3)) {
			void musor_3479432724374279423();
			autoshot = !autoshot;
			Sleep(250);
		}
		else if (GetAsyncKeyState(VK_NUMPAD4)) {
			void musor_3479432724374279423();
			bunnyhop = !bunnyhop;
			Sleep(250);
		}
		void musor_344387432784874238423();
		if (GetAsyncKeyState(VK_NUMPAD8)) bone_aim = 8;//ГОЛОВА
		else if (GetAsyncKeyState(VK_NUMPAD7)) bone_aim = 4;//ТЕЛО
		Sleep(30);
	}
}

bool check = false;
bool funcs[6];

void Write_Text() {
	setlocale(0, "rus");

	funcs[1] = false;
	funcs[2] = false;
	funcs[3] = false;
	funcs[4] = false;
	funcs[5] = false;

	int musor_4987472384932942905932052();
	while (1) 
	{
		if (check == true) {
			if (funcs[1] != aim ||
				funcs[2] != wh ||
				funcs[3] != wh_battle_royale ||
				funcs[4] != autoshot ||
				funcs[5] != bunnyhop)//&& !wh && !wh_battle_royale && !autoshot)//all FALSE
			{
				Sleep(100);
				funcs[1] = aim;
				funcs[2] = wh;
				funcs[3] = wh_battle_royale;
				funcs[4] = autoshot;
				funcs[5] = bunnyhop;
			}
			else {
				Sleep(500);
				continue;
			}
		}
		else {
			Sleep(100);
			funcs[1] = aim;
			funcs[2] = wh;
			funcs[3] = wh_battle_royale;
			funcs[4] = autoshot;
			funcs[5] = bunnyhop;
		}

		system("cls");
		int musor_3497327949382432423();
		system("color 2");

		cout << "{FREE} -> [Cat-X]" << endl;
		int musor_34273427984974297842();
		Sleep(1);
		cout << "___________________________________" << endl;
		int musor_32474327843289742389243();
		Sleep(1);
		cout << "{NUMPAD_0} [АИМ] -> " << (aim ? "ON" : "OFF") << endl;
		int musor_384734783748934297883492();
		Sleep(1);
		cout << "{NUMPAD_1} [ВХ] -> " << (wh ? "ON" : "OFF") << endl;
		int musor_325532532532532();
		Sleep(1);
		cout << "{NUMPAD_2} [ВХ - DANGER ZONE] -> " << (wh_battle_royale ? "ON" : "OFF") << endl;
		int musor_4535435345345335();
		Sleep(1);
		cout << "{NUMPAD_3} [АВТОШОТ] -> " << (autoshot ? "ON" : "OFF") << endl;
		Sleep(1);
		cout << "{NUMPAD_4} [БАННИ-ХОП] -> " << (bunnyhop ? "ON" : "OFF") << endl;
		Sleep(1);
		int musor_4554543534354354();
		cout << "___________________________________" << endl;
		Sleep(1);
		cout << "{SPACE} -> АКТИВАЦИЯ 'БАННИ-ХОП'" << endl;
		Sleep(1);
		void musor_3794732423();
		cout << "{CAPSLOCK} -> АКТИВАЦИЯ 'АИМ'" << endl;
		Sleep(1);
		int musor_342796342674327479423();
		cout << "{NUMPAD_8} -> АИМ-ГОЛОВА" << endl;
		Sleep(1);
		int musor_34297634297634297423();
		cout << "{NUMPAD_7} -> АИМ-ТЕЛО" << endl;
		Sleep(1);
		int musor_342389427987432987243();
		cout << "___________________________________" << endl;
		Sleep(1);
		int musor_34298734979783897432();
		cout << "[>_<] -> ОБНОВЛЕНО: 17.07.19 | 19:00 (МСК)" << endl;
		Sleep(1);
		int musor_378347843929432897438943();
		cout << "[>_<] -> АВТОР: #Lako" << endl;
		Sleep(1);
		int musor_3489734234297849782394382();
		cout << "[>_<] -> ПОДПИСЫВАЙСЯ: vk.com/official_funcode" << endl;

		if (check == false) {
			check = true;
		}

		Sleep(50);
	}
}