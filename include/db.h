#ifndef DB_H
#define DB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    TrieNode* trie;
} DataBase;

DataBase* createDataBase();

DataBase* insertNewRecord(DataBase* db, PersonRecord newRecord);

PersonRecord createPersonRecord(char id[MAX_ID_SIZE], char fullName[MAX_FULL_NAME_SIZE], int age);

PersonRecord* printPersonRecord(PersonRecord* record);

DataBase* printEntireDB(DataBase* db);

void _displayDBElement(TrieNode* node, int level);

void deleteDataBase(DataBase* db);

#endif