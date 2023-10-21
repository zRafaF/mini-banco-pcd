#include <stdio.h>

#include "fileops.h"
#include "trie.h"

int main() {
    printf("Number: %i, Letter: %c\n", charToTrieIdx('b'), trieIdxToChar(1));
    printf("Number: %i, Letter: %c\n", charToTrieIdx('c'), trieIdxToChar(2));
    printf("Number: %i, Letter: %c\n", charToTrieIdx('z'), trieIdxToChar(25));
    return 0;
}
