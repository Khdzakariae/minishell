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

    printInorder(node->left);
    printf("data ids : %d\n", node->data);
    printInorder(node->right);
}

void preorder(t_tree *node)
{
    if (node == NULL)
        return;

    printf("data ids : %d\n", node->data);
    printInorder(node->left);
    printInorder(node->right);
}
void postorder(t_tree *node)
{
    if (node == NULL)
        return;

    printInorder(node->left);
    printInorder(node->right);
    printf("data ids : %d\n", node->data);
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
    root = insert(root, 2);
    root = insert(root, 100);
    root = insert(root, -10);

    puts("============== inorder ==============");
    printInorder(root);
    puts("============== preorder ==============");
    preorder(root);
    puts("============== postorder ==============");
    postorder(root);


}
