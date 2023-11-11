#include <locale.h>
#include <stdio.h>

#include "db.h"
#include "fileops.h"
#include "trie.h"

int main() {
    for (size_t i = 0; i < 800; i++) {
        printf("%i ", i);

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
