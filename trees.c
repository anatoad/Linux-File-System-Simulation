/* TOADER Ana-Maria, 314CB */
#include "trees.h"

/* Function search searches for an element info in a given tree, using the cmp
comparison function. Returns pointer to element if found, NULL otherwise. */
TTree search(TTree tree, void *info, TFCmp cmp)
{
    if (!tree || !info)  /* invalid arguments */
        return NULL;

    TTree node = tree;
    while (node) {
        if (!cmp(node->info, info))  /* element was found */
            return node;
        if (cmp(node->info, info) > 0)
            node = node->left;  /* search in the left subtree */
        else
            node = node->right;  /* search in the right subtree */
    }

    return NULL;
}

/* Function init_node dynamically allocates an element of type TNode,
initialises info field with given parameter. Returns pointer to the element,
if allocated successfully, NULL otherwise. */
TTree init_node(void *info)
{
    TTree node = (TTree)malloc(sizeof(TNode));
    if (!node)  /* allocation failed */
        return NULL;

    node->info = info;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* Function init_dir dynamically allocates an element of type TDir, initialises
fields name and parent with given parameters. Returns pointer to the element, if
allocated successfully, NULL otherwise. */
TDir *init_dir(char *name, TTree parent)
{
    TDir *dir = (TDir *)malloc(sizeof(TDir));
    if (!dir)
        return NULL;

    /* allocate enough memory for the name field */
    dir->name = (char *)malloc(strlen(name) + 1);
    if (!dir->name) {
        free(dir);
        return NULL;
    }

    /* copy the information into the name field */
    strncpy(dir->name, name, strlen(name) + 1);

    dir->parent = parent;
    dir->directories = NULL;
    dir->files = NULL;
    
    return dir;
}

/* Function init_file allocates an element of type TFile, initialises fields
name and parent with given parameters. */
TFile *init_file(char *name, TTree parent)
{
    TFile *file = (TFile *)malloc(sizeof(TFile));
    if (!file)
        return NULL;

    file->name = (char *)malloc(strlen(name) + 1);
    if (!file->name) {
        free(file);
        return NULL;
    }

    strncpy(file->name, name, strlen(name) + 1);
    file->parent = parent;

    return file;
}

/* Function insert inserts a new node into the given binary search tree,
initialising the info field of the node with the given parameter (info). */
int insert(TTree *tree, void *info, TFCmp cmp)
{
    TTree parent = NULL, node = *tree;
    while (node) {
        parent = node;
        if (!cmp(node->info, info))  /* information exists in the tree */
            return -1;
        if (cmp(node->info, info) > 0)
            node = node->left;
        else
            node = node->right;        
    }

    /* allocate memory for a new node which contains the given information */
    TTree new_node = init_node(info);
    if (!new_node)
        return 0;
    
    if (!parent) {  /* tree is initially empty */
        *tree = new_node;
        return 1;
    }

    if (cmp(parent->info, new_node->info) > 0)  /* insert to the left */
        parent->left = new_node;
    else  /* insert to the right */
        parent->right = new_node;

    return 1;
}

/* Function delete is used to remove a node from a given binary search tree,
node which contains the same information as info. */
int delete(TTree *tree, void *info, TFCmp cmp, TFree free_info)
{
    if(!(*tree))
        return -1;

    TTree node = *tree, parent = NULL;

    while (node) {
        if (!cmp(node->info, info)) {  /* element to be removed is found */
            if (node->left && node->right) {  /* if node has two sons */
                /* get the maximum value (succ) from the left subtree
                and the parent node of this maximum value (pred) */
                TTree pred = NULL, succ = node->left;
                while (succ->right) {
                    pred = succ;
                    succ = succ->right;
                }

                /* delete the information */
                free_info(&node->info);

                if (pred) {
                    pred->right = succ->left;
                    node->info = succ->info;
                } else {
                    if (parent) {  /* node to be deleted is not the root */
                        node->left = succ->left;
                        node->info = succ->info;
                    } else {  /* node to be deleted is the root */
                        (*tree)->left = succ->left;
                        (*tree)->info = succ->info;
                    }
                }

                free(succ);
                return 1;
            }

            TTree son = NULL;
        
            /* if node only has one son */
            son = (node->left) ? node->left : node->right;

            if (parent) {
                if (parent->right == node)  /* right son */
                    parent->right = son;
                else  /* left son */
                    parent->left = son;
            } else {
                *tree = son;
            }

            if (node)
                free_info(&node->info);
                
            free(node);
            node = NULL;
            return 1;
        }
        parent = node;

        if (cmp(node->info, info) > 0)
            node = node->left;
        else
            node = node->right;
    }
    
    return -1;
}

/* Function print_tree recursively prints information from nodes in a given
binary search tree using an inorder traversal (left, root, right). */
void print_tree(TTree node, TFPrint print)
{
    if (!node)
        return;
    
    /* print the information from the left subtree */
    print_tree(node->left, print);

    /* print the information from the current node */
    print(node->info);

    /* print the information from the right subtree */
    print_tree(node->right, print);
}

/* Function free_tree is used to free memory occupied by a given tree. */
void free_tree(TTree *node, TFree free_info)
{
    if (!(*node))
        return;
    
    if ((*node)->left)  /* free the left subtree */
        free_tree(&(*node)->left, free_info);

    if ((*node)->right)  /* free the right subtree */
        free_tree(&(*node)->right, free_info);

    /* free the information in the current node */
    free_info(&(*node)->info);
    free(*node);
    *node = NULL;
}
