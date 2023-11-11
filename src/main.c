#include <locale.h>
#include <stdio.h>

#include "db.h"
#include "fileops.h"
#include "trie.h"

int main() {
    DataBase* myDb = createDataBase();

    insertNewRecord(myDb, createPersonRecord("abc", "Jhon", 25));

    insertNewRecord(myDb, createPersonRecord("cbcaaa", "Jhon", 25));
    insertNewRecord(myDb, createPersonRecord("abcaaa", "Jhon", 25));
    insertNewRecord(myDb, createPersonRecord("abc", "Jhon", 25));
    insertNewRecord(myDb, createPersonRecord("ab", "Jhon", 25));

    printEntireDB(myDb);

    deleteDataBase(myDb);
    return 0;
}
