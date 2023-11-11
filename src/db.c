#include "db.h"

DataBase* createDataBase(char staticPath[PATH_STRING_SIZE]) {
    DataBase* db = (DataBase*)malloc(sizeof(DataBase));
    if (db == NULL) {
        fprintf(stderr, "Erro durante alocação de memoria do banco de dados\n");
        exit(EXIT_FAILURE);
    }
    db->trie = newTrie();
    strncpy(db->staticPath, staticPath, PATH_STRING_SIZE - 1);
    return db;
}

PersonRecord* insertNewRecord(DataBase* db, PersonRecord newRecord) {
    if (findRecordById(db, newRecord.id)) {
        return NULL;
    }
    TrieNode* node = insertWordIntoTrie(db->trie, newRecord.id);
    PersonRecord* recordPtr = (PersonRecord*)malloc(sizeof(PersonRecord));

    if (recordPtr == NULL) {
        fprintf(stderr, "Erro durante alocação de memoria ao novo record\n");
        exit(EXIT_FAILURE);
    }

    strncpy(recordPtr->id, newRecord.id, MAX_ID_SIZE - 1);
    strncpy(recordPtr->fullName, newRecord.fullName, MAX_FULL_NAME_SIZE - 1);
    recordPtr->age = newRecord.age;
    node->record = recordPtr;

    return node->record;
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
    strncpy(newRecord.id, id, MAX_ID_SIZE - 1);
    strncpy(newRecord.fullName, fullName, MAX_FULL_NAME_SIZE - 1);
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

ParseResult parseData(char data[MAX_DATA_SIZE], size_t dataSize) {
    ParseResult result;
    result.error = 1;

    char id[MAX_ID_SIZE + 1];
    char name[MAX_FULL_NAME_SIZE + 1];
    char ageString[MAX_AGE_CHARS_SIZE + 1];
    int age;

    size_t idSize = 0;
    for (size_t i = 0; data[i] != ' ' || i >= MAX_ID_SIZE; i++) {
        if (i >= MAX_ID_SIZE) return result;
        id[idSize] = data[i];
        idSize++;
    }
    if (idSize == 0)
        return result;

    id[idSize] = '\0';

    size_t ageSize = 0;
    for (size_t i = dataSize - 1; data[i] != ' '; i--) {
        if (i < 0) return result;
        if (ageString[i] == '\n') continue;
        ageString[ageSize] = data[i];
        ageSize++;
    }
    if (ageSize == 0)
        return result;

    ageString[ageSize] = '\0';
    _invertString(ageString);
    age = atoi(ageString);

    size_t nameSize = 0;
    for (size_t i = idSize + 1; i < dataSize - ageSize - 1; i++) {
        if (i >= MAX_FULL_NAME_SIZE - idSize + 1) return result;
        if (name[i] == '\n') continue;

        name[nameSize] = data[i];
        nameSize++;
    }
    if (nameSize == 0)
        return result;

    name[nameSize] = '\0';

    result.error = 0;
    result.result = createPersonRecord(id, name, age);
    return result;
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

        ParseResult parsedRecord = parseData(buffer, bufferDataSize);
        if (parsedRecord.error) continue;
        PersonRecord newRecord = parsedRecord.result;
        insertNewRecord(db, createPersonRecord(newRecord.id, newRecord.fullName, newRecord.age));
    }

    fclose(fp);
    return true;
}

bool saveRecordsToDisk(DataBase* db) {
    FILE* fp = fopen(db->staticPath, "w");

    if (fp == NULL) {
        fprintf(stderr, "Error: Unable to open the file at path: %s\n", db->staticPath);
        return false;
    }

    unsigned int recordCount = countNumOfRecords(db);

    fprintf(fp, "%u\n", recordCount);

    _printToDiskRecursive(db->trie, 0, fp);

    fseek(fp, -2, SEEK_END);
    ftruncate(fileno(fp), ftell(fp));  // Remove the newline character

    fclose(fp);
    return true;
}

void _printToDiskRecursive(TrieNode* node, int level, FILE* fp) {
    if (node->record != NULL) {
        PersonRecord* record = (PersonRecord*)(node->record);
        fprintf(fp, "%s %s %i\n", record->id, record->fullName, record->age);
    }

    for (int i = 0; i < N_OF_CHILDREN; i++) {
        if (node->children[i]) {
            _printToDiskRecursive(node->children[i], level + 1, fp);
        }
    }
}

unsigned int countNumOfRecords(DataBase* db) {
    return countNumOfElements(db->trie);
}