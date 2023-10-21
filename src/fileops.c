#include "fileops.h"

#include <stdio.h>

void printAll() {
    printf("printed from inside");
}

void readFile() {
    char *filename = "banco.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: could not open file %s", filename);
        return;
    }

    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp))
        printf("%s", buffer);

    // close the file
    fclose(fp);
}