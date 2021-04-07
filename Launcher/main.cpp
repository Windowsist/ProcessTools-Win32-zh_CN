﻿
#include "pch.h"

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nShowCmd)
{
    StringTableInit(hInstance);
    wchar_t pathmdfn[260], pathfn[260], cmdl[260], pathdir[260];
    GetModuleFileNameW(hInstance, pathmdfn, 260);
    {
        UINT baselen = lstrlenW(pathmdfn) - 1;
        while (pathmdfn[baselen] != L'\\' && baselen)
        {
            baselen--;
        }
        baselen++;
        cmdl[0] = L'\"';
        lstrcpynW(pathfn, pathmdfn, baselen + 1);
        lstrcpynW(cmdl + 1, pathmdfn, baselen + 1);
        lstrcpynW(pathdir, pathmdfn, baselen + 1);
        lstrcpyW(pathmdfn + lstrlenW(pathmdfn) - 3, L"ini");
        GetPrivateProfileStringW(L"LaunchApp", L"AppPath", nullptr, pathfn + baselen, 260 - baselen, pathmdfn);
        GetPrivateProfileStringW(L"LaunchApp", L"WorkingDirectory", nullptr, pathdir + baselen, 260 - baselen, pathmdfn);
        GetPrivateProfileStringW(L"LaunchApp", L"CommandLine", nullptr, cmdl + baselen + 1, 259 - baselen, pathmdfn);
    }
    if (!CreateProcessW(pathfn, cmdl, nullptr, nullptr, FALSE, 0, nullptr, pathdir, &_STARTUPINFOW(), &_PROCESS_INFORMATION()))
    {
        LPWSTR info = new wchar_t[(size_t)lstrlenW(szCfgFile) + lstrlenW(pathmdfn) + lstrlenW(szProgram) + lstrlenW(pathfn) + lstrlenW(szCmdLine) + lstrlenW(cmdl) + lstrlenW(szDirectory) + lstrlenW(pathdir) + 1];
        lstrcpyW(info, szCfgFile);
        lstrcatW(info, pathmdfn);
        lstrcatW(info, szProgram);
        lstrcatW(info, pathfn);
        lstrcatW(info, szCmdLine);
        lstrcatW(info, cmdl);
        lstrcatW(info, szDirectory);
        lstrcatW(info, pathdir);
        MessageBoxW(nullptr, info, szStartFailed, MB_ICONERROR);
        delete[] info;
    }
    return 0;
}