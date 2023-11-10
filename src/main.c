#include <locale.h>
#include <stdio.h>

#include "db.h"
#include "fileops.h"
#include "trie.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("Number: %i, Letter: %c\n", charToTrieIdx('b'), trieIdxToChar(1));
    printf("Number: %i, Letter: %c\n", charToTrieIdx('c'), trieIdxToChar(2));
    printf("Number: %i, Letter: %c\n", charToTrieIdx('z'), trieIdxToChar(25));
    printf("Number: %i, Letter: %c\n", charToTrieIdx('a'), trieIdxToChar(0));

    DataBase* myDb = createDataBase();

    PersonRecord newPerson = createPersonRecord("123", "Jhon", 25);
    insertNewRecord(myDb, newPerson);

    printEntireDB(myDb);

    deleteDataBase(myDb);
    return 0;
}
