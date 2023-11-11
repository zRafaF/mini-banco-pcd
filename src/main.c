#include "db.h"
#include "dbui.h"

void runTest(DataBase* db) {
    _processUserInput(db, "P");
    _processUserInput(db, "? afd");
    _processUserInput(db, "? afdg");
    _processUserInput(db, "? rusbe");
    _processUserInput(db, "+ rusbe Michael Joseph Jackson 50");
    _processUserInput(db, "? rusbe");
    _processUserInput(db, "- afdg");
    _processUserInput(db, "? afdg");
    _processUserInput(db, "+ baby Justin Bieber 24");
    _processUserInput(db, "+ bab Alok 32");
    _processUserInput(db, "+ mike rafael 32");
    _processUserInput(db, "? baby");
    _processUserInput(db, "- dwiop");
    _processUserInput(db, "P");
    _processUserInput(db, "S");
    _processUserInput(db, "F");
}

int main() {
    DataBase* myDb = createDataBase("banco.txt");

    loadRecordsFromDisk(myDb);

    // runTest(myDb);

    while (processUi(myDb)) {
    }

    deleteDataBase(myDb);
    return 0;
}
