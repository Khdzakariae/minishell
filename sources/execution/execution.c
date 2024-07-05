/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:00:19 by zel-khad          #+#    #+#             */
/*   Updated: 2024/07/05 12:21:08 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int isCommandInPath(const char *command) 
{
    int i = 0;
    char *path;
	char **token;
	char *fullPath;
	
	path = getenv("PATH");
    if (path == NULL) 
	{
        printf("Le chemin d'accès n'est pas défini.\n");
        return -1;
    }

    token = ft_split(path, ':');
    if (token == NULL) 
	{
        printf("Erreur lors du fractionnement du chemin d'accès.\n");
        return -1;
    }
    if (access(command, F_OK | X_OK) == 0) 
	{
        printf("La commande '%s' est dans le PATH: %s\n", command, token[i]);
        return 1;
    }
    while (token[i] != NULL) 
	{
        fullPath = ft_strjoin(ft_strjoin(token[i], "/"), command);
        if (fullPath == NULL) 
		{
            printf("Erreur lors de l'allocation mémoire.\n");
            return -1;
        }
        if (access(fullPath, X_OK) == 0) 
		{
            printf("La commande '%s' est dans le PATH: %s\n", command, token[i]);
            free(fullPath);
            return 1;
        }
        free(fullPath);
        i++;
    }
    printf("La commande '%s' n'est pas dans le PATH.\n", command);
    return 0;
}