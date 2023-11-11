#include <locale.h>
#include <stdio.h>

#include "db.h"
#include "fileops.h"
#include "trie.h"

int main() {
    DataBase* myDb = createDataBase();

    PersonRecord newPerson = createPersonRecord("abc", "Jhon", 25);
    insertNewRecord(myDb, newPerson);

    PersonRecord newPerson2 = createPersonRecord("cbcaaa", "Jhon", 25);
    insertNewRecord(myDb, newPerson2);

    printEntireDB(myDb);

    deleteDataBase(myDb);
    return 0;
}
