#include <minishell.h>

char *ft_strcpy(char **dst, const char *src) {
    if (src == NULL) {
        return NULL;
    }

    *dst = malloc(ft_strlen(src) + 1);
    if (*dst == NULL) {
        return NULL;
    }

    size_t i = 0;
    while (src[i]) {
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
        free(current->type); 
        free(current);
        current = next;
    }
}


void add_node(t_token **head, const char *symbol) {
    t_token *tmp = malloc(sizeof(t_token));
    if (tmp == NULL) {
        // Handle malloc failure
        fprintf(stderr, "Memory allocation failed for new node.\n");
        return;
    }

    if (ft_strcpy(&tmp->type, symbol) == NULL) {
        // Handle strdup failure
        fprintf(stderr, "Memory allocation failed for symbol copy.\n");
        free(tmp);
        return;
    }

    tmp->next = NULL;

    if (*head == NULL) {
        *head = tmp;
    } else {
        t_token *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = tmp;
    }

    puts("Node added successfully.");
}