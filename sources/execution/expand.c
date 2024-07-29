/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:00:51 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/29 12:32:31 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


char *expand_help(char *cmd, char **env)
{
	int i;
	char *str = NULL;
	char *tmp;

	i = 0;
	tmp = NULL;
	if (!cmd)
		return (NULL);
	while(cmd[i] && cmd[i] != '$')
		i++;
	if (cmd[i])
	{
		tmp = expand_help(cmd + i + 1, env);
		cmd[i] = '\0';
	}
	str = ft_strjoin(find_str_from_env(env, cmd), tmp);
	return(str);
}

char *expand(char *cmd, char **env)
{
	int i;
	char *str;
	char *tmp;

	i = 0;
	str = NULL;
	while(cmd[i] && cmd[i] != '$')
		i++;
	if(cmd[i])
	{
		str = expand_help(cmd + i, env);
		cmd[i] = '\0';
	}
	tmp = ft_strjoin(cmd, str);
	if (str)
		free(str);
	str = tmp;
	return(str);
}

char *quote_join(char *cmd, char *str, int start, int j)
{
	char *tmp;
	char *tmp1;

	tmp = ft_substr(cmd, start, j - start);
	if (str != NULL)
	{
		tmp1 = ft_strjoin(str, tmp);
		free(str);
		free(tmp);
		str = tmp1;
	}
	else
		str = tmp;
	return(str);
}


char *handle_quoting(char *cmd, char **env)
{
	int i;
	int singl_q = 0;
	int double_q = 0;
	int start = 0;
	int flag = 0;
	char *tmp;
	char *str;

	i = 0;
	str = NULL;
	while(cmd[i])
	{
		if (!singl_q && cmd[i] == '\"')
		{	
			double_q++;
			if (double_q == 2)
			{
				str = quote_join(cmd, str, start, i);
				tmp = expand(str, env);
				if (tmp)
				{
					free(str);
					str = tmp;
				}
				double_q = 0;
			}
			start = i + 1;
		}
		else if (!double_q && cmd[i] == '\'')
		{
			singl_q++; 
			if (singl_q == 2)
			{
				str = quote_join(cmd, str, start, i);
				singl_q = 0;
			}
			start = i + 1;
		}
		else if (!double_q && !singl_q)
		{
			if (flag == 0)
			{
				start = i;
				flag = 1;
			}
			if (cmd[i + 1] == '\"' || cmd[i + 1] == '\'' || !cmd[i + 1])
			{
				str = quote_join(cmd, str, start, i + 1);
				tmp = expand(str, env);
				if (tmp)
				{
					free(str);
					str = tmp;
				}
				flag = 0;
			}
		}
		i++;
	}
	return(str);
}

void cmd_quote_handler(char **cmd, char **env)
{
	int i = 0;
	char *str;
	
	if (!cmd)
		return ;
	while(cmd[i])
	{
		str = handle_quoting(cmd[i], env);
		if (!str)
			i--;
		else
		{
			free(cmd[i]);
			cmd[i] = str;
		}
		i++;
	}
}