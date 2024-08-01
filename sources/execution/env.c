/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:20:07 by aogbi             #+#    #+#             */
/*   Updated: 2024/08/01 23:55:52 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char **array_dup(char **str, int add)
{
    char **array;
    int     i;

    i = count_array_of_str(str);
    array = malloc(sizeof(char *) * (i + add + 1));
    if (!array)
        return (NULL);
    i = 0;
    while(str && str[i])
    {
        array[i] = str[i];
        i++;
    }
    add += i;
    while(i <= add)
    {
        array[i] = NULL;
        i++;
    }
    return(array);
}

char **array_remove(char **str, int index)
{
    char **array;
    int     i;
    int     j;

    i = -1;
    i = count_array_of_str(str);
    if (!i)
        return (NULL);
    else
    {
        array = malloc(sizeof(char *) * (i));
        if (!array)
            return (NULL);
    }
    i = 0;
    j = 0;
    while(str[i])
    {
		if (index != i)
        	array[j++] = str[i];
        else
			free(str[i]);
        i++;
    }
    array[j] = NULL;
    return(array);
}

char **array_alloc(char **str)
{
    char **array;
    int     i;

    i = count_array_of_str(str);
    if (!str)
        return(NULL);
    array = malloc(sizeof(char *) * (i + 1));
    if (!array)
        return (NULL);
    i = 0;
    while(str && str[i])
    {
        array[i] = ft_strdup(str[i]);
        i++;
    }
    array[i] = NULL;
    return(array);
}

int ft_free_herdoc(t_list *list)
{
	t_list *tmp;
	int index;

	index = 0;
	while(list)
	{
		tmp = ((t_ogbi *)(list->content))->input_files;
		while(tmp)
		{
			if (((t_red *)tmp->content)->type == HEREDOC)
				free(((t_red *)tmp->content)->value);
			tmp = tmp->next;
		}
		list = list->next;
	}
	return (0);
}
