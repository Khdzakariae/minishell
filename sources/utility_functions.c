#include <minishell.h>
#include <stdio.h>
char *ft_strcpy(char **dst, const char *src) 
{
    size_t i = 0;

    if (src == NULL) 
        return NULL;

    *dst = malloc(ft_strlen(src) + 1);
    if (*dst == NULL)
        return NULL;
    while (src[i]) 
    {
        (*dst)[i] = src[i];
        i++;
    }
    (*dst)[i] = '\0';

    return *dst;
}

void freeList(t_token *head) 
{
    t_token *current = head;
    t_token *next;

    while (current != NULL) {
        next = current->next;
        free(current->value); 
        free(current);
        current = next;
    }
}


void add_node(t_token **head, const char *value, int type) 
{
    puts("hama==");
    t_token *tmp = malloc(sizeof(t_token));
    if (tmp == NULL) 
    {
        fprintf(stderr, "Memory allocation failed for new node.\n");
        return;
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
        t_token *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = tmp;
    }
}