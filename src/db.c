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

PersonRecord createPersonRecord(char id[MAX_ID_SIZE], char fullName[MAX_FULL_NAME_SIZE], int age) {
    PersonRecord newRecord;
    strcpy(newRecord.id, id);
    strcpy(newRecord.fullName, fullName);
    newRecord.age = age;

    return newRecord;
}

void printEntireDB(DataBase* db) {
    printf("Numero de elementos na TRIE: %u\nImprimindo a trie:\n", countNumOfElements(db->trie));
    printTrie(db->trie);
}

void deleteDataBase(DataBase* db) {
    deleteNode(db->trie);
    free(db);
}
