#include <minishell.h>


int main ()
{

    while (1)
    {
        char *line = readline(COLOR_BOLD GRN "➜ minishell__v1 ✗ ");
         char *cmd = "/usr/bin/ls";
        char *argvrc[] = {cmd, NULL , NULL};
        char *envVec[] = {NULL};
        if(execve(cmd, argvrc, NULL) == -1)
            perror("not fount");
    }

}



