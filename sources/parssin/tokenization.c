/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:25:15 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/13 22:23:59 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// t_token *generet_cmd(t_token *token)
// {
// 	t_token *tmp = token;
	
// 	if (tmp == NULL)
// 		return NULL;
// 	tmp->type = CMD;
// 	while (tmp->next)
// 	{
// 		if (tmp->type != 1 && tmp->type != 0 )
// 			tmp->next->type = CMD;
// 		tmp = tmp->next;
// 	}
// 	tmp = token;
// 	return (token);
// }

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
	// while (line[i] && ft_strchr(whitespace, line[i]))
	// 	i++;
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


int count_word(t_token **tmp)
{
    
    int count_word = 0;
    while ((*tmp))
    {
        if ((*tmp)->type == WORD)
            count_word++;
        else if ((*tmp)->type != SPACE_)
            break;
        *tmp = (*tmp)->next;
    }
    return count_word;
}



t_cmd *generet_cmd(t_token *token, t_cmd *cmd_)
{
	t_token *tmp ;
	t_token	*tmp1;
	int count = 0;
	tmp = token;
	tmp1 = token;
	while(tmp)
	{
		if (tmp1->type == WORD)
			count = count_word(&tmp);
		printf("la valeur de word is |%d|\n", count);
		if (tmp == NULL)
			break;
		tmp = tmp->next;
	}
	
	return(cmd_);
}

t_token	*gettoken(char *line)
{
	t_token	*token;
	t_cmd	*cmd_;
	char	*whitespace;
	char	*symbols;
	int		i;

	cmd_ = NULL;
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
	// token = 
	cmd_ = generet_cmd(token, cmd_);
	return (token);
}
