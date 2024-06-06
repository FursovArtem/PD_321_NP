#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<CommCtrl.h>
#include<cstdio>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hSpin = GetDlgItem(hwnd, IDC_SPIN_PREFIX);
		SendMessage(hSpin, UDM_SETRANGE32, 0, 32);
	}
	break;
	case WM_COMMAND:
	{
		HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
		HWND hEditPrefox = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
		switch (LOWORD(wParam))
		{
		case IDC_IPADDRESS:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				//BYTE = 8 bit
				//WORD = 2 BYTE = 16 bit;
				//DWORD = 4 BYTE = 32 bit;
				//QWORD = 8 BYTE = 64 bit;
				//TBYTE = 10 BYTE = 80 bit;
				//DQWORD = 16 BYTE = 128 bit;
				DWORD dwAddress = 0;
				//https://learn.microsoft.com/en-us/windows/win32/controls/ipm-getaddress
				SendMessage(hIPaddress, IPM_GETADDRESS, 0, (LPARAM)&dwAddress);
				BYTE first = FIRST_IPADDRESS(dwAddress);
				BYTE dw_prefix = 0;
				if (first < 128)dw_prefix = 8;
				else if (first < 192)dw_prefix = 16;
				else if (first < 224)dw_prefix = 24;
				CHAR sz_prefix[5]{};
				sprintf(sz_prefix, "%i", dw_prefix);
				SendMessage(hEditPrefox, WM_SETTEXT, 0, (LPARAM)sz_prefix);
			}
		}
		break;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}