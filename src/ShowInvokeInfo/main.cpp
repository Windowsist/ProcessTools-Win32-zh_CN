
#include "main.h"

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nShowCmd)
{
    return (int)DialogBoxParamW(
        hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), nullptr,
        [](HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
            switch (message)
            {
            case WM_INITDIALOG:
            {
                LPWCH env = GetEnvironmentStringsW();
                int envlen = 0;
                for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
                {
                    envlen += lstrlenW(i) + 2;
                }
                LPWSTR envString = new wchar_t[envlen + 1];
                envString[0] = 0;
                for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
                {
                    lstrcatW(envString, i);
                    lstrcatW(envString, L"\r\n");
                }
                SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT1), GetCommandLineW()); //windowsx.h Edit_SetText()
                SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT2), envString);         //windowsx.h Edit_SetText()
                delete[] envString;
            }
                return (INT_PTR)TRUE;
            case WM_COMMAND:
                if (LOWORD(wParam) == IDOK)
                {
                    EndDialog(hDlg, (INT_PTR)0);
                    return (INT_PTR)TRUE;
                }
                break;
            }
            return (INT_PTR)FALSE;
        },
        0L);
}
