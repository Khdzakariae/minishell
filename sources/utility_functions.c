#include <minishell.h>


void	add_node(t_token **head, t_type type)
{
	t_token	*tmp;
	t_token	*temp1;

	tmp = malloc(sizeof(t_token));
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