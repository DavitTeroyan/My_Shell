#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include "builtin.h"
#include "parser.h"


void sigint_handler(int sig)
{
    printf("\n");
    printf("my_shell> ");
    fflush(stdout);
}


void sigchld_handler(int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0);
}


void sigterm_handler(int sig)
{
    printf("\nShell terminated\n");
    exit(0);
}


int main()
{
    signal(SIGINT, sigint_handler);
    signal(SIGCHLD, sigchld_handler);
    signal(SIGTERM, sigterm_handler);


    char line[256];
    char *argv[20];

    char prompt[50] = "my_shell";


    while(1)
    {

        printf("%s> ", prompt);
        fflush(stdout);


        if (fgets(line, sizeof(line), stdin) == NULL)
            break;


        parse(line, argv);


        if (argv[0] == NULL)
            continue;


        if (run_builtin(argv, prompt))
            continue;



        pid_t pid = fork();


        if(pid == 0)
        {
            signal(SIGINT, SIG_DFL);

            execvp(argv[0], argv);

            perror("Command not found");

            exit(1);
        }


        else if(pid > 0)
        {
            waitpid(pid, NULL, 0);
        }


        else
        {
            perror("fork failed");
        }

    }


    return 0;
}
