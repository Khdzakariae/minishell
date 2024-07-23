/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:25:15 by zel-khad          #+#    #+#             */
/*   Updated: 2024/07/23 17:50:04 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	extract_word(t_token **token, char *line, int i)
{
	int		start;
	char	*whitespace;
	char	*symbols;

	start = i;
	whitespace = " \t\r\n\v";
	symbols = " <|>&()'\"";
	while (line[i] && !ft_strchr(whitespace, line[i]) && !ft_strchr(symbols,line[i]))
		i++;
	add_node(token, ft_substr(line, start, (size_t)(i - start)), WORD);
	return (i);
}


void lexer_collect_string(t_token **token, char *line, int *i)
{
	int start;
	char *tmp;
	start = *i;
	int j = *i;
	

	if (line[j] == '\'')
	{
		while ((line[*i] != '\0') && (line[(*i) + 1] != '\''))
		{
        	(*i)++;
		}
		(*i)++;
		int length = *i - start;
		tmp = ft_substr(line, (start), length + 1);
		// printf("the tmp is ---- ++ ------> %s\n", tmp);
		if (tmp == NULL)
			free(tmp);
		else
			add_node(token, tmp, WORD);
	}
	if (line[j] == '"')
	{
		while ((line[*i] != '\0') && (line[(*i) + 1] != '"'))
		{
        	(*i)++;
		}
		(*i)++;
		int length = *i - start;
		tmp = ft_substr(line, (start + 1), length - 1);
		// printf("the tmp is ----------> %s\n", tmp);
		if (tmp == NULL)
			free(tmp);
		else
			add_node(token, tmp, WORD);
		(*i)++;
	}
}



t_token	*gettoken(char *line)
{
	t_token	*token;

	char	*whitespace;
	char	*symbols;
	int		i;

	token = NULL;
	i = 0;
	whitespace = " \t\r\n\v";
	symbols = " <|>&()";
	while (line[i] && ft_strchr(whitespace, line[i]))
		i++;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			lexer_collect_string(&token, line, &i);
		else if  (!ft_strchr(symbols, line[i]) && !ft_strchr(whitespace, line[i]))
			i = extract_word(&token, line, i) - 1;
		else
			parse_symbol(&token, line[i], line, &i);
		i++;
	}
	return (token);
}
