#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char* get_putty_cmd(char* userinfo, char* c_params,
                    char* host, char* port) {
    char* cmd = malloc(32768);

    cmd = "\"C:\\Program Files\\PuTTY\\putty.exe\" -ssh ";
    
    if(port) {
        strncat(cmd, "-P ", 3);
        strncat(cmd, port, strlen(port) );
        strncat(cmd, " ", 1);
    }

    if(userinfo) {
        strncat(cmd, userinfo, strlen(userinfo) );
        strncat(cmd, "@", 1);
    }

    if(host) {
        strncat(cmd, host, strlen(host) );
    }

    return cmd;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

    char arguments[2048];
    char my_name[2048];

    strcpy(arguments, lpCmdLine);
    strcpy(my_name, GetCommandLine());

    int arg_len = strlen(arguments);
    int cmd_len = strlen(my_name);
    int chop_len = cmd_len - arg_len;
    
    my_name[chop_len] = 0;
    while( isspace(my_name[chop_len-1]) ) {
        my_name[chop_len-1] = 0;
        chop_len--;
    }
    
    if (arg_len == 0) {
        char usage[2048];
        sprintf(usage, "Usage: %s ssh://[USER@]HOST[:PORT]", my_name);
        MessageBox(NULL, TEXT(usage), TEXT("Error"), MB_OK);
        return 2;
    }
    
    char *first_arg = strtok(arguments, " ");
    if (first_arg != NULL) {
        char running[2048];
        sprintf(running, "[%s]\n", first_arg);
        MessageBox(NULL, TEXT(first_arg), TEXT("Running"), MB_OK);
        return 0;
    }
    
    return 1;

}

