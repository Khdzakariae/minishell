/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:48:56 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/03 08:15:25 by aogbi            ###   ########.fr       */
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
t_ogbi	*init_ogbi(char **command, t_list *input_files, t_list *output_files)
{
	t_ogbi	*ogbi;

	ogbi = malloc(sizeof(t_ogbi));
	ogbi->cmd = command;
	ogbi->input_files = input_files;
	ogbi->output_files = output_files;
	return (ogbi);
}

void del_lst(void *contant)
{
	t_list *list;
	t_list *tmp;

	list = (t_list *)contant;
	while (list)
	{
		tmp = list;
        list = tmp->next;
		free(tmp);
	}
}

void	merge_free(void *contant)
{
	t_ogbi	*ogbi;

	ogbi = (t_ogbi *)contant;
	// del((char **)ogbi->cmd);
	del_lst(ogbi->input_files);
	del_lst(ogbi->output_files);
	free(ogbi);
}

t_list *merge(t_cmd *parssin)
{
	t_list	*node;
	t_ogbi	*ogbi;
	char    **command;
    t_list	*input_files;
	t_list	*output_files;

	node = NULL;
	set_to_null(&input_files, &output_files);
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
			ogbi = init_ogbi(command, input_files, output_files);
			ft_lstadd_back(&node, ft_lstnew(ogbi));
			set_to_null(&input_files, &output_files);
        }
        parssin = parssin->next;
    }
	ogbi = init_ogbi(command, input_files, output_files);
	ft_lstadd_back(&node, ft_lstnew(ogbi));
    return (node);
}
