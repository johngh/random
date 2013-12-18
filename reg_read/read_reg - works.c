#include <windows.h>
#include <stdio.h>

int main()
{
	char lszValue[255];
	char value[255];
	HKEY hKey;
	LONG returnStatus;
	DWORD dwType=REG_SZ;
	DWORD dwSize=255;
	DWORD BufferSize = 393216;
	// returnStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", NULL,  KEY_ALL_ACCESS, &hKey);
	returnStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0,  KEY_ALL_ACCESS, &hKey);
	if (returnStatus == ERROR_SUCCESS) {

		returnStatus = RegQueryValueEx(hKey, TEXT("SystemRoot"), NULL, &dwType,(LPBYTE)&lszValue, &dwSize);

//		RegGetValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "SystemRoot", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);

		if (returnStatus == ERROR_SUCCESS) {

			printf("Value Read is %s\n", lszValue);

		} else {
		
			printf("Didn't read value.\n");

		}

	} else {

		printf("Didn't read value.\n");
	}
	RegCloseKey(hKey);
	system("pause");
}
