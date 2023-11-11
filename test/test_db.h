#ifndef TEST_DB_H
#define TEST_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unity.h>

#include "../include/db.h"
#include "../include/dbui.h"
#include "../include/globals.h"

char testDbPathGlobal[PATH_STRING_SIZE];
char* readTextFileBuffer = 0;

char* _readTextFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    long length;

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    readTextFileBuffer = malloc(length + 1);
    if (readTextFileBuffer) {
        int cnt = fread(readTextFileBuffer, sizeof(char), length, file);

        readTextFileBuffer[cnt] = '\0';
    }
    fclose(file);
    return readTextFileBuffer;
}

void test_db__invertString(void) {
    char stringTest[MAX_INPUT_SIZE];

    strncpy(stringTest, "abcde", MAX_INPUT_SIZE - 1);
    _invertString(stringTest);
    TEST_ASSERT_EQUAL_STRING("edcba", stringTest);

    strncpy(stringTest, "1234567890", MAX_INPUT_SIZE - 1);
    _invertString(stringTest);
    TEST_ASSERT_EQUAL_STRING("0987654321", stringTest);

    strncpy(stringTest, "_123", MAX_INPUT_SIZE - 1);
    _invertString(stringTest);
    TEST_ASSERT_EQUAL_STRING("321_", stringTest);
}

void test_db_parseData(void) {
    char stringTest[MAX_INPUT_SIZE];
    ParseResult parseResult;

    strncpy(stringTest, "abc João Miguel 22\n", MAX_INPUT_SIZE - 1);
    parseResult = parseData(stringTest, strlen(stringTest));
    TEST_ASSERT_FALSE(parseResult.error);
    TEST_ASSERT_EQUAL_STRING("abc", parseResult.result.id);
    TEST_ASSERT_EQUAL_STRING("João Miguel", parseResult.result.fullName);
    TEST_ASSERT_EQUAL_INT(22, parseResult.result.age);

    strncpy(stringTest, " rav Lima Nicole da silva junior 1\n", MAX_INPUT_SIZE - 1);
    parseResult = parseData(stringTest, strlen(stringTest));
    TEST_ASSERT_TRUE(parseResult.error);

    strncpy(stringTest, " ", MAX_INPUT_SIZE - 1);
    parseResult = parseData(stringTest, strlen(stringTest));
    TEST_ASSERT_TRUE(parseResult.error);

    strncpy(stringTest, "abcde", MAX_INPUT_SIZE - 1);
    parseResult = parseData(stringTest, strlen(stringTest));
    TEST_ASSERT_TRUE(parseResult.error);

    strncpy(stringTest, "u J o ã o M i g u e l 1\n", MAX_INPUT_SIZE - 1);
    parseResult = parseData(stringTest, strlen(stringTest));
    TEST_ASSERT_FALSE(parseResult.error);
    TEST_ASSERT_EQUAL_STRING("u", parseResult.result.id);
    TEST_ASSERT_EQUAL_STRING("J o ã o M i g u e l", parseResult.result.fullName);
    TEST_ASSERT_EQUAL_INT(1, parseResult.result.age);
}

void test_db_e2e(void) {
    for (int i = 0; i < 20; i++) {
        DataBase* myDb = createDataBase(testDbPathGlobal);

        insertNewRecord(myDb, createPersonRecord("abc", "Miguel Arnaldo", 22));
        saveRecordsToDisk(myDb);
        TEST_ASSERT_EQUAL_STRING("1\nabc Miguel Arnaldo 22\n", _readTextFile(testDbPathGlobal));

        insertNewRecord(myDb, createPersonRecord("ab", "Jerivaldo Nupo", 99));
        saveRecordsToDisk(myDb);
        TEST_ASSERT_EQUAL_STRING("2\nab Jerivaldo Nupo 99\nabc Miguel Arnaldo 22\n", _readTextFile(testDbPathGlobal));

        removeRecordById(myDb, "ab");
        saveRecordsToDisk(myDb);
        TEST_ASSERT_EQUAL_STRING("1\nabc Miguel Arnaldo 22\n", _readTextFile(testDbPathGlobal));

        TEST_ASSERT_NULL(insertNewRecord(myDb, createPersonRecord("abc", "Jurema Lima", 99)));

        PersonRecord* miguelRecord = findRecordById(myDb, "abc");
        TEST_ASSERT_EQUAL_STRING("Miguel Arnaldo", miguelRecord->fullName);

        TEST_ASSERT_NULL(findRecordById(myDb, "munydi"));

        deleteDataBase(myDb);
        remove(testDbPathGlobal);
    }
}

void test_db_countNumOfRecords(void) {
    DataBase* myDb = createDataBase(testDbPathGlobal);

    insertNewRecord(myDb, createPersonRecord("abc", "Miguel Arnaldo", 2));
    insertNewRecord(myDb, createPersonRecord("ab", "Ramon lima", 4));
    insertNewRecord(myDb, createPersonRecord("abd", "Ramires", 99));
    insertNewRecord(myDb, createPersonRecord("dwr", "Liopos asd", 0));
    TEST_ASSERT_EQUAL_INT(4, countNumOfRecords(myDb));

    insertNewRecord(myDb, createPersonRecord("ab", "Corion", 8));
    TEST_ASSERT_EQUAL_INT(4, countNumOfRecords(myDb));

    removeRecordById(myDb, "ab");
    TEST_ASSERT_EQUAL_INT(3, countNumOfRecords(myDb));

    deleteDataBase(myDb);
}

void test_dbui__processUserInput(void) {
    DataBase* myDb = createDataBase(testDbPathGlobal);

    TEST_ASSERT_FALSE(_processUserInput(myDb, " "));
    TEST_ASSERT_FALSE(_processUserInput(myDb, "F"));
    TEST_ASSERT_FALSE(_processUserInput(myDb, "2d1"));
    TEST_ASSERT_FALSE(_processUserInput(myDb, "2d1 a sdasd sad sad d a sd asd a"));

    _processUserInput(myDb, "+ arn Arnaldo Lima 34\n");
    _processUserInput(myDb, "S");
    TEST_ASSERT_EQUAL_STRING("1\narn Arnaldo Lima 34\n", _readTextFile(testDbPathGlobal));

    _processUserInput(myDb, "+ arn asd a sdas das dasd as das da 34\n");
    _processUserInput(myDb, "S");
    TEST_ASSERT_EQUAL_STRING("1\narn Arnaldo Lima 34\n", _readTextFile(testDbPathGlobal));

    _processUserInput(myDb, "+ asd Ajlgs lksdm 0\n");
    _processUserInput(myDb, "+ dhw ASd ashish 1\n");
    _processUserInput(myDb, "+ asbtd asdasd Liasdama 99\n");
    _processUserInput(myDb, "+ asbtwe asdçasdão ajnsd 33\n");
    _processUserInput(myDb, "S");
    TEST_ASSERT_EQUAL_STRING("5\narn Arnaldo Lima 34\nasbtd asdasd Liasdama 99\nasbtwe asdçasdão ajnsd 33\nasd Ajlgs lksdm 0\ndhw ASd ashish 1\n", _readTextFile(testDbPathGlobal));

    _processUserInput(myDb, "- asd");
    _processUserInput(myDb, "- arn");
    _processUserInput(myDb, "- asbtd");
    _processUserInput(myDb, "- asbtwe");
    _processUserInput(myDb, "S");
    TEST_ASSERT_EQUAL_STRING("1\ndhw ASd ashish 1\n", _readTextFile(testDbPathGlobal));

    deleteDataBase(myDb);
}

#endif