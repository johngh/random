#include <windows.h>
#include <stdio.h>

int main()
{

	char value[255];

	DWORD dword_size = 1025;


	if (
		RegGetValue(HKEY_CLASSES_ROOT, "ssh", "PuTTY Path", RRF_RT_ANY, NULL, (PVOID)&value, &dword_size)
		== ERROR_SUCCESS
	) {

		printf("Value Read is %s\n", value);

	} else {
		
		printf("Didn't read value.\n");

	}

}
