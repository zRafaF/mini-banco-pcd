#include <stdio.h>
#include <unity.h>

#include "test_db.h"
#include "test_trie.h"

void setUp(void) {}
void tearDown(void) {}

int main() {
    strncpy(testDbPathGlobal, "banco_teste.txt", PATH_STRING_SIZE - 1);

    UNITY_BEGIN();

    // Testando Trie
    RUN_TEST(test_trie_charToTrieIdx);
    RUN_TEST(test_trie_trieIdxToChar);
    RUN_TEST(test_trie_newTrie);
    RUN_TEST(test_trie_insertAndRemoveWordOfTrie);
    RUN_TEST(test_trie_isLeaf);
    RUN_TEST(test_trie_getChild);
    RUN_TEST(test_trie_getChildAt);
    RUN_TEST(test_trie_countNumOfElements);
    RUN_TEST(test_trie_deleteNode);

    // Testando o Banco de Dados
    RUN_TEST(test_db__invertString);
    RUN_TEST(test_db_parseData);
    RUN_TEST(test_db_e2e);
    RUN_TEST(test_dbui__processUserInput);

    remove(testDbPathGlobal);

    return UNITY_END();
}
