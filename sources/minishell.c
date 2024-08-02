/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:33:51 by zel-khad          #+#    #+#             */
/*   Updated: 2024/08/02 22:36:28 by aogbi            ###   ########.fr       */
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
	t_list	*list;
	t_export	*env_list;
	char	*line;
	extern char **environ;

	cmd_ = NULL;
	env_list = malloc(sizeof(t_export));
	env_list->env = array_alloc(environ);
	env_list->export = NULL;
	int i;
	i = find_index_from_env(env_list->env, "SHLVL", 1);
	if (i > 0)
	{
		line = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(env_list->env[i] + 6) + 1));
		free(env_list->env[i]);
		env_list->env[i] = line;
	}
	while (1)
	{
		line = readline(COLOR_BOLD GRN"➜ minishell__v1 ✗ "RESET);
		if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		token = gettoken(line);
		// if(chech_quoting(token) == false)
		// {
		// 	ft_putstr_fd("zash: syntax error near unexpected token\n", 2);
		// 	continue;
		// }
        // puts("=================== stract token ======================");
		// printlist(token);
        cmd_ = malloc(sizeof(t_cmd));
        cmd_ = NULL;
		generet_cmd(token, &cmd_);
        // puts("=================== stract cmd ======================");
		// printlist_(cmd_);
		list = merge(cmd_, environ);
		// char *type = ((t_red *)((t_list *)((t_ogbi *)list->content)->output_files)->content)->value;
		// printf("%s\n", type);
		if (env_list->env)
			pipex(list, env_list);
		ft_lstclear(&list, merge_free);
		ft_free_herdoc(list);
        freelist_(cmd_);
	    freelist(token);
	}
	clear_history();
}
