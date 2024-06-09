#include <minishell.h>
 


t_token *gettoken(char *line)
{
    t_token *token = NULL;

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
                add_node(&token, "(");
            else if (line[i] == ')')
                add_node(&token, ")");
            else if (line[i] == '\\')
                add_node(&token, "\\");
            else if (line[i] == '"')
                add_node(&token, "\"");
            else if (line[i] == '\'')
                add_node(&token, "'");
            else if (line[i] == '$')
                add_node(&token, "$");
            else if (line[i] == '&' && line[i + 1] == '&')
            {
                add_node(&token, "&&");
                i++;
            }
            else if (line[i] == '&')
                add_node(&token, "&");
            else if (line[i] == '>')
                add_node(&token, ">");
            else if (line[i] == '<')
                add_node(&token, "<");
            else if (line[i] == '|' && line[i + 1] == '|')
            {
                add_node(&token, "||");
                i++;
            }
            else if (line[i] == '|')
                add_node(&token, "|");
        }
        i++;
    }
    return(token);
}

void printList(t_token* head) {
    t_token* current = head;

    while (current != NULL) {
        printf("%s\n", current->type);
        current = current->next;
    }
    printf("\n");
}

void minishell()
{
    int id ;
    char *line;
    t_token *token;

    while (1)
    {
        line = readline(COLOR_BOLD GRN "➜ minishell__v1 ✗ ");
        chech_Quoting(line);
        token = gettoken(line);
        printList(token);
        freeList(token);
        usleep(50);


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







