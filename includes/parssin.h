/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:39:07 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/10 19:16:25 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSSIN_H
# define PARSSIN_H

# include <../lib/libft/libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <stdio.h> 
#include <signal.h> 

# define COLOR_BOLD "\e[1m"
# define KNRM "\x1B[0m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
# define RESET "\x1B[0m"

typedef struct s_tree
{
	int				data;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;
enum				types
{
	WORD = 1,
	LEFT_PARENTHESES = 2,
	RIGHT_PARENTHESES = 3,
	BACKSLASH = 4,
	DOUBLE_QUOTATION = 5,
	SINGLE_QUOTATION = 6,
	DOLLAR_SIGN = 7,
	AND = 8,
	AMPERSAND = 9,
	SORTIE = 10,
	ENTREE = 11,
	LEFT_GUILLEMET = 13,
	RIGHT_GUILLEMET = 14,
	OR = 15,
	PIPE = 16
};

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}					t_token;

void signels_handler();
t_token	            *gettoken(char *line);
void				freelist(t_token *head);
bool				chech_quoting(char *line);
void				add_node(t_token **head, const char *value, int type);
void	parse_symbol(t_token **token, char symbol, char *line, int *i);

#endif