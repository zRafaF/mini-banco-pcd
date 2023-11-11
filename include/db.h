#ifndef DB_H
#define DB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "trie.h"

typedef struct
{
    char id[MAX_ID_SIZE];
    char fullName[MAX_FULL_NAME_SIZE];
    int age;
} PersonRecord;

typedef struct
{
    int size;
    TrieNode* trie;
} DataBase;

DataBase* createDataBase() {
    DataBase* db = (DataBase*)malloc(sizeof(DataBase));
    if (db == NULL) {
        fprintf(stderr, "Erro durante alocação de memoria do banco de dados\n");
        exit(EXIT_FAILURE);
    }
    db->size = 0;
    db->trie = newTrie();
    return db;
}

DataBase* insertNewRecord(DataBase* db, PersonRecord newRecord) {
    TrieNode* node = insertWordIntoTrie(db->trie, newRecord.id);
    PersonRecord* recordPtr = (PersonRecord*)malloc(sizeof(PersonRecord));

    if (recordPtr == NULL) {
        fprintf(stderr, "Erro durante alocação de memoria ao novo record\n");
        exit(EXIT_FAILURE);
    }

    strcpy(recordPtr->id, newRecord.id);
    strcpy(recordPtr->fullName, newRecord.fullName);
    recordPtr->age = newRecord.age;
    node->record = recordPtr;
    db->size++;
}

PersonRecord createPersonRecord(char id[16], char fullName[128], int age) {
    PersonRecord newRecord;
    strcpy(newRecord.id, id);
    strcpy(newRecord.fullName, fullName);
    newRecord.age = age;

    return newRecord;
}

void printEntireDB(DataBase* db) {
    printTrie(db->trie);
}

void deleteDataBase(DataBase* db) {
    deleteNode(db->trie);
    free(db);
}

#endif