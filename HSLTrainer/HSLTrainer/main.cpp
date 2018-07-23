#include <Windows.h>

#include "resource.h"
#include "Trainer.h"

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Trainer *t = Trainer::instance();

	switch (uMsg) {
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				TCHAR szBuffer[11];
				case IDC_HEALTH:
					::GetDlgItemText(hDlg, IDC_EDIT1, szBuffer, 10);
					if (wcslen(szBuffer))
						t->ModifyHealth(_wtoi(szBuffer));
					break;
				case IDC_ARMOUR:
					::GetDlgItemText(hDlg, IDC_EDIT1, szBuffer, 10);
					if (wcslen(szBuffer))
						t->ModifyArmour(_wtoi(szBuffer));
					break;
				case IDC_MELEEATT:
					::GetDlgItemText(hDlg, IDC_EDIT1, szBuffer, 10);
					if (wcslen(szBuffer))
						t->ModifyAttack(Trainer::MELEE, _wtoi(szBuffer));
					break;
				case IDC_RANGEDATT:
					::GetDlgItemText(hDlg, IDC_EDIT1, szBuffer, 10);
					if (wcslen(szBuffer))
						t->ModifyAttack(Trainer::RANGED, _wtoi(szBuffer));
					break;
				case IDC_MAGICATT:
					::GetDlgItemText(hDlg, IDC_EDIT1, szBuffer, 10);
					if (wcslen(szBuffer))
						t->ModifyAttack(Trainer::MAGIC, _wtoi(szBuffer));
					break;
				case IDC_MELEEDMG:
					::GetDlgItemText(hDlg, IDC_EDIT1, szBuffer, 10);
					if (wcslen(szBuffer))
						t->ModifyDamage(Trainer::MELEE, _wtoi(szBuffer));
					break;
				case IDC_RANGEDDMG:
					::GetDlgItemText(hDlg, IDC_EDIT1, szBuffer, 10);
					if (wcslen(szBuffer))
						t->ModifyDamage(Trainer::RANGED, _wtoi(szBuffer));
					break;
				case IDC_MAGICDMG:
					::GetDlgItemText(hDlg, IDC_EDIT1, szBuffer, 10);
					if (wcslen(szBuffer))
						t->ModifyDamage(Trainer::MAGIC, _wtoi(szBuffer));
					break;
				case IDC_GODMODE:
					if (!t->IsGodmode()) {
						t->EnableGodmode(true);
						::SetDlgItemText(hDlg, IDC_GODMODE, TEXT("Disable Godmode"));
					} else {
						t->EnableGodmode(false);
						::SetDlgItemText(hDlg, IDC_GODMODE, TEXT("Enable Godmode"));
					}
				case IDC_RESET:
					t->Reset();
					break;
			}
			break;

		case WM_CLOSE:
			return TRUE;

		case WM_DESTROY:
			return TRUE;
	}

	return FALSE;
}

void StartInterface(LPVOID lpParam) {
	HINSTANCE hInstance = reinterpret_cast<HINSTANCE>(lpParam);
	::DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);

	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0) != 0) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}

BOOL APIENTRY DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			::CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(StartInterface), reinterpret_cast<LPVOID>(hInstDll), 0, NULL);
			break;
	}

	return TRUE;
}