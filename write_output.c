    // char *arguments;
    // arguments = lpCmdLine[0] ? lpCmdLine : usage;

    FILE *fp;

    char *op_file = "c:\\output.txt";
    // char *op_file = "c:\\bing";

    fp = fopen (op_file,"w");

    if (fp == NULL) {
        char error[2048];
        sprintf(error, "%s: Can't write '%s': %s\n",
            my_name, op_file, strerror(errno));
        MessageBox(NULL, TEXT(error), TEXT("Write failed"), MB_OK);
        return 1;
    }

    fprintf(fp, "%s\n", "Some message");

    fclose (fp);
