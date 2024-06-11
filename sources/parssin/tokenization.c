/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:25:15 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/11 10:39:45 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token *generet_cmd(t_token *token)
{
	t_token *tmp = token;
	
	tmp->type = CMD;
	while (tmp->next)
	{
		if (tmp->type != 1 && tmp->type != 0 )
			tmp->next->type = CMD;
		tmp = tmp->next;
	}
	tmp = token;
	return (token);
}

int	extract_word(t_token **token, char *line, int i)
{
	int		start;
	char	*whitespace;
	char	*symbols;

	start = i;
	whitespace = " \t\r\n\v";
	symbols = " <|>&()'\"";
	while (line[i] && !ft_strchr(whitespace, line[i]) && !ft_strchr(symbols,
			line[i]))
		i++;
	add_node(token, ft_substr(line, start, (size_t)(i - start)), WORD);
	while (line[i] && ft_strchr(whitespace, line[i]))
		i++;
	return (i);
}

void lexer_collect_string(t_token **token, char *line, int *i)
{
	int start;
	char *tmp;
	start = *i;
	
	while (line[*i] != '"')
		(*i)++;
	if (line[*i] == '"')
	{
		tmp = ft_substr(line, start, (size_t)(i - start));
		add_node(token, tmp, WORD);
		*i = *i + ft_strlen(tmp);
	}
	else
		printf("ERROR");
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
	symbols = " <|>&()'";
	while (line[i] && ft_strchr(whitespace, line[i]))
		i++;
	while (line[i])
	{
		if (line[i] == '"')
			lexer_collect_string(&token, line, &i);
		else if  (!ft_strchr(symbols, line[i]) && !ft_strchr(whitespace, line[i]))
			i = extract_word(&token, line, i) - 1;
		else
			parse_symbol(&token, line[i], line, &i);
		i++;
	}
	token = generet_cmd(token);
	return (token);
}
