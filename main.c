/* TOADER Ana-Maria, 314CB */
#include "commands.h"

int main()
{
    char *name = NULL;
    TTree root = init_root();
    if (!root)
        return -1;

    TTree current_dir = root;

    char *string = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
    if (!string) {
        free(root);
        return -1;
    }

    while (fgets(string, MAX_STRING_LENGTH, stdin)) {
        if (string[strlen(string) - 1] == '\n')
            string[strlen(string) - 1] = '\0';

        if (strstr(string, "touch")) {  /* touch */
            name = get_name(string);
            touch(current_dir, name);

        } else if (strstr(string, "mkdir")) {  /* mkdir */
            name = get_name(string);
            mkdir(current_dir, name);

        } else if (strstr(string, "ls")) {  /* ls */
            ls(current_dir);

        } else if (strstr(string, "rm ")) {  /* rm */
            name = get_name(string);
            rm(current_dir, name);

        } else if (strstr(string, "rmdir")) {  /* rmdir */
            name = get_name(string);
            rmdir(current_dir, name);

        } else if (strstr(string, "cd")) {  /* cd */
            name = get_name(string);
            cd(&current_dir, name);

        } else if (strstr(string, "pwd")) {  /* pwd */
            pwd(current_dir);

        } else if (strstr(string, "find -d")) {  /* find -d */
            name = get_name(string + OFFSET_FIND);
            find_d(root, name);

        } else if (strstr(string, "find -f")) {
            name = get_name(string + OFFSET_FIND);
            find_f(root, name);
        }

        if (name) {
            free(name);
            name = NULL;
        }
    }

    free(string);
    free_directories(&root, free_dir);
    
    return 0;
}