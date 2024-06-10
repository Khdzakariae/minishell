/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:17:02 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/10 19:17:04 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void handle_sigint()
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

void signels_handler()
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}