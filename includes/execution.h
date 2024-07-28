/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:25 by zel-khad          #+#    #+#             */
/*   Updated: 2024/07/22 03:56:27 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include <minishell.h>
#include <parssin.h>
#include <fcntl.h>
#include <errno.h>
#include "../lib/libft/libft.h"

int	pipex(t_list *list, char **env);

int input_file(t_list *files);

int output_file(t_list *files);

t_list *merge(t_cmd *parssin);

int  del(void *content);

void	merge_free(void *contant);

#endif