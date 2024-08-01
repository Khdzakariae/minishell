/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:25 by zel-khad          #+#    #+#             */
/*   Updated: 2024/08/01 19:08:17 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include <minishell.h>
#include <parssin.h>
#include <fcntl.h>
#include <errno.h>
#include "../lib/libft/libft.h"

extern int g_stat;

typedef struct s_export
{
    char    **env;
    char    **export;
}   t_export;

int	pipex(t_list *list, t_export *env_list);

int input_file(t_list *files);

int output_file(t_list *files);

t_list *merge(t_cmd *parssin, char **env);

int  del(void *content);

void	merge_free(void *contant);

int cmd_quote_handler(char **cmd, char **env);

char *handle_quoting(char *cmd, char **env);

char	*find_str_from_env(char **env, char *str);

char **array_dup(char **str, int add);

int count_array_of_str(char **env);

void	ft_env(char **env, int is_not);

char **array_remove(char **str, int index);

char **array_alloc(char **str);

int	find_index_from_env(char **env, char *str, int type);

int cmd_name_is_valid(char *cmd_name, t_export *env_list);


#endif