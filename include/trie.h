#ifndef TRIE_H
#define TRIE_H

#define N_OF_CHILDREN 26

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

typedef struct
{
    void *record;        // NULL se não for terminal
    void *children[26];  // Ponteiros para os filhos
    void *parent;        // NULL se for a Root
} TrieNode;

int charToTrieIdx(char character) {
    return ((int)character) - 97;
}
char trieIdxToChar(int trieIdx) {
    return (char)(trieIdx + 97);
}

TrieNode *_newTrieNode(void *record, TrieNode *parent) {
    TrieNode *trie = (TrieNode *)malloc(sizeof(TrieNode));
    if (trie == NULL) {
        fprintf(stderr, "Erro durante alocação de memoria ao novo nodo da Trie\n");
        exit(EXIT_FAILURE);
    }
    trie->record = record;
    for (int i = 0; i < N_OF_CHILDREN; i++) {
        trie->children[i] = NULL;
    }
    return trie;
}

TrieNode *newTrie() {
    return _newTrieNode(NULL, NULL);
}

/*
Insere uma palavra em uma Trie

ATENÇÃO: Retorna o ultimo Nodo da trie o qual deve ser OBRIGATORIAMENTE atribuído um valor.
*/
TrieNode *insertWordIntoTrie(TrieNode *trie, char *word) {
    TrieNode *currentNode = trie;
    for (size_t i = 0; word[i] != '\0'; i++) {
        const char currentChar = word[i];

        TrieNode *newNode = _newTrieNode(NULL, currentNode);
        currentNode->children[charToTrieIdx(currentChar)] = newNode;
        currentNode = newNode;
    }
    return currentNode;
}

bool hasChild(TrieNode *trie) {
    for (int i = 0; i < N_OF_CHILDREN; i++) {
        if (trie->children[i] != NULL)
            return true;
    }

    return false;
}

void deleteNode(TrieNode *trie) {
    for (int i = 0; i < N_OF_CHILDREN; i++) {
        TrieNode *child = trie->children[i];
        if (child != NULL) {
            if (child->record != NULL) {
                free(trie->record);
            }
            deleteNode(child);
        }
    }

    free(trie);
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

TrieNode *printTrie(TrieNode *trie) {
    int level = 0;
    char str[MAX_ID_SIZE];
    printf("Imprimindo conteudo da trie:\n");
    _displayTrie(trie, str, level);
}

void _displayTrie(TrieNode *node, char str[], int level) {
    if (isLeaf(node)) {
        str[level] = '\0';
        printf("%s\n", str);
    }

    for (int i = 0; i < N_OF_CHILDREN; i++) {
        if (node->children[i]) {
            str[level] = i + 'a';
            _displayTrie(node->children[i], str, level + 1);
        }
    }
}

#endif