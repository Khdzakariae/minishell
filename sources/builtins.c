/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:30:33 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/11 22:16:23 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void builtins(t_token *token)
{
    if (ft_strcmp(token->value, "cd") == 0)
    {
     if(chdir(token->next->value) == 0) {
        printf("Directory changed successfully to %s\n", token->value);
    } else {
        perror("chdir() error");
    }
    }
    else
        puts("zeeb");
}


