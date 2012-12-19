#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{

    FILE *fp;

    fp = fopen ("c:\\output.txt","w");

    if (fp == NULL) {
        printf ("File not created: errno = %d\n", errno);
        return 1;
    }

    int i;

    for (i = 1; i < argc; i++) fprintf(fp, "%s ", argv[i]);

    fprintf (fp, "\n");

    fclose (fp);
    printf ("Please check c:\\output.txt\n");
    return 0;

}
