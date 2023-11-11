#ifndef TEST_TRIE_H
#define TEST_TRIE_H

#include <unity.h>

#include "../include/trie.h"

int *_createFakeRecord() {
    return malloc(sizeof(int));
}

void test_trie_charToTrieIdx(void) {
    TEST_ASSERT_EQUAL_INT(0, charToTrieIdx('a'));
    TEST_ASSERT_EQUAL_INT(1, charToTrieIdx('b'));
    TEST_ASSERT_EQUAL_INT(25, charToTrieIdx('z'));
}
void test_trie_trieIdxToChar(void) {
    TEST_ASSERT_EQUAL_CHAR('a', trieIdxToChar(0));
    TEST_ASSERT_EQUAL_CHAR('b', trieIdxToChar(1));
    TEST_ASSERT_EQUAL_CHAR('z', trieIdxToChar(25));
}

void test_trie_newTrie(void) {
    TrieNode *trie = newTrie();
    TEST_ASSERT_NOT_NULL(trie);

    TEST_ASSERT_NULL(trie->parent);
    for (int i = 0; i < N_OF_CHILDREN; i++)
        TEST_ASSERT_NULL(trie->children[i]);

    deleteTrie(trie);
}

void test_trie_insertAndRemoveWordOfTrie(void) {
    TrieNode *trie = newTrie();

    TrieNode *insertedNode = insertWordIntoTrie(trie, "hello");
    TEST_ASSERT_NOT_NULL(insertedNode);

    TEST_ASSERT_NULL(insertedNode->record);

    TEST_ASSERT_NULL(findWordInTrie(trie, "he"));
    TEST_ASSERT_NULL(findWordInTrie(trie, "hello"));

    insertedNode->record = _createFakeRecord();
    TEST_ASSERT_NOT_NULL(insertedNode->record);

    TEST_ASSERT_NOT_NULL(findWordInTrie(trie, "hello"));
    TEST_ASSERT_NULL(findWordInTrie(trie, "he"));

    TEST_ASSERT_FALSE(removeWordOfTrie(trie, "he"));
    TEST_ASSERT_FALSE(removeWordOfTrie(trie, "abc"));
    TEST_ASSERT_TRUE(removeWordOfTrie(trie, "hello"));

    TEST_ASSERT_NULL(findWordInTrie(trie, "hello"));

    deleteTrie(trie);
}

void test_trie_isLeaf(void) {
    TrieNode *trie = newTrie();
    TEST_ASSERT_TRUE(isLeaf(trie));

    TrieNode *insertedNode = insertWordIntoTrie(trie, "hello");
    insertedNode->record = _createFakeRecord();

    TEST_ASSERT_FALSE(isLeaf(trie));
    TEST_ASSERT_TRUE(isLeaf(insertedNode));
    TEST_ASSERT_FALSE(isLeaf(insertedNode->parent));

    deleteTrie(trie);
}

void test_trie_getChild(void) {
    TrieNode *trie = newTrie();

    TrieNode *insertedNode = insertWordIntoTrie(trie, "hello");
    insertedNode->record = _createFakeRecord();

    TEST_ASSERT_NULL(getChild(trie, 'a'));

    TrieNode *h_node = getChild(trie, 'h');
    TrieNode *e_node = getChild(h_node, 'e');
    TrieNode *l_node = getChild(e_node, 'l');
    TrieNode *l2_node = getChild(l_node, 'l');
    TrieNode *o_node = getChild(l2_node, 'o');

    TEST_ASSERT_NOT_NULL(h_node);
    TEST_ASSERT_NULL(getChild(h_node, 'a'));
    TEST_ASSERT_NOT_NULL(e_node);
    TEST_ASSERT_NOT_NULL(o_node);
    TEST_ASSERT_NULL(getChild(o_node, '\n'));

    deleteTrie(trie);
}

void test_trie_getChildAt(void) {
    TrieNode *trie = newTrie();

    TrieNode *insertedNode = insertWordIntoTrie(trie, "hello");
    insertedNode->record = _createFakeRecord();

    TEST_ASSERT_NULL(getChildAt(trie, charToTrieIdx('a')));

    TrieNode *h_node = getChildAt(trie, charToTrieIdx('h'));
    TrieNode *e_node = getChildAt(h_node, charToTrieIdx('e'));
    TrieNode *l_node = getChildAt(e_node, charToTrieIdx('l'));
    TrieNode *l2_node = getChildAt(l_node, charToTrieIdx('l'));
    TrieNode *o_node = getChildAt(l2_node, charToTrieIdx('o'));

    TEST_ASSERT_NOT_NULL(h_node);
    TEST_ASSERT_NULL(getChildAt(h_node, charToTrieIdx('a')));
    TEST_ASSERT_NOT_NULL(e_node);
    TEST_ASSERT_NOT_NULL(o_node);

    deleteTrie(trie);
}

void test_trie_countNumOfElements(void) {
    TrieNode *trie = newTrie();

    insertWordIntoTrie(trie, "hello")->record = _createFakeRecord();
    TEST_ASSERT_EQUAL_INT(1, countNumOfElements(trie));

    insertWordIntoTrie(trie, "hello");
    TEST_ASSERT_EQUAL_INT(1, countNumOfElements(trie));

    insertWordIntoTrie(trie, "he")->record = _createFakeRecord();
    TEST_ASSERT_EQUAL_INT(2, countNumOfElements(trie));

    insertWordIntoTrie(trie, "abc")->record = _createFakeRecord();
    TEST_ASSERT_EQUAL_INT(3, countNumOfElements(trie));

    removeWordOfTrie(trie, "hello");
    TEST_ASSERT_EQUAL_INT(2, countNumOfElements(trie));

    deleteTrie(trie);
}

void test_trie_deleteNode(void) {
    TrieNode *trie = newTrie();

    insertWordIntoTrie(trie, "abcd")->record = _createFakeRecord();

    TrieNode *a_node = getChild(trie, 'a');
    TrieNode *b_node = getChild(a_node, 'b');
    TrieNode *c_node = getChild(b_node, 'c');
    TrieNode *d_node = getChild(c_node, 'd');

    TEST_ASSERT_NOT_NULL(findWordInTrie(trie, "abcd"));
    TEST_ASSERT_NULL(findWordInTrie(trie, "abc"));

    insertWordIntoTrie(trie, "abc")->record = _createFakeRecord();
    TEST_ASSERT_NOT_NULL(findWordInTrie(trie, "abc"));

    deleteNode(c_node);
    TEST_ASSERT_NULL(findWordInTrie(trie, "abc"));

    insertWordIntoTrie(trie, "abc")->record = _createFakeRecord();
    deleteNode(d_node);
    TEST_ASSERT_NULL(findWordInTrie(trie, "abcd"));

    deleteTrie(trie);
}

#endif