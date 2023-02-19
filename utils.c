/* TOADER Ana-Maria, 314CB */
#include "utils.h"

/* Function get_name parses the given string and returns the string formed
by the sequence of letters found after the first space (' ') character. */
char *get_name(char *string)
{
    int i = 0, n = strlen(string), length = 0;
    while (string[i] != ' ' && i < n)
        i++;
    
    length = n - i + 2;

    char *name = (char *)calloc(length, sizeof(char));
    if (!name)
        return NULL;

    strncpy(name, string + i + 1, length);

    return name;
}

/* Function init_root allocates memory for a generic element of type TNode,
initialising the info field with a TDir element with name 'root'. */
TTree init_root()
{
    TTree root = (TTree)malloc(sizeof(TNode));
    if (!root)
        return NULL;

    root->info = init_dir("root", NULL);
    if (!root->info) {
        free(root);
        return NULL;
    }

    root->left = NULL;
    root->right = NULL;

    return root;
}

/* Function cmp_dir compares the name fields of two TDir elements. */
int cmp_dir(void *a, void *b)
{
    return strcmp(((TDir *)a)->name, ((TDir *)b)->name);
}

/* Function cmp_file compares the name fields of two TFile elements. */
int cmp_file(void *a, void *b)
{
    return strcmp(((TFile *)a)->name, ((TFile *)b)->name);
}

/* Function cmp_dir_file compares the name fields of a TDir element (first
parameter) and TFile element (second parameter). */
int cmp_dir_file(void *a, void *b)
{
    return strcmp(((TDir *)a)->name, ((TFile *)b)->name);
}

/* Function cmp_dir_file compares the name fields of a TFile element (first
parameter) and TDir element (second parameter). */
int cmp_file_dir(void *a, void *b)
{
    return strcmp(((TFile *)a)->name, ((TDir *)b)->name);
}

/* Function print_dir prints the name field of a TDir element. */
void print_dir(void *info)
{
    printf("%s ", ((TDir *)info)->name);
}

/* Function print_file prints the name field of a TFile element. */
void print_file(void *info)
{
    printf("%s ", ((TFile *)info)->name);
}

/* Function print_parent recursively prints the name field of TDir elements
in all parent nodes starting with 'node', until reaching the root node. */
void print_parent(TTree node)
{
    if (!node)
        return;

    TDir *dir = (TDir *)node->info;
    if (!dir)
        return;

    print_parent(dir->parent);
    printf("/%s", dir->name);
}

/* Function free_file is a generic function used to cast a void* element to a
TFile* element and free its memory using the free_TFile function. */
void free_file(void **file)
{
    free_TFile((TFile **)file);
}

/* Function free_TFile is used to free memory occupied by a TFile element. */
void free_TFile(TFile **file)
{
    if (!(*file))
        return;
    free((*file)->name);
    free(*file);
    *file = NULL;
}

/* Function free_dir is a generic function used to cast a void* element to a
TDir* element and free its memory using the free_TDir function. */
void free_dir(void **dir)
{
    free_TDir((TDir **)dir);
}

/* Function free_TDir is used to free memory occupied by a TDir element. */
void free_TDir(TDir **dir)
{
    if (!(*dir))
        return;
    free((*dir)->name);
    free(*dir);
    *dir = NULL;
}

/* Function erase_dir is a generic function used to free all fields of a TDir
element (directory) including the directories subtree and the files subtree. */
void erase_dir(void **info)
{
    TDir *dir = (TDir *)(*info);  /* cast element to TDir* */

    free(dir->name);  /* free the name field */

    /* recursively free all elements in the directories subtree */
    free_directories(&dir->directories, free_dir);

    /* recursively free all elements in the files subtree */
    free_tree(&dir->files, free_file);

    free(*info);
    *info = NULL;
}

/* Function free_directories is used to recursively free memory occupied by
a tree using the function free_info to free the info fields of each node. */
void free_directories(TTree *node, TFree free_info)
{
    if (!(*node))
        return;
    
    if ((*node)->left)  /* free the left subtree */
        free_directories(&(*node)->left, free_info);

    if ((*node)->right)  /* free the right subtree */
        free_directories(&(*node)->right, free_info);

    /* free the subtree in the directories field */
    free_directories(&((TDir *)(*node)->info)->directories, free_dir);

    /* free the subtree in the files field */
    free_tree(&((TDir *)(*node)->info)->files, free_file);

    /* free the information field */
    free_info(&(*node)->info);
    free(*node);
    *node = NULL;
}

/* Function find_dir searches for an element in a given tree of directories
using comparison function cmp and generic element info as reference, returns
pointer to the node if found, returns NULL if element is not found. */
TTree find_dir(TTree tree, void *info, TFCmp cmp)
{
    if (!tree)
        return NULL;

    TDir *dir = (TDir *)tree->info;

    if (!cmp(tree->info, info))  /* if element is found */
        return tree;

    /* search in the directories subtree of the current directory */
    TTree node = find_dir(dir->directories, info, cmp);
    if (node)
        return node;
    
    /* search in the left subtree of the current node */
    node = find_dir(tree->left, info, cmp);
    if (node)
        return node;

    /* search in the right subtree of the current node */
    node = find_dir(tree->right, info, cmp);
    if (node)
        return node;

    return NULL;
}

/* Function find_file searches for an TFile element in a given tree using the 
comparison function cmp and the generic element info as reference, returns
pointer to the node if element is found, returns NULL otherwise. */
TTree find_file(TTree tree, void *info, TFCmp cmp)
{
    if (!tree)
        return NULL;
    
    TDir *dir = (TDir *)tree->info;

    /* search in the files subtree of the current directory */
    TTree node = search(dir->files, info, cmp);
    if (node)
        return node;

    /* search in the directories subtree of the current directory */
    node = find_file(dir->directories, info, cmp);
    if (node)
        return node;

    /* search in the left subtree of the current node */
    node = find_file(tree->left, info, cmp);
    if (node)
        return node;

    /* search in the right subtree of the current node */
    node = find_file(tree->right, info, cmp);
    if (node)
        return node;

    return NULL;
}
