/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:53:37 by aogbi             #+#    #+#             */
/*   Updated: 2024/06/28 21:48:19 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../../includes/execution.h"

char **make_array(char *str)
{
	return(ft_split(str, ' '));
}
char	*find_path_from_env(char **env)
{
	int i = 0;

    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
            return (env[i] + 5);
        i++;
    }
    return (NULL);
}

int	pipex(t_list *list, int size, char **env)
{
	char **path;
	int i = 0;

	path = ft_split(find_path_from_env(env), ':');
	while(size--)
	{
		
	}
}
int main(int argc, char *argv[], char *env[])
{
	t_list    *list;
	int i = 1;

	list = NULL;
	if (argc < 3)
		return 0;
	while(argc - i - 2)
	{
		ft_lstadd_front(&list, ft_lstnew((void *)((char **)make_array(argv[i]))));
		i++;
	}
    pipex(list, argc - 1, env);
    return 0;
}
