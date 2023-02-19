## Linux-File-System-Simulation

Linux file system simulator, generic commands implementation (touch, mkdir, ls, pwd, rm, rmdir, cd, find -f, find -d).

The implementation is based on generic binary search trees, each node having the fields: info, left, right. The left and right field contain pointers to the two direct descendants
of a node. The 'info' field is a generic pointer which stores either a directory (TDir type) or a file (TFile type).

### **main.c**
The input commands are parsed using functions from the utils source and header file. Each command (ls, touch, mkdir, rm, rmdir, cd, pwd, find) has a corresponding function,
implemented to solve the problem requirements. All previously allocated memory is freed, ensuring that there are no memory leaks.

### **utils.c utils.h**
Functions used to maintain the binary search tree structure of the files system. Here there are also defined functions used to free the memory of such data structures
using recursion, as well as functions used to print information and parse input strings.

### **trees.c trees.h**
Generic functions used to perform the main operations on binary search trees: initialising nodes, inserting nodes into a tree, removing nodes from trees, as well as printing information
from a tree and freeing the memory of such a structure.

### **commands.c commands.h**
- **pwd** - prints the path to the working directory  
- **touch** - creates a new file in the current directory by inserting a new node into the files subtree, if a file or directory with the same name doesn't already exist  
- **mkdir** - similar to touch, except it inserts a new node containing a directory, not a file  
- **ls** - prints the information from the directories and files subtree of a given node in lexicographical order using recursion  
- **rm** - deletes a file with a given name  
- **rmdir** - recursively deletes a directory with a given name  
- **cd** - modifies the value of the current node according to the wanted destination directory and whether or not it is found in the file system  
- **find -f** - search for a file in the file system, starting from the root directory, searching in every directories subtree and files subtree  
- **find -d** - search for a directory in the file system  
