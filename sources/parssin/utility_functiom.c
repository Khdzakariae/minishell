/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functiom.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:48:12 by zel-khad          #+#    #+#             */
/*   Updated: 2024/07/24 13:20:59 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void geberete_autput_input(t_token **token,t_cmd **cmd_)
{
    char **tab;
    int type = (*token)->type;
    tab = malloc(2 * sizeof(char *));
    if ((*token))
        (*token) = (*token)->next;
    while ((*token) && ((*token)->type == SPACE_))
        (*token) = (*token)->next;
    tab[0] = ft_strcpy_1(&tab[0], (*token)->value);
    tab[1] = NULL;
    add_node_(cmd_, tab, type);
}

int count_word(t_token **tmp, t_cmd **cmd_)
{
    int count_word = 0;

    while ((*tmp) && ((*tmp)->type == WORD || (*tmp)->type == SPACE_ || (*tmp)->type == ENTREE || (*tmp)->type == SORTIE || (*tmp)->type == APPAND || (*tmp)->type == HEREDOC))
    {
        if ((*tmp)->type == WORD)
        {
            count_word++;
            while ((*tmp)->next != NULL && (*tmp)->next->type != SPACE_)
                *tmp = (*tmp)->next;
        }
        if ((*tmp) && ((*tmp)->type == SORTIE || (*tmp)->type == ENTREE || (*tmp)->type == APPAND || (*tmp)->type == HEREDOC))
            geberete_autput_input(tmp, cmd_);
        *tmp = (*tmp)->next;
    }
    return count_word;
}

char  **generate_tab_cmd(char **cmd_, t_token *token, int count)
{
    int i = 0;
    int flag = 0;
    char *assest;
    
    assest = NULL;
    while (i < count)
    {
        if (token && token->type == WORD)
        {
            while (token && token->type == WORD)
            {
                
                assest = ft_strjoin(assest, token->value);
                token = token->next;
                flag = 1;
            }
            if (flag == 1)
            {
                flag = 0;
                cmd_[i] = ft_strcpy_1(&cmd_[i], assest);
                i++;
                continue;
            }
            i++;
        }
        else if (token && (token->type == SORTIE || token->type == ENTREE || token->type == ENTREE || token->type == APPAND || token->type == HEREDOC))
        {
            if (token && token->type == SPACE_)
                token = token->next;
            token = token->next;
            token = token->next;    
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
        if (tmp && (tmp->type == SORTIE || tmp->type == ENTREE || tmp->type == APPAND || tmp->type == HEREDOC ))
            geberete_autput_input(&tmp ,cmd_);
        else if (tmp->type == WORD)
        {
            count = count_word(&tmp, cmd_);
            tab = malloc((count + 1) * sizeof(char *));
            tab = generate_tab_cmd(tab, tmp1, count);
            add_node_(cmd_ ,tab,  0);
            tmp1 = tmp;
            continue;
        }
		else  if (tmp != NULL && tmp->type != SPACE_)
            add_node_(cmd_, NULL,tmp->type);
        if (tmp == NULL)
            break;
		tmp = tmp->next;
    }
}