/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:25 by zel-khad          #+#    #+#             */
/*   Updated: 2024/07/02 23:35:41 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include <fcntl.h>
#include <errno.h>
#include "../lib/libft/libft.h"

void	pipex(t_list *list, char **env, t_list *in_list, t_list *out_list);

int input_file(t_list *files);

int output_file(t_list *files);

#endif