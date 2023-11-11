#include "db.h"

DataBase* createDataBase(char staticPath[PATH_STRING_SIZE]) {
    DataBase* db = (DataBase*)malloc(sizeof(DataBase));
    if (db == NULL) {
        fprintf(stderr, "Erro durante alocação de memoria do banco de dados\n");
        exit(EXIT_FAILURE);
    }
    db->trie = newTrie();
    strcpy(db->staticPath, staticPath);

    return db;
}

DataBase* insertNewRecord(DataBase* db, PersonRecord newRecord) {
    if (findRecordById(db, newRecord.id)) {
        return db;
    }
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

PersonRecord* findRecordById(DataBase* db, char id[MAX_ID_SIZE]) {
    TrieNode* recordNode = findWordInTrie(db->trie, id);
    if (recordNode) {
        return (PersonRecord*)recordNode->record;
    }
    return NULL;
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

PersonRecord parseData(char data[MAX_DATA_SIZE], size_t dataSize) {
    char id[MAX_ID_SIZE];
    char name[MAX_FULL_NAME_SIZE];
    int age;

    size_t idSize = 0;
    for (size_t i = 0; data[i] != ' '; i++) {
        id[idSize] = data[i];
        idSize++;
    }
    id[idSize] = '\0';

    char ageString[MAX_AGE_CHARS_SIZE];
    size_t ageSize = 0;
    for (size_t i = dataSize - 1; data[i] != ' '; i--) {
        ageString[ageSize] = data[i];
        ageSize++;
    }
    ageString[ageSize] = '\0';
    _invertString(ageString);
    age = atoi(ageString);

    size_t nameSize = 0;
    for (size_t i = idSize + 1; i < dataSize - ageSize - 1; i++) {
        name[nameSize] = data[i];
        nameSize++;
    }
    name[nameSize] = '\0';

    return createPersonRecord(id, name, age);
}

void _invertString(char* str) {
    int length = strlen(str);
    int i, j;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

bool loadRecordsFromDisk(DataBase* db) {
    FILE* fp = fopen(db->staticPath, "r");

    if (fp == NULL) {
        fprintf(stderr, "Error: Não foi possível abrir o arquivo no caminho: %s\n", db->staticPath);
        return false;
    }

    char buffer[MAX_DATA_SIZE];
    bool doOnce = true;
    while (fgets(buffer, MAX_DATA_SIZE, fp)) {
        if (doOnce) {
            doOnce = false;
            continue;
        }  // skips the first line
        const size_t bufferDataSize = strlen(buffer);

        PersonRecord newRecord = parseData(buffer, bufferDataSize);
        insertNewRecord(db, createPersonRecord(newRecord.id, newRecord.fullName, newRecord.age));
    }

    // close the file
    fclose(fp);
    return true;
}

bool saveRecordsToDisk(DataBase* db) {
    return true;
}
