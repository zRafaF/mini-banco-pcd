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

// Converte um char para o index do `children`
int charToTrieIdx(char character);

// Converte um index do `children` para seu char
char trieIdxToChar(int trieIdx);

// Função privada: Cria um novo nodo
TrieNode *_newTrieNode(void *record, TrieNode *parent);

/*
Instancia uma nova Trie e retorna o ponteiro para a root

ATENÇÃO: É necessário deletar esse Nodo.
*/
TrieNode *newTrie();

/*
Insere uma palavra em uma Trie

ATENÇÃO: Retorna o ultimo Nodo da trie o qual deve ser OBRIGATORIAMENTE atribuído um valor.
*/
TrieNode *insertWordIntoTrie(TrieNode *trie, char *word);

// Remove uma palavra em uma Trie
bool removeWordOfTrie(TrieNode *trie, char *word);

// Função privada: Remove os nodos de baixo para cima recursivamente
void _removeUpRecurse(TrieNode *trie);

// Verifica se um nodo possui um filho
bool hasChild(TrieNode *trie);

/*
Desaloca o `record` do nodo.

Caso o nodo não possua `children` sua memória sera desalocada e trocado para NULL no nodo pai.
*/
void deleteNode(TrieNode *trie);

// Verifica se um nodo é uma folha
bool isLeaf(TrieNode *tree);

// Retorna o nodo filho com um determinado valor
TrieNode *getChild(TrieNode *tree, char childChar);

// Retorna o nodo filho em um determinado índice
TrieNode *getChildAt(TrieNode *tree, int childIdx);

// Imprime todos os elementos contidos na Trie
TrieNode *printTrie(TrieNode *trie);

// Função privada: Recursão para imprimir a Trie
void _displayTrie(TrieNode *node, char str[], int level);

/*
Conta o numero de elementos guardados na Trie

ATENÇÃO: Essa função travesa por toda a trie
*/
unsigned int countNumOfElements(TrieNode *trie);

// Função privada: Recursão para contar o numero de elementos da Trie
void _countElems(TrieNode *node, unsigned int *elem, int level);

/*
Deleta a trie recursivamente, limpa os records

ATENÇÃO: Não deleta a root
*/
void deleteTrie(TrieNode *trie);

#endif
