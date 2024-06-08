#include <minishell.h>

char *ft_strcpy(char *src, char *dst)
{
    if (src == NULL || dst == NULL) 
	{
        return NULL;
    }

    size_t i = 0;

    while (src[i]) 
	{
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}

 void freeList(t_token* head) 
 {
    t_token* current = head;
    t_token* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
	free(current);
}

void	add_node(t_token **head, char *symbol)
{
	t_token	*tmp;
	t_token	*temp1;

	tmp = malloc(sizeof(t_token));
	ft_strcpy(symbol, symbol);
	symbol = symbol;
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