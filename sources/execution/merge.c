/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:48:56 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/03 04:36:08 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

void add_to_list(void *contant, t_list **add)
{
	t_list *node;

	node = ft_lstnew(contant);
	ft_lstadd_back(add, node);
}

void set_to_null(t_list **input_files, t_list **output_files)
{
   	*input_files = NULL;
    *output_files = NULL;
}

t_list *merge(t_cmd *parssin)
{
	t_list	*node;
	t_ogbi	*ogbi;
	char    **command;
    t_list	*input_files;
	t_list	*output_files;

	set_to_null(&input_files, &output_files);
	node = NULL;
    while(parssin)
    {
        if (parssin->type == SORTIE)
			add_to_list(*(parssin->value), &output_files);
		else if (parssin->type == ENTREE)
			add_to_list(*(parssin->value), &input_files);
		else if (parssin->type == WORD)
			command = parssin->value;
		else if (parssin->type == PIPE)
		{
			ogbi = malloc(sizeof(t_ogbi));
			ogbi->cmd = command;
			ogbi->input_files = input_files;
			ogbi->output_files = output_files;
			ft_lstadd_back(&node, ft_lstnew(ogbi));
			set_to_null(&input_files, &output_files);
        }
        parssin = parssin->next;
    }
	ogbi = malloc(sizeof(t_ogbi));
	ogbi->cmd = command;
	ogbi->input_files = input_files;
	ogbi->output_files = output_files;
	ft_lstadd_back(&node, ft_lstnew(ogbi));
    return (node);
}
