/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:32:04 by zel-khad          #+#    #+#             */
/*   Updated: 2024/06/11 22:10:19 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcpy(char **dst, const char *src)
{
	size_t	i;

	i = 0;
	if (src == NULL)
		return (NULL);
	*dst = malloc(ft_strlen(src) + 1);
	if (*dst == NULL)
		return (NULL);
	while (src[i])
	{
		(*dst)[i] = src[i];
		i++;
	}
	(*dst)[i] = '\0';
	return (*dst);
}

void	freelist(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
void freelist_(t_cmd *head)
{
    t_cmd *current;
    t_cmd *next;

	current = head;
	// while (current != NULL)
	// {
	// 	next = current->next;
	// 	free(current->value);
	// 	free(current);
	// 	current = next;
	// }    
    while (current != NULL)
    {
        next = current->next;
        if (current->value != NULL)
        {
            int i = 0;
            while (current->value[i] != NULL)
            {
                free(current->value[i]);
                i++;
            }
            free(current->value);
        }

        free(current);
        current = next;
    }
}


void	add_node_(t_cmd **head, int type)
{
	t_cmd	*tmp;
	t_cmd	*temp1;

	tmp = malloc(sizeof(t_cmd));
	tmp->value = NULL;
	tmp->type = type;
	tmp->next = NULL;
	if (*head == NULL)
		*head = tmp;
	else
	{
		temp1 = *head;
		while (temp1->next != NULL)
			temp1 = temp1->next;
		temp1->next = tmp;
	}
}

void	add_node(t_token **head, const char *value, int type)
{
	t_token	*tmp;
	t_token	*current;

	tmp = malloc(sizeof(t_token));
	if (tmp == NULL)
	{
		fprintf(stderr, "Memory allocation failed for new node.\n");
		return ;
	}
	if (value == NULL)
		tmp->value = NULL;
	else
		ft_strcpy(&tmp->value, value);
	tmp->type = type;
	tmp->next = NULL;
	if (*head == NULL)
		*head = tmp;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = tmp;
	}
}
