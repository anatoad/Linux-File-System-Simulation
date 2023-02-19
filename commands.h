/* TOADER Ana-Maria, 314CB */
#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "utils.h"

void touch(TTree current_dir, char *name);

void mkdir(TTree current_dir, char *name);

void pwd(TTree node);

void ls(TTree tree);

void rm(TTree current_dir, char *name);

void rmdir(TTree current_dir, char *name);

void cd(TTree *current_dir, char *name);

void find_d(TTree current_dir, char *name);

void find_f(TTree current_dir, char *name);

#endif