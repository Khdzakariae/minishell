#include <minishell.h>


// int main ()
// {
//     int id ;

//     while (1)
//     {
//         char *line = readline(COLOR_BOLD GRN "➜ minishell__v1 ✗ ");
//          char *cmd = "/usr/bin/line";
//         char *argvrc[] = {cmd, NULL , NULL};
//         char *envVec[] = {NULL};
//         id = fork();
//         if (id == 0)
//         {   
//             if(execve(cmd, argvrc, NULL) == -1)
//                 perror("not fount");
//         }
//         else
//             wait(NULL);
//     }
// }

bool search(t_tree *root, int data)
{
    if (root == NULL)
        return(false);
    else if (root->data == data)
        return(true);
    else if (root->data <= data)
        return(search(root->left, data));
    else
        return(search(root->right, data));
}


t_tree *get_new_node(int data)
{
    t_tree *new_node = malloc(sizeof(t_tree));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;
}


t_tree *insert(t_tree *root, int data)
{
    if (root == NULL)
    {
        root = get_new_node(data);
        return(root);
    }
    else if (data <= root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return(root);
}

long find_min(t_tree *root)
{
    if (root == NULL)
        return(549498487754545);
    t_tree *tmp = root;
    while (tmp->left != NULL)
    {
        tmp = tmp->left;
    }
    return(tmp->data);
}

long find_grand(t_tree *root)
{
    if (root == NULL)
        return(549498487754545);
    t_tree *tmp = root;
    while (tmp->right != NULL)
    {
        tmp = tmp->right;
    }
    return(tmp->data);
}

void printInorder(t_tree *node)
{
    if (node == NULL)
        return;

    // First recur on left child
    printInorder(node->left);

    // Then print the data of node
    printf("%d \n ", node->data);

    // Now recur on right child
    printInorder(node->right);
}

int main ()
{
    t_tree *root;
    int cherche = 0;
    root = NULL;
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 10);
    root = insert(root, 8);
    root = insert(root, 20);
    root = insert(root, 12);
    printInorder(root);


}



