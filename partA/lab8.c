#include <stdio.h>
#include <stdlib.h>

void displayFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    printf("filename:%s\n", filename);
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    
    printf("\n");
    
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 file2 ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        displayFile(argv[i]);
    }

    return 0;
}
