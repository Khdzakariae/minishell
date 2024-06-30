/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functiom.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:48:12 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/30 15:49:23 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int count_word(t_token **tmp)
{
    int count_word = 0;
    while ((*tmp) && ((*tmp)->type == WORD || (*tmp)->type == SPACE_))
    {
        if ((*tmp)->type == WORD)
            count_word++;
        if ((*tmp)->next && ((*tmp)->next->type != WORD && (*tmp)->next->type != SPACE_))
            break;
        *tmp = (*tmp)->next;
    }
    return count_word;
}

char  **generate_tab_cmd(char **cmd_, t_token *token, int count)
{
    int i = 0;
    while (i < count)
    {

        if (token->type == WORD)
        {
            cmd_[i] = ft_strcpy(&cmd_[i], token->value);
            i++;
        }
        token = token->next;
    }
    cmd_[i] = NULL;
    return(cmd_);
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
        if (tmp->type == WORD)
        {
            count = count_word(&tmp);
            tab = malloc((count + 1) * sizeof(char *));
            tab = generate_tab_cmd(tab, tmp1, count);
            add_node_(cmd_ ,tab,  0);
            tmp1 = tmp;
        }
		else  if (tmp != NULL && tmp->type != SPACE_)
            add_node_(cmd_, NULL,tmp->type);
        if (tmp == NULL)
            break;
		tmp = tmp->next;
    }
}