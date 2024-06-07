#include <minishell.h>

void gettoken(char *line)
{
    int i ;
    
    char *whitespace;
    char *symbols;

    i = 0;
    whitespace = " \t\r\n\v";
    symbols = "<|>&()";

    while(line[i] && ft_strchr(whitespace, line[i]))
        i++;
    while (line[i])
    {
        /* code */
    }
    
    printf("the index of token is %d\n", i);

}


void minishell()
{
    int id ;
    char *line;

    while (1)
    {
        line = readline(COLOR_BOLD GRN "➜ minishell__v1 ✗ ");
        gettoken(line);


        // char *argvrc[] = {cmd, NULL , NULL};
        // char *envVec[] = {NULL};
        // id = fork();
        // if (id == 0)
        // {   
        //     if(execve(cmd, argvrc, NULL) == -1)
        //         perror("not fount");
        // }
        // else
        //     wait(NULL);
    }
}


int main ()
{
    minishell();
    
}




