/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:39:07 by zel-khad          #+#    #+#             */
/*   Updated: 2024/07/03 03:29:20 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSSIN_H
# define PARSSIN_H

# include <../lib/libft/libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	int				type;
	char			**value;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_ogbi
{
    char    **cmd;
    t_list  *output_files;
    t_list  *input_files;
}   t_ogbi;

enum				e_types
{
	WORD = 0,
	SORTIE = 1, // >
	ENTREE = 2, // <
	PIPE = 3,   // |
	SPACE_ = 4,
	AMPERSAND = 5,
	APPAND = 6,           // >>
	HEREDOC = 7,          // <<
	SINGLE_QUOTATION = 8, // '
	AND = 9,              // &&
	DOLLAR_SIGN = 10      // $
};

// char **tab;
// ls -la |
// 	-- 1er node --
//  tab[1] = "ls"
//  tab[2] = "-la"

// 	-- 2eme node--
// type = PIPE;
// NULL;

// 	-- 3eme --
// 	if > fille

void				printlist_(t_cmd *head);
int					count_word(t_token **tmp, t_cmd **cmd_);
char				**generate_tab_cmd(char **cmd_, t_token *token, int count);
void				generet_cmd(t_token *token, t_cmd **cmd_);
void				freelist_(t_cmd *head);
void				printlist(t_token *head);
void				add_node_(t_cmd **head, char **tab, int type);
void				signels_handler(void);
t_token				*gettoken(char *line);
void				freelist(t_token *head);
bool				chech_quoting(char *line);
void				add_node(t_token **head, const char *value, int type);
void				parse_symbol(t_token **token, char symbol, char *line,
						int *i);

#endif