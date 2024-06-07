#include <minishell.h>

void gettoken(char *line)
{
    t_token *token;
    int i ;
    
    char *whitespace;
    char *symbols;

    i = 0;
    whitespace = " \t\r\n\v";
    symbols = "<|>&()'\"";

    while(line[i] && ft_strchr(whitespace, line[i]))
        i++;
    while (line[i])
    {
        if (ft_strchr(symbols, line[i]))
        {
            if (line[i] == '(')
                add_node(token, LEFT_PARENTHESES);
            else if (line[i] == ')')
                add_node(token, RIGHT_PARENTHESES);
            else if (line[i] == '\\')
                add_node(token, BACKSLASH);
            else if (line[i] == '"')
                add_node(token, DOUBLE_QUOTATION);
            else if (line[i] == '\'')
                add_node(token, SINGLE_QUOTATION);
            else if (line[i] == '$')
                add_node(token, DOLLAR_SIGN);
            else if (line[i] == '&')
                add_node(token, AMPERSAND);
            else if (line[i] == '>')
                add_node(token, SORTIE);
            else if (line[i] == '<')
                add_node(token, ENTREE);
        }
        i++;
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




