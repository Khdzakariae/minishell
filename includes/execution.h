/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:25 by zel-khad          #+#    #+#             */
/*   Updated: 2024/08/04 19:36:51 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include <minishell.h>
#include <parssin.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../lib/libft/libft.h"

extern int g_stat;

typedef struct s_export
{
    char    **env;
    char    **export;
}   t_export;

typedef struct s_quote
{
	int index;
	int singl_q;
	int double_q;
	int start;
	int flag;
	t_ogbi *ogbi;
}	t_quote;

int	pipex(t_list *list, t_export *env_list);

int input_file(t_list *files);

int output_file(t_list *files);

t_list *merge(t_cmd *parssin, char **env);

int  del(void *content);

void	merge_free(void *contant);

int cmd_quote_handler(t_ogbi *ogbi, char **env);

// char *handle_quoting(char *cmd, char **env, t_ogbi *ogbi);
char *handle_quoting(int *index, char **env, t_ogbi *ogbi);

char	*find_str_from_env(char **env, char *str);

char **array_dup(char **str, int add);

int count_array_of_str(char **env);

void	ft_env(char **env, int is_not);

char **array_remove(char **str, int index);

char **array_alloc(char **str);

int	find_index_from_env(char **env, char *str, int type);

int cmd_name_is_valid(char *cmd_name, t_export *env_list);

int ft_free_herdoc(t_list *list);

char *expand(char *cmd, char **env);

char **put_strs_in_array_index(char **str, int index, int add);

char *handle_quoting_redirections(char **env, char *cmd);


#endif