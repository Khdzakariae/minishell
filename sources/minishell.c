/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:33:51 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/13 22:03:35 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	printlist(t_token *head)
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
	t_token	*token;
	char	*line;

	while (1)
	{
		line = readline(COLOR_BOLD "➜ minishell__v1 ✗ ");
		if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		chech_quoting(line);
		token = gettoken(line);
		// builtins(token);
		printlist(token);
		freelist(token);
		usleep(50);
	}
	clear_history();
}
