/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:17:12 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/10 19:17:13 by zel-khad         ###   ########.fr       */
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
	else if (symbol == '<')
		parse_redirect_input(token, line, i);
	else if (symbol == '>')
		parse_redirect_output(token, line, i);
	else if (symbol == '|')
		parse_pipe(token, line, i);
}