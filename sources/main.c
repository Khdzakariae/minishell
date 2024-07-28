/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:33:45 by zel-khad          #+#    #+#             */
/*   Updated: 2024/07/28 13:26:31 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int main(void) 
{

	char *str = "word";
	char *tmp1 = NULL;
	char *tmp = ft_strdup("hello");
	str = ft_strjoin(str, tmp);
	free(tmp);
	tmp1 = ft_strjoin(str, "zabi");
	free(str);
	str = tmp1;
	printf("the str is |%s|\n", str);
	free(str);
	// signels_handler();
	// minishell();
    return 0;
}

