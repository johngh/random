#include <stdio.h>
#include <string.h>

int main(void)
{
    char writablestring[] = "The C Programming Language";
    char *token = strtok(writablestring, " ");
    while(token != NULL) {
        printf("[%s]\n", token);
        token = strtok(NULL, " ");
    }
    return 0;
}
