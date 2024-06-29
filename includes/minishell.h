/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <aogbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:39:00 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/28 22:26:33 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <parssin.h>
# include <execution.h>
# include "../lib/libft/libft.h"

char	*ft_strcpy_1(char **dst, const char *src);

int	ft_strcmp(char *s1, char *s2);
void builtins(t_token *token);
void	minishell(void);

#endif