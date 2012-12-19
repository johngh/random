#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    LPWSTR *szArgList;
    int argCount;

    char *my_args = GetCommandLine();

    szArgList = CommandLineToArgvW(my_args, argCount);
    if (szArgList == NULL) {
        MessageBox(NULL, L"Unable to parse command line", L"Error", MB_OK);
        return 10;
    }

    for(int i = 0; i < argCount; i++) {
        MessageBox(NULL, szArgList[i], L"Arglist contents", MB_OK);
    }

    LocalFree(szArgList);
    return 0;
}

