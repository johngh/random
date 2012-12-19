#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#include <Windows.h>
#include <Winreg.h>


#define BUFFER 8192

char ReadReg(void){
 
   // char folder[MAX_KEY];
   char folder[2048];
    
   DWORD dwType,
         dwSize = sizeof(folder) - 1;
 
   if (SHGetValue(HKEY_LOCAL_MACHINE,
              "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",
              "Common Startup",
              &dwType,
              folder,
              &dwSize) != ERROR_SUCCESS);
    {
    MessageBox(NULL,
               "Error.\n",
               "Error while reading:", // Titolo del messagebox
               MB_OK);
    }
 
    folder[dwSize / sizeof(folder[0])] = TEXT('\0');
     
    printf("%s\n", folder);
}


int main()
{
        int answer = ReadReg();
	// char value[255];
	// DWORD BufferSize = BUFFER;
	// RegGetValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "SystemRoot", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);
	// std::cout << value << std::endl;
	system("pause");
}
