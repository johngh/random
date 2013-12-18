#include <windows.h>
#include <stdio.h>

int main()
{
	char value[255];
	HKEY hive_key;
	LONG return_status;
	DWORD dword_type = REG_SZ;
	DWORD dword_size = 1025;

	return_status = RegOpenKeyEx(HKEY_CLASSES_ROOT, "ssh", 0,  KEY_ALL_ACCESS, &hive_key);

	char key_name[257];
	strcpy(key_name, "ssh");

	char string_name[257];
	strcpy(string_name, "PuTTY Path");
	
	if (return_status == ERROR_SUCCESS) {

		return_status = RegQueryValueEx(hive_key, string_name, NULL, &dword_type,(LPBYTE)&value, &dword_size);

		if (return_status == ERROR_SUCCESS) {

			printf("Value Read is %s\n", value);

		} else {
		
			printf("Didn't read value.\n");

		}

	} else {

		printf("Didn't open key.\n");

	}
	RegCloseKey(hive_key);

	return_status = RegGetValue(HKEY_CLASSES_ROOT, key_name, string_name, RRF_RT_ANY, NULL, (PVOID)&value, &dword_size);

	if (return_status == ERROR_SUCCESS) {

		printf("Value Read is %s\n", value);

	} else {
		
		printf("Didn't read value.\n");

	}

}
