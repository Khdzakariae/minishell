/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:24:59 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/10 10:26:49 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_parantheses(char *line)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '(')
			flag++;
		else if (line[i] == ')')
			flag--;
		i++;
		if (flag < 0)
		{
			printf(RED "ERROR PARANTES");
			return (false);
		}
	}
	if (flag != 0)
	{
		printf(RED "ERROR PARANTES");
		return (false);
	}
	return (true);
}

bool	check_double_quotation(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '"')
			count++;
		i++;
	}
	if (count % 2 != 0)
	{
		printf(RED "ERROR DOUBLE_QUOTATION");
		return (false);
	}
	return (true);
}

bool	check_single_quotation(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 != 0)
	{
		printf(RED "ERROR single_QUOTATION");
		return (false);
	}
	return (true);
}

bool	chech_quoting(char *line)
{
	if (check_parantheses(line) == false)
		return (false);
	if (check_double_quotation(line) == false || check_single_quotation(line))
		return (false);
	return (true);
}
