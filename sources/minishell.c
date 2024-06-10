#include <minishell.h>


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
