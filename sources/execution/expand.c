/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:00:51 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/28 17:46:10 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void convert_variable_helper(char **cmd, int i, int j)
// {
// 	char *value;
// 	char *tmp;

// 	if (!ft_strcmp(cmd[i] + j, "$?"))
// 	{
// 		cmd[i][j] = '\0';
// 		tmp = ft_strjoin(cmd[i], ft_itoa(g_stat));
// 		free(cmd[i]);
// 		cmd[i] = tmp;
// 	}
// 	else if(!cmd[i][1])
// 		return ;
// 	else
// 	{
// 		value = getenv(cmd[i] + j + 1);
// 		if (value)
// 		{
// 			cmd[i][j] = '\0';
// 			tmp = ft_strjoin(cmd[i], ft_strdup(value));
// 			free(cmd[i]);
// 			cmd[i] = tmp;
// 		}
// 		else
// 		{
// 			if (j != 0)
// 				cmd[i][j] = '\0';
// 			else
// 			{
// 				j = i;
// 				while(cmd[j])
// 				{
// 					free(cmd[j]);
// 					cmd[j] = NULL;
// 					if (cmd[j + 1])
//             	    	cmd[j] = ft_strdup(cmd[j + 1]);
//             	    j++;
// 				}
// 				i--;
// 			}
// 		}
// 	}
// 	return ;
// }

// char *expand(char *cmd)
// {
// 	int i;
// 	int j;
	
// 	i = 0;
// 	if (!cmd)
// 		return;
// 	while(cmd[i])
// 	{
// 		j = 0;
// 		while(cmd[i][j] != '$' && cmd[i][j])
// 		{
// 			if (cmd[i][j] == '\'')
// 				return ;
// 			j++;
// 		}
// 		if (cmd[i][j])
// 			convert_variable_helper(cmd, i, j);
//         i++;
// 	}
// }

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


char *handle_quoting(char *cmd)
{
	int i;
	int singl_q = 0;
	int double_q = 0;
	int start = 0;
	int flag = 0;
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
				// str = expand(str);
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
				flag = 0;
			}
		}
		i++;
	}
	return(str);
}

int is_quote(char *cmd)
{
	int i;
	
	i = 0;
	while(cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void cmd_quote_handler(char **cmd)
{
	int i = 0;
	char *str;
	
	while(cmd[i])
	{
		if (is_quote(cmd[i]))
		{
			str = handle_quoting(cmd[i]);
			free(cmd[i]);
			cmd[i] = str;
		}
		i++;
	}
}

void convert_variable(char **cmd)
{

	cmd_quote_handler(cmd);

}