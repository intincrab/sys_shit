#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Executing ls command...\n");
    
    execlp("ls", "ls", "-l", NULL); // execute ls command

    exit(1);
}