/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:48:56 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/03 00:39:08 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef struct s_ogbi
{
    char    **cmd;
    t_list  *output_files;
    t_list  *input_files;
}   t_ogbi;

void add_to_list(char **list, t_list **add)
{
	t_list *node;
}

t_ogbi merge(t_cmd *parssin)
{
	char	**cmd;
    t_list	*input_files;
	t_list	*output_files;

    while(parssin)
    {
        if (parssin->type == SORTIE)
        {}
		else if (parssin->type == ENTREE)
		{}
		else if (parssin->type == WORD)
		{}
		else if (parssin->type == PIPE)
		{}
        parssin = parssin->next;
    }
    return ();
}
