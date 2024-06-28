/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:17:12 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/28 22:15:14 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_redirect_input(t_token **token, char *line, int *i)
{
	if (line[*i + 1] == '<')
	{
		add_node(token, NULL, LEFT_GUILLEMET);
		(*i)++;
	}
	else
		add_node(token, NULL, ENTREE);
}

void	parse_redirect_output(t_token **token, char *line, int *i)
{
	if (line[*i + 1] == '>')
	{
		add_node(token, NULL, RIGHT_GUILLEMET);
		(*i)++;
	}
	else
		add_node(token, NULL, SORTIE);
}

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

void parse_space(t_token **token, char *line, int *i)
{
		char *whitespace = " \t\r\n\v";
		if (ft_strchr(whitespace, line[*i]))
		{
			while(line[*i] && !ft_strchr(whitespace, line[*i]))
				(*i)++;
			if (!ft_strchr(whitespace, line[*i + 1]))
				add_node(token, NULL, SPACE);
		}
}

void	parse_symbol(t_token **token, char symbol, char *line, int *i)
{
	if (symbol == '(')
		add_node(token, NULL, LEFT_PARENTHESES);
	else if (symbol == ')')
		add_node(token, NULL, RIGHT_PARENTHESES);
	else if (symbol == '\\')
		add_node(token, NULL, BACKSLASH);
	else if(symbol == ' ')
		parse_space(token, line, i);
	else if (symbol == '\'')
		add_node(token, NULL, SINGLE_QUOTATION);
	else if (symbol == '$')
		add_node(token, NULL, DOLLAR_SIGN);
	else if (symbol == '&')
		parse_ampersand(token, line, i);
	else if (symbol == '<')
		parse_redirect_input(token, line, i);
	else if (symbol == '>')
		parse_redirect_output(token, line, i);
	else if (symbol == '|')
		parse_pipe(token, line, i);
}
