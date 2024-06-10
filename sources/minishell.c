#include <minishell.h>
void parse_ampersand(t_token **token, char *line, int *i) 
{
    if (line[*i + 1] == '&') 
	{
        add_node(token, NULL, AND);
        (*i)++;
    }
    else 
        add_node(token, NULL, AMPERSAND);
}

void parse_pipe(t_token **token, char *line, int *i) {
    if (line[*i + 1] == '|')
	{
        add_node(token, NULL, OR);
        (*i)++;
	}
    else 
        add_node(token, NULL, PIPE);
}

void parse_symbol(t_token **token, char symbol, char *line, int *i) 
{

	if (symbol == '(')


    if (symbol == '(' || symbol == ')')
        add_node(token, NULL, (symbol == '(') ? LEFT_PARENTHESES : RIGHT_PARENTHESES);
    else if (symbol == '\\') 
        add_node(token, NULL, BACKSLASH);
    else if (symbol == '"') 
        add_node(token, NULL, DOUBLE_QUOTATION);
    else if (symbol == '\'')
        add_node(token, NULL, SINGLE_QUOTATION);
    else if (symbol == '$') 
        add_node(token, NULL, DOLLAR_SIGN);
    else if (symbol == '&') 
        parse_ampersand(token, line, i);
    else if (symbol == '>') 
        add_node(token, NULL, SORTIE);
    else if (symbol == '<') 
        add_node(token, NULL, ENTREE);
    else if (symbol == '|') 
        parse_pipe(token, line, i);

}


int	extract_word(t_token **token, char *line, int i)
{
	int		start;
	char	*whitespace;
	char	*symbols;

	start = i;
	whitespace = " \t\r\n\v";
	symbols = " <|>&()'\"";
	while (line[i] && !ft_strchr(whitespace, line[i]) && !ft_strchr(symbols,
			line[i]))
		i++;
	add_node(token, ft_substr(line, start, (size_t)(i - start)), WORD);
	while (line[i] && ft_strchr(whitespace, line[i]))
		i++;
	return (i);
}

t_token	*gettoken(char *line)
{
	t_token	*token;
	int		i;
	char	*whitespace;
	char	*symbols;

	token = NULL;
	i = 0;
	whitespace = " \t\r\n\v";
	symbols = " <|>&()'\"";
	while (line[i] && ft_strchr(whitespace, line[i]))
		i++;
	while (line[i])
	{
		if (!ft_strchr(symbols, line[i]) && !ft_strchr(whitespace, line[i]))
			i = extract_word(&token, line, i) - 1;
		else
			parse_symbol(&token, line[i], line, &i);
		i++;
	}
	return (token);
}

void	printList(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		printf("-----> type %d\n", current->type);
		printf("-----> value %s\n", current->value);
		current = current->next;
	}
	printf("\n");
}

void	minishell(void)
{
	int		id;
	t_token	*token;
	char	*line;

	while (1)
	{
		line = readline(COLOR_BOLD GRN "➜ minishell__v1 ✗ ");
		chech_Quoting(line);
		token = gettoken(line);
		// printList(token);
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
