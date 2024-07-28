/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:00:51 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/28 10:02:40 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void convert_variable_helper(char **cmd, int i, int j)
{
	char *value;
	char *tmp;

	if (!ft_strcmp(cmd[i] + j, "$?"))
	{
		cmd[i][j] = '\0';
		tmp = ft_strjoin(cmd[i], ft_itoa(g_stat));
		free(cmd[i]);
		cmd[i] = tmp;
	}
	else if(!cmd[i][1])
		return ;
	else
	{
		value = getenv(cmd[i] + j + 1);
		if (value)
		{
			cmd[i][j] = '\0';
			tmp = ft_strjoin(cmd[i], ft_strdup(value));
			free(cmd[i]);
			cmd[i] = tmp;
		}
		else
		{
			if (j != 0)
				cmd[i][j] = '\0';
			else
			{
				j = i;
				while(cmd[j])
				{
					free(cmd[j]);
					cmd[j] = NULL;
					if (cmd[j + 1])
            	    	cmd[j] = ft_strdup(cmd[j + 1]);
            	    j++;
				}
				i--;
			}
		}
	}
	return ;
}

void convert_variable(char **cmd)
{
	int i;
	int j;
	
	i = 0;
	if (!cmd)
		return;
	while(cmd[i])
	{
		j = 0;
		while(cmd[i][j] != '$' && cmd[i][j])
		{
			if (cmd[i][j] == '\'')
				return ;
			j++;
		}
		if (cmd[i][j])
			convert_variable_helper(cmd, i, j);
        i++;
	}
}