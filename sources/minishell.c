#include <minishell.h>

t_token *gettoken(char *line)
{
    t_token *token = NULL;

    int i ;
    int start = 0;
    int end = 0 ;    
    char *whitespace;
    char *symbols;

    i = 0;
    whitespace = " \t\r\n\v";
    symbols = "<|>&()'\"";

    while(line[i] && ft_strchr(whitespace, line[i]))
        i++;
    while (line[i])
    {
        if (line[i] != ' ')
            start++;
        else if ((line[i] >= 97) && (line[i] <= 122))
            end++;
        if (ft_strchr(symbols, line[i]))
        {
            if (line[i] == '(')
                add_node(&token, NULL, LEFT_PARENTHESES);
            else if (line[i] == ')')
                add_node(&token, NULL, RIGHT_PARENTHESES);
            else if (line[i] == '\\')
                add_node(&token, NULL, BACKSLASH);
            else if (line[i] == '"')
                add_node(&token,NULL, DOUBLE_QUOTATION);
            else if (line[i] == '\'')
                add_node(&token, NULL, SINGLE_QUOTATION);
            else if (line[i] == '$')
                add_node(&token, NULL, DOLLAR_SIGN);
            else if (line[i] == '&' && line[i + 1] == '&')
            {
                add_node(&token, NULL, AND);
                i++;
            }
            else if (line[i] == '&')
                add_node(&token, NULL, AMPERSAND);
            else if (line[i] == '>')
                add_node(&token, NULL, SORTIE);
            else if (line[i] == '<')
                add_node(&token, NULL, ENTREE);
            else if (line[i] == '|' && line[i + 1] == '|')
            {
                add_node(&token, NULL, OR);
                i++;
            }
            else if (line[i] == '|')
                add_node(&token, NULL, PIPE);
        }
        i++;
    }
    return(token);
}

void printList(t_token* head) {
    t_token* current = head;

    while (current != NULL) {
        printf("%d\n", current->type);
        current = current->next;
    }
    printf("\n");
}

void minishell()
{
    int id ;
    t_token *token;
    char *line;

    while (1)
    {
        line = readline(COLOR_BOLD GRN "➜ minishell__v1 ✗ ");
        chech_Quoting(line);
        token = gettoken(line);
        printList(token);
        // freeList(token);
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







