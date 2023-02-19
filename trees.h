/* TOADER Ana-Maria, 314CB */
#ifndef __TREES_H__
#define __TREES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    void *info;             /* node generic information */
    struct node *left;      /* left subtree */
    struct node *right;     /* right subtree */
} TNode, *TTree;            /* binary search tree structure */

typedef struct dir {
    char *name;             /* name of directory */
    TTree parent;           /* pointer to the parent directory */
    TTree files;            /* pointer to the root of files tree */
    TTree directories;      /* pointer to the root of directories tree */
} TDir;                     /* directory information */

typedef struct file {
    char *name;             /* name of file */
    TTree parent;           /* pointer to the parent directory */
} TFile;                    /* file information */

typedef int (*TFCmp)(void *, void *);

typedef void (*TFPrint)(void *);

typedef void (*TFree)(void **);

TTree search(TTree tree, void *info, TFCmp cmp);

TTree init_node(void *info);

TDir *init_dir(char *name, TTree parent);

TFile *init_file(char *name, TTree parent);

int insert(TTree *tree, void *info, TFCmp cmp);

int delete(TTree *tree, void *info, TFCmp cmp, TFree free_info);

void print_tree(TTree node, TFPrint print);

void free_tree(TTree *node, TFree free_info);

#endif