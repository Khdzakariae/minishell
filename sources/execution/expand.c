/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:00:51 by aogbi             #+#    #+#             */
/*   Updated: 2024/07/28 14:48:17 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void handle_quoting(char **cmd)
// {
// 	int i = 0;
// 	int j;
	

// 	while (cmd[i])
// 	{
// 		if (cmd[i][j] == '\"')
// 		{
// 			j++;
			
// 		}
// 		else if (cmd[i][j] == '\'')
// 		{
			
// 		}
// 		else
		
// 	}
	
// }

char *quote_join(char *cmd, char *str, int start, int j)
{
	char *tmp = NULL;
	char *tmp1 = NULL;

	start++;
	tmp = ft_substr(cmd, start, j - start);
	printf("cmd : %s, start : %d, j : %d\n", cmd, start, j);
	if (str)
	{
		tmp1 = ft_strjoin(str, tmp);
		free(str);
		free(tmp);
		str = tmp1;
	}
	else
		str = tmp;
	return (str);
}

void handle_quoting(char **cmd)
{
	int i = 0, j;
	int singl_q = 0;
	int double_q = 0;
	int start = 0;
	char *str = NULL;
	
	while(cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if (!singl_q && cmd[i][j] == '\"')
			{
				double_q++;
				if (double_q == 2)
				{
					puts("---------------------");
					str = quote_join(cmd[i], str, start, j);
					double_q = 0;
					printf("double : %s\n", str);
				}
				start = j;
			}
			else if (!double_q && cmd[i][j])
			{
				singl_q++;
				if (singl_q == 2)
				{
					puts("+++++++++++++++++++++++");
					str = quote_join(cmd[i], str, start, j);
					singl_q = 0;
					printf("singl : %s\n", str);
				}
				start = j;
			}
			printf("j : %d\n", j);
			j++;
		}
		free(cmd[i]);
		cmd[i] = str;
		i++;	
	}
}





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

void convert_variable(char **cmd)
{

	handle_quoting(cmd);

	
	// int i;
	// int j;
	
	// i = 0;
	// if (!cmd)
	// 	return;
	// while(cmd[i])
	// {
	// 	j = 0;
	// 	while(cmd[i][j] != '$' && cmd[i][j])
	// 	{
	// 		if (cmd[i][j] == '\'')
	// 			return ;
	// 		j++;
	// 	}
	// 	if (cmd[i][j])
	// 		convert_variable_helper(cmd, i, j);
    //     i++;
	// }
}