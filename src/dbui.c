#include "dbui.h"

bool processUi(DataBase* db) {
    char userInput[MAX_INPUT_SIZE];

    scanf("%[^\n]%*c", userInput);

    char command = 'e';
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
            return false;
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

    printf("ID %s nao encontrado.. ", data);
}

void _addToDb(DataBase* db, char data[MAX_DATA_SIZE], size_t dataSize) {
    PersonRecord newRecord = _parseData(data, dataSize);
    insertNewRecord(db, newRecord);
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

    printf("ID %s nao encontrado.. ", data);
}

void _printDb(DataBase* db) {
    printEntireDB(db);
}

PersonRecord _parseData(char data[MAX_DATA_SIZE], size_t dataSize) {
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
