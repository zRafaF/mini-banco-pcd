#include "db.h"

DataBase* createDataBase() {
    DataBase* db = (DataBase*)malloc(sizeof(DataBase));
    if (db == NULL) {
        fprintf(stderr, "Erro durante alocação de memoria do banco de dados\n");
        exit(EXIT_FAILURE);
    }
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

    return db;
}

bool removeRecordById(DataBase* db, char id[MAX_ID_SIZE]) {
    return removeWordOfTrie(db->trie, id);
}

PersonRecord createPersonRecord(char id[MAX_ID_SIZE], char fullName[MAX_FULL_NAME_SIZE], int age) {
    PersonRecord newRecord;
    strcpy(newRecord.id, id);
    strcpy(newRecord.fullName, fullName);
    newRecord.age = age;

    return newRecord;
}

PersonRecord* printPersonRecord(PersonRecord* record) {
    printf("(%s|%s|%i)\n", record->id, record->fullName, record->age);
    return record;
}

DataBase* printEntireDB(DataBase* db) {
    _displayDBElement(db->trie, 0);

    return db;
}

void _displayDBElement(TrieNode* node, int level) {
    if (node->record != NULL) {
        PersonRecord* record = (PersonRecord*)(node->record);
        printPersonRecord(record);
    }

    for (int i = 0; i < N_OF_CHILDREN; i++) {
        if (node->children[i]) {
            _displayDBElement(node->children[i], level + 1);
        }
    }
}

void deleteDataBase(DataBase* db) {
    deleteTrie(db->trie);
    free(db);
}
