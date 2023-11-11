#include "db.h"
#include "dbui.h"

int main() {
    DataBase* myDb = createDataBase("banco.txt");

    loadRecordsFromDisk(myDb);

    while (processUi(myDb)) {
    }

    deleteDataBase(myDb);
    return 0;
}
