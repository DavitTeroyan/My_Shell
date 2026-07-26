#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"


int run_builtin(char **argv, char *prompt)
{

    // exit
    if (strcmp(argv[0], "exit") == 0)
    {
        exit(0);
    }


    // help
    if (strcmp(argv[0], "help") == 0)
    {
        printf("Built-in commands:\n");
        printf("cd\n");
        printf("exit\n");
        printf("help\n");
        printf("pwd\n");
        printf("echo\n");
        printf("clear\n");
        printf("setenv\n");
        printf("unsetenv\n");
        printf("chprompt\n");

        return 1;
    }


    // cd
    if (strcmp(argv[0], "cd") == 0)
    {
        if (argv[1] == NULL)
            printf("cd: missing argument\n");
        else
            chdir(argv[1]);

        return 1;
    }


    // pwd
    if (strcmp(argv[0], "pwd") == 0)
    {
        char cwd[1024];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s\n", cwd);

        return 1;
    }


    // echo
    if (strcmp(argv[0], "echo") == 0)
    {
        int i = 1;

        while (argv[i] != NULL)
        {
            printf("%s ", argv[i]);
            i++;
        }

        printf("\n");

        return 1;
    }


    // clear
    if (strcmp(argv[0], "clear") == 0)
    {
        system("clear");

        return 1;
    }


    // setenv
    if (strcmp(argv[0], "setenv") == 0)
    {
        if (argv[1] == NULL || argv[2] == NULL)
        {
            printf("Usage: setenv NAME VALUE\n");
        }
        else
        {
            setenv(argv[1], argv[2], 1);
        }

        return 1;
    }


    // unsetenv
    if (strcmp(argv[0], "unsetenv") == 0)
    {
        if (argv[1] == NULL)
        {
            printf("Usage: unsetenv NAME\n");
        }
        else
        {
            unsetenv(argv[1]);
        }

        return 1;
    }


    // chprompt
    if (strcmp(argv[0], "chprompt") == 0)
    {
        if (argv[1] != NULL)
        {
            strcpy(prompt, argv[1]);
        }

        return 1;
    }


    return 0;
}
