#include "trie.h"

int charToTrieIdx(char character) {
    assert(((int)character >= 97) && ((int)character <= 122));

    return ((int)character) - 97;
}
char trieIdxToChar(int trieIdx) {
    assert(trieIdx >= 0 && trieIdx < N_OF_CHILDREN);

    return (char)(trieIdx + 97);
}

TrieNode *_newTrieNode(void *record, TrieNode *parent) {
    TrieNode *trie = (TrieNode *)malloc(sizeof(TrieNode));
    if (trie == NULL) {
        fprintf(stderr, "Erro durante alocação de memoria ao novo nodo da Trie\n");
        exit(EXIT_FAILURE);
    }
    trie->record = record;
    trie->parent = parent;
    for (int i = 0; i < N_OF_CHILDREN; i++) {
        trie->children[i] = NULL;
    }
    return trie;
}

TrieNode *newTrie() {
    return _newTrieNode(NULL, NULL);
}

TrieNode *insertWordIntoTrie(TrieNode *trie, char *word) {
    TrieNode *currentNode = trie;
    for (size_t i = 0; word[i] != '\0'; i++) {
        const char currentChar = word[i];

        TrieNode *childNodePtr = currentNode->children[charToTrieIdx(currentChar)];

        if (childNodePtr != NULL) {
            currentNode = childNodePtr;
            continue;
        }

        TrieNode *newNode = _newTrieNode(NULL, currentNode);
        currentNode->children[charToTrieIdx(currentChar)] = newNode;
        currentNode = newNode;
    }
    return currentNode;
}

TrieNode *findWordInTrie(TrieNode *trie, char *word) {
    TrieNode *lastNode = trie;
    for (size_t i = 0; word[i] != '\0'; i++) {
        const char currentChar = word[i];
        TrieNode *childNodePtr = lastNode->children[charToTrieIdx(currentChar)];

        if (childNodePtr != NULL) {
            lastNode = childNodePtr;
            continue;
        }
        return NULL;
    }
    if (lastNode->record)
        return lastNode;
    return NULL;
}

bool removeWordOfTrie(TrieNode *trie, char *word) {
    TrieNode *lastNode = findWordInTrie(trie, word);

    if (lastNode == NULL) return false;

    if (hasChild(lastNode)) {
        free(lastNode->record);
        lastNode->record = NULL;
        return true;
    }

    TrieNode *penultimateNode = lastNode->parent;

    deleteNode(lastNode);
    _removeUpRecurse(penultimateNode);

    return true;
}

void _removeUpRecurse(TrieNode *node) {
    TrieNode *parentNode = node->parent;
    if (node->record == NULL && node->parent && !hasChild(node)) {
        deleteNode(node);
        _removeUpRecurse(parentNode);
    }
}

bool hasChild(TrieNode *trie) {
    for (int i = 0; i < N_OF_CHILDREN; i++) {
        if (trie->children[i] != NULL)
            return true;
    }

    return false;
}

void deleteNode(TrieNode *trie) {
    free(trie->record);
    trie->record = NULL;

    if (hasChild(trie)) {
        return;
    }

    TrieNode *parentNode = trie->parent;

    for (int i = 0; i < N_OF_CHILDREN; i++) {
        if (parentNode->children[i] == trie)
            parentNode->children[i] = NULL;
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
    assert(childIdx >= 0 && childIdx < N_OF_CHILDREN);

    return (TrieNode *)(tree->children[childIdx]);
}

TrieNode *printTrie(TrieNode *trie) {
    int level = 0;
    char str[MAX_ID_SIZE];
    _displayTrie(trie, str, level);

    return trie;
}

void _displayTrie(TrieNode *node, char str[], int level) {
    if (node->record != NULL) {
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

unsigned int countNumOfElements(TrieNode *trie) {
    int level = 0;
    unsigned int elem = 0;
    _countElems(trie, &elem, level);

    return elem;
}

void _countElems(TrieNode *node, unsigned int *elem, int level) {
    if (isLeaf(node) || node->record != NULL) {
        (*elem)++;
    }

    for (int i = 0; i < N_OF_CHILDREN; i++) {
        if (node->children[i]) {
            _countElems(node->children[i], elem, level + 1);
        }
    }
}

void deleteTrie(TrieNode *trie) {
    for (int i = 0; i < N_OF_CHILDREN; i++) {
        if (trie->children[i]) {
            deleteTrie(trie->children[i]);
        }
    }
    if (trie->parent)
        deleteNode(trie);
    else {
        free(trie);
    }
}