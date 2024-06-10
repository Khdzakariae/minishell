#include <minishell.h>

bool	check_PARENTHESES(char *line)
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

bool	check_DOUBLE_QUOTATION(char *line)
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

bool	check_SINGLE_QUOTATION(char *line)
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
bool	chech_Quoting(char *line)
{
	if (check_PARENTHESES(line) == false)
		return (false);
	if (check_DOUBLE_QUOTATION(line) == false || check_SINGLE_QUOTATION(line))
		return (false);
	return (true);
}
