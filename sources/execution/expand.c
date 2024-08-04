/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:00:51 by aogbi             #+#    #+#             */
/*   Updated: 2024/08/04 20:33:29 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *split_word_expand(char **env, char *cmd)
{
	int i;
	char *str;
	char *tmp;

	i = 0;
	str = NULL;
	tmp = NULL;
	while(cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
		i++;
	if(cmd[i])
	{
		tmp = ft_strdup(cmd + i);
		cmd[i] = '\0';
		i++;
	}
	str = find_str_from_env(env, cmd);
	if(tmp)
	{
		str = ft_strjoin(str, tmp);
		free(tmp);
	}
	else if (str)
		str = ft_strdup(str);
	if(str && str[1] == '?')
	{
		tmp = ft_strjoin(ft_itoa(g_stat), str + 2);
		free(str);
		str = tmp;
	}
	return(str);
}

char *expand_help(char *cmd, char **env)
{
	int i;
	char *str;
	char *tmp;
	char *tmp1 = NULL;

	i = 0;
	tmp = NULL;
	str = NULL;
	if (!cmd)
		return (NULL);
	while(cmd[i] && (cmd[i] != '$' || !(ft_isalnum(cmd[i + 1]) || cmd[i + 1] == '_')))
		i++;
	if (cmd[i])
	{
		tmp = expand_help(cmd + i + 1, env);
		cmd[i] = '\0';
	}
	tmp1 = split_word_expand(env, cmd);
	str = ft_strjoin(tmp1, tmp);
	if (tmp1)
		free(tmp1);
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

char *quote_expand(char *cmd, int start, int j, char **env)
{
	char *tmp;
	char *tmp1;

	tmp = ft_substr(cmd, start, j - start);
	tmp1 = expand(tmp, env);
	if (tmp1)
	{
		free(tmp);
		tmp = tmp1;
	}
	return(tmp);
}

char *quote_join(char *tmp, char *str)
{
	char *tmp1;

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

char *double_quote(char *str, t_quote *quote, char *cmd, char **env)
{
	char *tmp;

	quote->double_q++;
	if (quote->double_q == 2)
	{
		tmp = quote_expand(cmd, quote->start, quote->index, env);
		str = quote_join(tmp, str);
		quote->double_q = 0;
	}
	quote->start = quote->index + 1;
	return(str);
}

char *single_quote(char *str, t_quote *quote, char *cmd)
{
	char *tmp;
	quote->singl_q++;
	if (quote->singl_q == 2)
	{
		tmp = ft_substr(cmd, quote->start, quote->index - quote->start);
		str = quote_join(tmp, str);
		quote->singl_q = 0;
	}
	quote->start = quote->index + 1;
	return (str);
}

char *whitout_quote(char *str, t_quote *quote, char **env, int *index)
{
	char *tmp;

	if (quote->flag == 0)
	{
		quote->start = quote->index;
		quote->flag = 1;
	}
	if (quote->ogbi->cmd[*index][quote->index + 1] == '\"' || quote->ogbi->cmd[*index][quote->index + 1] == '\'' || !quote->ogbi->cmd[*index][quote->index + 1])
	{
		tmp = quote_expand(quote->ogbi->cmd[*index], quote->start, quote->index + 1, env);
		str = quote_join(tmp, str);
		quote->flag = 0;
		if (!strchr(str, ' '))
			return (str);
		if (quote->ogbi)
		{
			char **split;
			char **tmp1;
			int count;

			split = ft_split(str, ' ');
			free(str);
			count = count_array_of_str(split);
			tmp1 = put_strs_in_array_index(quote->ogbi->cmd, *index, count - 1);
			free(quote->ogbi->cmd);
			quote->ogbi->cmd = tmp1;
			int i = 0;
			while(i < count)
			{
				quote->ogbi->cmd[*index + i] = split[i];
				str = ft_strdup(quote->ogbi->cmd[*index + i]);
				i++;
			}
			*index += i - 1;
			i = 0;
		}
	}
	return (str);
}

char *quote_error(char *str)
{
	write(2, "unexpected while looking for matching `\"'\"\n", 44);
	free(str);
	return (NULL);
}

char *handle_quoting(int *index, char **env, t_ogbi *ogbi)
{
	t_quote quote;
	char *str;

	quote = (t_quote){0, 0, 0, 0, 0, ogbi};
	str = NULL;
	if (!ogbi->cmd[*index])
		return(NULL);
	while(ogbi->cmd[*index][quote.index])
	{
		if (!quote.singl_q && ogbi->cmd[*index][quote.index] == '\"')
			str = double_quote(str, &quote, ogbi->cmd[*index], env);
		else if (!quote.double_q && ogbi->cmd[*index][quote.index] == '\'')
			str = single_quote(str, &quote, ogbi->cmd[*index]);
		else if (!quote.double_q && !quote.singl_q)
			str = whitout_quote(str, &quote, env, index);
		quote.index++;
	}
	if (quote.double_q || quote.singl_q)
		str = quote_error(str);
	return(str);
}

char *whitout_quote_redirections(char *str, t_quote *quote, char **env, char *cmd)
{
	char *tmp;

	if (quote->flag == 0)
	{
		quote->start = quote->index;
		quote->flag = 1;
	}
	if (cmd[quote->index + 1] == '\"' || cmd[quote->index + 1] == '\'' || !cmd[quote->index + 1])
	{
		tmp = quote_expand(cmd, quote->start, quote->index + 1, env);
		str = quote_join(tmp, str);
		quote->flag = 0;
	}
	return (str);
}

char *handle_quoting_redirections(char **env, char *cmd)
{
	t_quote quote;
	char *str;

	quote = (t_quote){0, 0, 0, 0, 0, NULL};
	str = NULL;
	if (!cmd)
		return(NULL);
	while(cmd[quote.index])
	{
		if (!quote.singl_q && cmd[quote.index] == '\"')
			str = double_quote(str, &quote, cmd, env);
		else if (!quote.double_q && cmd[quote.index] == '\'')
			str = single_quote(str, &quote, cmd);
		else if (!quote.double_q && !quote.singl_q)
			str = whitout_quote_redirections(str, &quote, env, cmd);
		quote.index++;
	}
	if (quote.double_q || quote.singl_q)
		str = quote_error(str);
	return(str);
}

int cmd_quote_handler(t_ogbi *ogbi, char **env)
{
	int i = 0;
	char *str;

	if (!ogbi->cmd)
		return (1);
	while(ogbi->cmd[i])
	{
		str = handle_quoting(&i, env, ogbi);
		ogbi->cmd[i] = str;
		if (!str)
			return (1);
		i++;
	}
	return (0);
}