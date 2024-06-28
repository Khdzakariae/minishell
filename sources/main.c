/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:33:45 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/14 00:18:18 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *expandEnvironmentVariable(char *input)
{
    char *varValue ;
    varValue = getenv(input);
	return(varValue);
}
int main(void) 
{
	// printf("%s\n",expandEnvironmentVariable("HOME"));
	signels_handler();
	minishell();
    return 0;
}

