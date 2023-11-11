#include <locale.h>
#include <stdio.h>

#include "db.h"
#include "dbui.h"
#include "fileops.h"
#include "trie.h"

int main() {
    DataBase* myDb = createDataBase();

    while (processUi(myDb)) {
    }

    deleteDataBase(myDb);
    return 0;
}
