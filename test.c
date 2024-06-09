// bool search(t_tree *root, int data)
// {
//     if (root == NULL)
//         return(false);
//     else if (root->data == data)
//         return(true);
//     else if (root->data <= data)
//         return(search(root->left, data));
//     else
//         return(search(root->right, data));
// }


// t_tree *get_new_node(int data)
// {
//     t_tree *new_node = malloc(sizeof(t_tree));
//     new_node->data = data;
//     new_node->left = NULL;
//     new_node->right = NULL;
    
//     return new_node;
// }


// t_tree *insert(t_tree *root, int data)
// {
//     if (root == NULL)
//     {
//         root = get_new_node(data);
//         return(root);
//     }
//     else if (data <= root->data)
//         root->left = insert(root->left, data);
//     else
//         root->right = insert(root->right, data);
//     return(root);
// }

// long find_min(t_tree *root)
// {
//     if (root == NULL)
//         return(549498487754545);
//     t_tree *tmp = root;
//     while (tmp->left != NULL)
//     {
//         tmp = tmp->left;
//     }
//     return(tmp->data);
// }

// long find_grand(t_tree *root)
// {
//     if (root == NULL)
//         return(549498487754545);
//     t_tree *tmp = root;
//     while (tmp->right != NULL)
//     {
//         tmp = tmp->right;
//     }
//     return(tmp->data);
// }

// void printInorder(t_tree *node)
// {
//     if (node == NULL)
//         return;

//     printInorder(node->left);
//     printf("data ids : %d\n", node->data);
//     printInorder(node->right);
// }

// void preorder(t_tree *node)
// {
//     if (node == NULL)
//         return;

//     printf("data ids : %d\n", node->data);
//     printInorder(node->left);
//     printInorder(node->right);
// }
// void postorder(t_tree *node)
// {
//     if (node == NULL)
//         return;

//     printInorder(node->left);
//     printInorder(node->right);
//     printf("data ids : %d\n", node->data);
// }

// int main ()
// {
//     t_tree *root;
//     int cherche = 0;
//     root = NULL;
//     root = insert(root, 15);
//     root = insert(root, 25);
//     root = insert(root, 10);
//     root = insert(root, 8);
//     root = insert(root, 20);
//     root = insert(root, 12);
//     root = insert(root, 2);
//     root = insert(root, 100);
//     root = insert(root, -10);

//     puts("============== inorder ==============");
//     printInorder(root);
//     puts("============== preorder ==============");
//     preorder(root);
//     puts("============== postorder ==============");
//     postorder(root);


// }

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_token {
    char *type;
    struct s_token *next;
} t_token;

size_t ft_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

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

void freeList(t_token *head) {
    t_token *current = head;
    t_token *next;

    while (current != NULL) {
        next = current->next;
        free(current->type);
        free(current);
        current = next;
    }
}

void printList(t_token* head) {
    t_token* current = head;

    while (current != NULL) {
        printf("%s\n", current->type);
        current = current->next;
    }
    printf("\n");
}

int main() {
    t_token *token_list = NULL;

    add_node(&token_list, "(");
    add_node(&token_list, ")");
    add_node(&token_list, "\\");
    add_node(&token_list, "\"");

    // Print the list
    printList(token_list);

    // Free the list
    freeList(token_list);

    return 0;
}
