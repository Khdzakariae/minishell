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

void	printlist_(t_cmd *head)
{
	t_cmd	*current;

	int i = 0;
	current = head;
	while (current != NULL)
	{
		printf("-----> type %d\n", current->type);
		while (current->value[i])
		{
			printf("-----> value %s\n", current->value[i]);
			i++;
			/* code */
		}
		
		current = current->next;
	}
	printf("\n");
}
int count_word(t_token **tmp)
{
    
    int count_word = 0;
    while ((*tmp))
    {
        if ((*tmp)->type == WORD)
            count_word++;
        else if ((*tmp)->type != SPACE_)
            break;
        *tmp = (*tmp)->next;
    }
    return count_word;
}

t_cmd *generate_tab_cmd(t_cmd *cmd_, t_token *token, int count)
{
    int i = 0;
    cmd_->type = WORD;
    while (i < count)
    {
        if (token->type == WORD)
        {
            cmd_->value[i] = ft_strcpy(&cmd_->value[i], token->value);
            i++;
        }
        token = token->next;
    }
    cmd_->value[i] = NULL;
    return cmd_;
}



t_cmd *generet_cmd(t_token *token, t_cmd *cmd_)
{
    t_token *tmp;
    t_token *tmp1;
    int count = 0;
    tmp = token;
    tmp1 = token;
    while (tmp)
    {
        if (tmp1->type == WORD)
        {
            count = count_word(&tmp);
            add_node_(&cmd_);
            cmd_->value = malloc((count + 1) * sizeof(char *));
            cmd_ = generate_tab_cmd(cmd_, tmp1, count);
			
        }
			// exit(20);
        if (tmp == NULL)
            break;
        tmp = tmp->next;
    }
    return cmd_;
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
		printlist(token);
		puts("===========================");
		cmd_ = generet_cmd(token, cmd_);
		printlist_(cmd_);

		// builtins(token);
		freelist(token);
		usleep(50);
	}
	clear_history();
}
