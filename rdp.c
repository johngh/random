#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char* get_rdp_cmd(char* userinfo, char* c_params,
                    char* host, char* port) {
    char* cmd = malloc(32768);

    cmd = "/v ";
    
    if(userinfo) {
        strncat(cmd, userinfo, strlen(userinfo) );
        strncat(cmd, "@", 1);
    }

    if(host) {
        strncat(cmd, host, strlen(host) );
    }

    if(port) {
        strncat(cmd, ":", 1);
        strncat(cmd, port, strlen(port) );
    }

    return cmd;
}

int show_usage(char *my_name) {
    char usage[2048];
    sprintf(usage, "Usage: %s ssh://[USER@]HOST[:PORT]", my_name);
    MessageBox(NULL, TEXT(usage), TEXT("Error"), MB_OK);
    return 0;
}
    
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {

    char *putty_cmd = "C:\\Program Files\\PuTTY\\putty.exe";
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
        show_usage(my_name);
        return 2;
    }

    char *first_arg = strtok(arguments, " ");

    if ( arguments[0] == '"' ) {
        first_arg++;
        first_arg[strlen(first_arg)-1] = 0;
    }

    // Shouldn't get this - already checked arg_len
    // if (first_arg == NULL) {
    //     return 1;
    // }

    if( strncmp(first_arg, "ssh://", 6) != 0 ) {    

        char error[2048];
        sprintf(error, "%s: Argument '%s' not recognized as ssh:// URL\n",
            my_name, first_arg);
        MessageBox(NULL, TEXT(error), TEXT("Error"), MB_OK);
        return 1;

    }

    // sshURI        =  "ssh:" hier-part
    // hier-part     =  "//" authority path-abempty
    // authority     =  [ [ ssh-info ] "@" ] host [ ":" port ]
    // host          =  <as specified in [RFC3986]>
    // port          =  <as specified in [RFC3986]>
    // path-abempty  =  <as specified in [RFC3986]>
    // ssh-info      =  [ userinfo ] [";" c-param *("," c-param)]
    // userinfo      =  <as specified in [RFC3986]>
    // c-param       =  paramname "=" paramvalue
    // paramname     =  *( ALPHA / DIGIT / "-" )
    // paramvalue    =  *( ALPHA / DIGIT / "-" )
    char* host = NULL;
    char* port = NULL;
    char* userinfo = NULL;
    char* c_params = NULL;
    char *p, *t1, *t2; // temp
    char* cmd;

    p = first_arg;
    p += 6; // Trim off leading ssh://
    t1 = p + strlen(p) - 1;
    if( *t1 == '/' ) {
        *t1 = '\0';
    }

    t1 = strstr(p, "@");
    if( t1 != NULL ) {
        // ssh-info part present
        *t1 = '\0';
        userinfo = p;
        p = t1+1;

        t2 = strstr(userinfo, ";");
        if( t2 != NULL ) {
            *t2 = '\0';
            c_params = t2+1;
        }
    }

    host = p;
    t1 = strstr(p, ":");
    if( t1 != NULL ) {
        // port present
        *t1 = '\0';
        port = t1+1;
    }

    cmd = get_putty_cmd(userinfo, c_params, host, port);

    char running[2048];
    sprintf(running, "%s %s", putty_cmd, cmd);
    // MessageBox(NULL, TEXT(running), TEXT("Running"), MB_OK);

    // STARTUPINFO startup_info;
    // memset(&startup_info, 0, sizeof(startup_info));

    STARTUPINFO startup_info = {sizeof(STARTUPINFO)};
    PROCESS_INFORMATION proc_info;

    if (! CreateProcess( putty_cmd, cmd,
        NULL, NULL, 0, 0, NULL, NULL,
        &startup_info, &proc_info) ) {
        MessageBox(NULL, TEXT("Fail"), TEXT("Error"), MB_OK);
    }

    free(cmd);

    return 0;

}

