/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:20:07 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/31 16:09:34 by aogbi            ###   ########.fr       */
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
        i++;
    }
    array[j] = NULL;
    return(array);
}
