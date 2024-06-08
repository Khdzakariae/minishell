# ifndef MINISHELL_H
# define MINISHELL_H

#include <../lib/libft/libft.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>


#define LEFT_PARENTHESES '('
#define RIGHT_PARENTHESES ')'
#define BACKSLASH '\\'
#define DOUBLE_QUOTATION '\"'
#define SINGLE_QUOTATION '\''
#define DOLLAR_SIGN '$'
#define AMPERSAND '&'
#define SORTIE '>'
#define ENTREE '<'
#define PIPE '|'

typedef struct s_tree
{
    int data;
    struct s_tree *left;
    struct s_tree *right;
}              t_tree;

// typedef struct s_type
// {
//     # define LEFT_PARENTHESES // (
//     # define RIGHT_PARENTHESES  // )
//     # define BACKSLASH //
//     # define DOUBLE_QUOTATION
//     # define SINGLE_QUOTATION //
//     # define DOLLAR_SIGN // $
//     # define AMPERSAND // &
//     # define SORTIE // >
//     # define ENTREE // <
//     # define PIPE // |
// }               t_type;


typedef struct s_token
{
    char type;
    int     id;
    int start;
    int end;
    struct s_token *next;
    
}               t_token;

#define COLOR_BOLD  "\e[1m"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void	add_node(t_token **head, char symbol);


# endif