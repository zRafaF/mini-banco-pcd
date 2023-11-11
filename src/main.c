#include <locale.h>
#include <stdio.h>

#include "db.h"
#include "fileops.h"
#include "trie.h"

void stressTestMemory(size_t numOfIterations) {
    for (size_t i = 0; i < numOfIterations; i++) {
        printf("%lu ", i);

        DataBase* myDb = createDataBase();

        insertNewRecord(myDb, createPersonRecord("abc", "Jhon", 25));

        insertNewRecord(myDb, createPersonRecord("cbcaaa", "Jhon", 25));
        insertNewRecord(myDb, createPersonRecord("abcaaa", "Jhon", 25));
        insertNewRecord(myDb, createPersonRecord("abc", "Jhon", 25));
        insertNewRecord(myDb, createPersonRecord("ab", "Jhon", 25));

        removeRecordById(myDb, "ab");
        removeRecordById(myDb, "cbcaaa");

        deleteDataBase(myDb);
    }
}

int main() {
    stressTestMemory(1);
    // DataBase* myDb = createDataBase();

    // insertNewRecord(myDb, createPersonRecord("abc", "Jhon", 25));

    // insertNewRecord(myDb, createPersonRecord("cbcaaa", "Jhon", 25));
    // insertNewRecord(myDb, createPersonRecord("abcaaa", "Jhon", 25));
    // insertNewRecord(myDb, createPersonRecord("abc", "Jhon", 25));
    // insertNewRecord(myDb, createPersonRecord("ab", "Jhon", 25));

    // printEntireDB(myDb);

    // removeRecordById(myDb, "ab");
    // removeRecordById(myDb, "cbcaaa");
    // printf("removido\n");
    // printEntireDB(myDb);

    // deleteDataBase(myDb);
    return 0;
}
