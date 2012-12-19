#include <stdio.h>
#include <string.h>

int main(void)
{
    char writablestring[] = "The C Programming Language";
    char *token = strtok(writablestring, " ");
    if (token != NULL) {
        printf("[%s]\n", token);
        return 0;
    }
    printf("No args :-(\n");
    return 1;
}
