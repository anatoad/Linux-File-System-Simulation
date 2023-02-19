/* TOADER Ana-Maria, 314CB */
#include "commands.h"

/* Function touch inserts a new file with the given name in the files field
(binary search tree) of the given directory. */
void touch(TTree current_dir, char *name)
{
    if (!name || !current_dir)
        return;

    TDir *dir = (TDir *)current_dir->info;
    if (!dir)
        return;

    /* allocate memory for the new file */
    TFile *file = init_file(name, current_dir);
    if (!file)
        return;

    /* search for an existing directory with the same name */
    TTree found = search(dir->directories, file, cmp_dir_file);
    if (found) {
        printf("Directory %s already exists!\n", name);
        free_TFile(&file);
        return;
    }

    if (insert(&dir->files, file, cmp_file) < 0) {
        printf("File %s already exists!\n", name);
        free_TFile(&file);
    }
}

/* Function mkdir inserts a new directory with the given name in the
directories field (binary search tree) of the given directory. */
void mkdir(TTree current_dir, char *name)
{
    if (!name || !current_dir)
        return;

    TDir *dir = (TDir *)current_dir->info;
    if (!dir)
        return;

    /* allocate memory for a new directory */
    TDir *new_dir = init_dir(name, current_dir);
    if (!new_dir)
        return;

    /* search for an existing file with the same name */
    TTree found = search(dir->files, new_dir, cmp_file_dir);
    if (found) {
        printf("File %s already exists!\n", name);
        free_TDir(&new_dir);
        return;
    }

    if (insert(&dir->directories, new_dir, cmp_dir) < 0) {
        printf("Directory %s already exists!\n", name);
        free_TDir(&new_dir);
    }
}

/* Function pwd is used to print the path from the root to the given node. */
void pwd(TTree node)
{
    print_parent(node);
    printf("\n");
}

/* Function ls prints the information from the directories subtree and files
subtree of a given node (directory) in lexicographical order. */
void ls(TTree tree)
{
    if (!tree)
        return;

    TDir *current_dir = (TDir *)tree->info;
    if (!current_dir)
        return;
    
    /* print the directories subtree */
    print_tree(current_dir->directories, print_dir);

    /* print the files subtree */
    print_tree(current_dir->files, print_file);

    printf("\n");
}

/* Function rm removes a node (file with given name) from the files subtree
of a given directory. */
void rm(TTree current_dir, char *name)
{
    if (!name || !current_dir)
        return;

    TDir *dir = (TDir *)current_dir->info;
    if (!dir)
        return;

    /* allocate memory for a new (temporary) file with the given name */
    TFile *file = init_file(name, current_dir);
    if (!file)
        return;

    if (delete(&dir->files, file, cmp_file, free_file) < 0)
        printf("File %s doesn't exist!\n", name);

    free_TFile(&file);
}

/* Function rmdir removes a node (directory with a given name) from the
directories subtree of a given directory. */
void rmdir(TTree current_dir, char *name)
{
    if (!name || !current_dir)
        return;

    TDir *dir = (TDir *)current_dir->info;
    if (!dir)
        return;
    
    /* allocate memory for a new directory with the given name */
    TDir *new_dir = init_dir(name, current_dir);
    if (!new_dir)
        return;
    
    if (delete(&dir->directories, new_dir, cmp_dir, erase_dir) < 0)
        printf("Directory %s doesn't exist!\n", name);

    free_TDir(&new_dir);
}

/* Function cd is used to change the value of the current directory to either
its parent (if name is "..") or to a subdirectory with given name. */
void cd(TTree *current_dir, char *name)
{
    if (!name || !current_dir)
        return;

    TDir *dir = (TDir *)(*current_dir)->info;
    if (!dir)
        return;

    if (!strcmp(name, "..")) {
        if (dir->parent)  /* if node is not the root (has a parent != null) */
            *current_dir = dir->parent;
        return;
    }

    /* allocate memory for a new directory with the given name */
    TDir *new_dir = init_dir(name, *current_dir);
    if (!new_dir)
        return;

    /* search for an existing directory with the same name in the
    subdirectories of the current directory */
    TTree new_node = search(dir->directories, new_dir, cmp_dir);
    if (!new_node)
        printf("Directory not found!\n");
    else
        *current_dir = new_node;

    free_TDir(&new_dir);
}

/* Function find_d is used to search for a directory with the given name
in all directories subtrees, starting from the given directory. */
void find_d(TTree current_dir, char *name)
{
    if (!name || !current_dir)
        return;

    TDir *dir = (TDir *)current_dir->info;
    if (!dir)
        return;

    TDir *new_dir = init_dir(name, current_dir);
    if (!new_dir)
        return;

    TTree found = find_dir(dir->directories, new_dir, cmp_dir);
    if (found) {
        printf("Directory %s found!\n", name);
        pwd(found);
    } else {
        printf("Directory %s not found!\n", name);
    }

    free_TDir(&new_dir);
}

/* Function find_f is used to search for a file with the given name in all
files subtrees, starting from the given directory. */
void find_f(TTree current_dir, char *name)
{
    if (!name || !current_dir)
        return;

    TDir *dir = (TDir *)current_dir->info;
    if (!dir)
        return;

    TFile *new_file = init_file(name, current_dir);
    if (!new_file)
        return;

    TTree found = find_file(current_dir, new_file, cmp_file);
    if (found) {
        printf("File %s found!\n", name);
        print_parent(((TFile *)found->info)->parent);
        printf("\n");
    } else {
        printf("File %s not found!\n", name);
    }

    free_TFile(&new_file);
}
