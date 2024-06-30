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


int count_word(t_token **tmp)
{
    int count_word = 0;
    while ((*tmp) && ((*tmp)->type == WORD || (*tmp)->type == SPACE))
    {
        if ((*tmp)->type == WORD)
            count_word++;
        *tmp = (*tmp)->next;
    }
	puts("=======================================================");
    printf("the cant value is -----> |%d|\n", count_word);
	puts("=======================================================");
    return count_word;
}

char  **generate_tab_cmd(char **cmd_, t_token *token, int count)
{
    int i = 0;
    while (i < count)
    {

        if (token->type == WORD)
        {
            printf("hahowa -- >%s\n",token->value);
            cmd_[i] = ft_strcpy(&cmd_[i], token->value);
            i++;
        }
		// (*cmd_) = (*cmd_)->next;
        token = token->next;
    }
    cmd_[i] = NULL;
    return(cmd_);
}

// void  generate_tab_cmd(t_cmd **cmd_, t_token *token, int count)
// {
//     int i = 0;
//     (*cmd_)->type = WORD;
//     while (i < count)
//     {

//         if (token->type == WORD)
//         {
//             (*cmd_)->value[i] = ft_strcpy(&(*cmd_)->value[i], token->value);
//             i++;
//         }
// 		// (*cmd_) = (*cmd_)->next;
//         token = token->next;
//     }
//     (*cmd_)->value[i] = NULL;
// }

void print_tab(char **tab)
{
    int i = 0;
    while (tab[i])
    {
        printf("tabde[%d] is |%s|\n", i, tab[i]);
        i++;
    }
}

void free_(char **tab)
{
    int i = 0;
    while(tab[i])
    {
        free(tab[i]);
        i++;
    }

}

void generet_cmd(t_token *token, t_cmd **cmd_)
{
    t_token *tmp;
    t_token *tmp1;
    char **tab;
    int count = 0;
    tmp = token;
    tmp1 = token;
    while (tmp)
    {
        printf("message obo ==  %d\n", (tmp)->type);
        if (tmp->type == WORD)
        {
            count = count_word(&tmp);
            tab = malloc((count + 1) * sizeof(char *));
            tab = generate_tab_cmd(tab, tmp1, count);
            add_node_(cmd_ ,tab,  0);
            tmp1 = tmp;
            // free(tab);
        }
		else  if (tmp != NULL && tmp->type != SPACE_)
        {
            printf("heloo");
            add_node_(cmd_, NULL,tmp->type);
        }
        if (tmp == NULL)
            break;
		tmp = tmp->next;
    }
    print_tab(tab);
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
            // free(cmd_);
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		chech_quoting(line);
		token = gettoken(line);
		printlist(token);
		puts("===========================");
        cmd_ = malloc(sizeof(t_cmd));
        cmd_ = NULL;
		generet_cmd(token, &cmd_);
		printlist_(cmd_);

		// builtins(token);
        freelist_(cmd_);
	    freelist(token);

	}
	clear_history();
}
