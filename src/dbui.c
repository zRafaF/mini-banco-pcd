#include "dbui.h"

bool processUi(DataBase* db) {
    char userInput[MAX_INPUT_SIZE];

    if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
        fprintf(stderr, "Error reading user input\n");
        return false;
    }

    size_t len = strlen(userInput);
    if (len > 0 && userInput[len - 1] == '\n') {
        userInput[len - 1] = '\0';
    }

#ifndef _WIN32
    strcat(userInput, "\n");
#endif

    printf("inp: %s\n", userInput);

    return _processUserInput(db, userInput);
}

bool _processUserInput(DataBase* db, char userInput[MAX_INPUT_SIZE]) {
    char command = 'F';
    char data[MAX_INPUT_SIZE];

    size_t userInputSize = 0;
    size_t dataSize = 0;

    for (userInputSize = 0; userInput[userInputSize] != '\0'; userInputSize++) {
        if (userInputSize == 0) {
            command = userInput[0];
            continue;
        }
        if (userInputSize == 1) {
            continue;
        }
        data[dataSize] = userInput[userInputSize];
        dataSize++;
    }
    data[dataSize] = '\0';

    switch (command) {
        case '?':
            _searchDBForId(db, data, dataSize);
            break;
        case '+':
            _addToDb(db, data, dataSize);
            break;
        case '-':
            _removeFromDb(db, data, dataSize);
            break;
        case 'P':
            _printDb(db);
            break;
        case 'S':
            _saveDb(db);
            break;
        case 'F':
            return false;
            break;

        default:
            return false;
            break;
    }

    return true;
}

void _searchDBForId(DataBase* db, char data[MAX_DATA_SIZE], size_t dataSize) {
    if (dataSize <= MAX_ID_SIZE) {
        PersonRecord* record = findRecordById(db, data);
        if (record) {
            printPersonRecord(record);
            return;
        }
    }

    printf("ID %s nao encontrado.\n", data);
}

void _addToDb(DataBase* db, char data[MAX_DATA_SIZE], size_t dataSize) {
    ParseResult parsedRecord = parseData(data, dataSize);
    if (parsedRecord.error) {
        fprintf(stderr, "Erro durante o parsing\n");
        return;
    };
    PersonRecord* insertedRecord = insertNewRecord(db, parsedRecord.result);
    if (insertedRecord == NULL) {
        fprintf(stderr, "Erro: ID repetido\n");
        return;
    }
    printf("Inserido ");
    printPersonRecord(insertedRecord);
}

void _removeFromDb(DataBase* db, char data[MAX_DATA_SIZE], size_t dataSize) {
    if (dataSize <= MAX_ID_SIZE) {
        PersonRecord* record = findRecordById(db, data);
        if (record) {
            printf("Removido ");
            printPersonRecord(record);
            removeRecordById(db, record->id);
            return;
        }
    }

    printf("ID %s nao encontrado.\n", data);
}

void _printDb(DataBase* db) {
    printEntireDB(db);
}

void _saveDb(DataBase* db) {
    if (saveRecordsToDisk(db)) {
        printf("%s salvo\n", db->staticPath);
    }
}