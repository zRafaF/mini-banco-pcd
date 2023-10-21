#ifndef TRIE_H
#define TRIE_H

#define N_OF_CHILDREN 26

#include <stdbool.h>
#include <stdio.h>

#include "db.h"

typedef struct
{
    PersonRecord *record;
    void *children[26];  // Ponteiros para os filhos
    bool isTerminal;
} TrieNode;

int charToTrieIdx(char character) {
    return ((int)character) - 97;
}
char trieIdxToChar(int trieIdx) {
    return (char)(trieIdx + 97);
}

TrieNode *newTrieNode(PersonRecord *record, bool isTerminal) {
    TrieNode trie;
    trie.record = record;
    trie.isTerminal = isTerminal;
    for (int i = 0; i < N_OF_CHILDREN; i++) {
        trie.children[i] = NULL;
    }
}

bool isLeaf(TrieNode *tree) {
    for (int i = 0; i < N_OF_CHILDREN; i++) {
        if (tree->children[i] != NULL)
            return false;
    }
    return true;
}

TrieNode *getChild(TrieNode *tree, char childChar) {
    for (int i = 0; i < N_OF_CHILDREN; i++) {
        if (trieIdxToChar(i) == childChar)
            return (TrieNode *)(tree->children[i]);
    }
    return NULL;
}

TrieNode *getChildAt(TrieNode *tree, int childIdx) {
    return (TrieNode *)(tree->children[childIdx]);
}

TrieNode *printTrie(TrieNode *tree) {
    unsigned int trieLayers = 0;
    while (true) {
        /* code */
    }
}

void display(TrieNode *node, char str[], int level) {
    if (isLeaf(node)) {
        str[level] = '\0';
        printf("%s", str);
    }
    int i;
    for (i = 0; i < N_OF_CHILDREN; i++) {
        if (node->children[i]) {
            str[level] = i + 'a';
            display(getChildAt(node, i), str, level + 1);
        }
    }
}

#endif