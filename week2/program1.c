#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main() {
    DIR *dir; // Pointer to directory stream
    struct dirent *entry; // Pointer to directory entry

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        exit(1);
    }

    printf("Contents of the current directory:\n");

    // Read and print each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}