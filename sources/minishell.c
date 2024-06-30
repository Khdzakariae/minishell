/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:33:51 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/30 15:49:32 by zel-khad         ###   ########.fr       */
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

void printlist_(t_cmd *head)
{
    t_cmd *current = head;

    while (current != NULL)
    {

        printf("-----> type %d\n", current->type);
        // Print values if present

            int i = 0;
            while ((current->value != NULL) && (current->value[i]))
            {
                printf("-----> value %s\n", current->value[i]);
                i++;
            }
        current = current->next;
    }
    printf("\n");
}

void	minishell(void)
{
	t_cmd	*cmd_;
	t_token	*token;
	char	*line;

	cmd_ = NULL;
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
        puts("=================== stract token ======================");
		printlist(token);
        cmd_ = malloc(sizeof(t_cmd));
        cmd_ = NULL;
		generet_cmd(token, &cmd_);
        puts("=================== stract cmd ======================");
		printlist_(cmd_);
        freelist_(cmd_);
	    freelist(token);

	}
	clear_history();
}
