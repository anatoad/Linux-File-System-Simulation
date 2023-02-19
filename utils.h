/* TOADER Ana-Maria, 314CB */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trees.h"

#define MAX_STRING_LENGTH 100
#define OFFSET_FIND 6

char *get_name(char *string);

TTree init_root();

int cmp_dir(void *a, void *b);

int cmp_file(void *a, void *b);

int cmp_dir_file(void *a, void *b);

int cmp_file_dir(void *a, void *b);

void print_dir(void *info);

void print_file(void *info);

void print_parent(TTree node);

void free_file(void **file);

void free_TFile(TFile **file);

void free_dir(void **dir);

void free_TDir(TDir **dir);

void erase_dir(void **info);

void free_directories(TTree *node, TFree free_info);

TTree find_dir(TTree tree, void *info, TFCmp cmp);

TTree find_file(TTree tree, void *info, TFCmp cmp);

#endif