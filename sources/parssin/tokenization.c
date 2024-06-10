/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:25:15 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/10 10:31:10 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_ampersand(t_token **token, char *line, int *i)
{
	if (line[*i + 1] == '&')
	{
		add_node(token, NULL, AND);
		(*i)++;
	}
	else
		add_node(token, NULL, AMPERSAND);
}

void	parse_pipe(t_token **token, char *line, int *i)
{
	if (line[*i + 1] == '|')
	{
		add_node(token, NULL, OR);
		(*i)++;
	}
	else
		add_node(token, NULL, PIPE);
}

void	parse_symbol(t_token **token, char symbol, char *line, int *i)
{
	if (symbol == '(')
		add_node(token, NULL, LEFT_PARENTHESES);
	else if (symbol == ')')
		add_node(token, NULL, RIGHT_PARENTHESES);
	else if (symbol == '\\')
		add_node(token, NULL, BACKSLASH);
	else if (symbol == '"')
		add_node(token, NULL, DOUBLE_QUOTATION);
	else if (symbol == '\'')
		add_node(token, NULL, SINGLE_QUOTATION);
	else if (symbol == '$')
		add_node(token, NULL, DOLLAR_SIGN);
	else if (symbol == '&')
		parse_ampersand(token, line, i);
	else if (symbol == '>')
		add_node(token, NULL, SORTIE);
	else if (symbol == '<')
		add_node(token, NULL, ENTREE);
	else if (symbol == '|')
		parse_pipe(token, line, i);
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

t_token	*gettoken(char *line)
{
	t_token	*token;
	char	*whitespace;
	char	*symbols;
	int		i;

	token = NULL;
	i = 0;
	whitespace = " \t\r\n\v";
	symbols = " <|>&()'\"";
	while (line[i] && ft_strchr(whitespace, line[i]))
		i++;
	while (line[i])
	{
		if (!ft_strchr(symbols, line[i]) && !ft_strchr(whitespace, line[i]))
			i = extract_word(&token, line, i) - 1;
		else
			parse_symbol(&token, line[i], line, &i);
		i++;
	}
	return (token);
}
