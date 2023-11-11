#ifndef TRIE_H
#define TRIE_H

#define N_OF_CHILDREN 26

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

typedef struct
{
    void *record;                   // NULL se não for terminal
    void *children[N_OF_CHILDREN];  // Ponteiros para os filhos
    void *parent;                   // NULL se for a Root
} TrieNode;

int charToTrieIdx(char character);
char trieIdxToChar(int trieIdx);

TrieNode *_newTrieNode(void *record, TrieNode *parent);

TrieNode *newTrie();

/*
Insere uma palavra em uma Trie

ATENÇÃO: Retorna o ultimo Nodo da trie o qual deve ser OBRIGATORIAMENTE atribuído um valor.
*/
TrieNode *insertWordIntoTrie(TrieNode *trie, char *word);

bool hasChild(TrieNode *trie);

void deleteNode(TrieNode *trie);

bool isLeaf(TrieNode *tree);

TrieNode *getChild(TrieNode *tree, char childChar);

TrieNode *getChildAt(TrieNode *tree, int childIdx);

TrieNode *printTrie(TrieNode *trie);

void _displayTrie(TrieNode *node, char str[], int level);

unsigned int countNumOfElements(TrieNode *trie);
void _countElems(TrieNode *node, unsigned int *elem, int level);

#endif