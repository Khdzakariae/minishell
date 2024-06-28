/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:12:43 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/14 00:20:09 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


char *expandenvironmentvariable(char *input)
{
    char *varValue ;
    varValue = getenv(input);
    if(varValue)
	    return(varValue);
    //else
        //
    return varValue;
}
