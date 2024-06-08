#include <minishell.h>


void	add_node(t_token **head, char symbol)
{
	t_token	*tmp;
	t_token	*temp1;

	tmp = malloc(sizeof(t_token));
	tmp->type = symbol;
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