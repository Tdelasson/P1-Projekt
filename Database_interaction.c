#include <stdio.h>
#include "sqlite3.h"

int main() {
    sqlite3* db;
    int rc = 0;
    rc = sqlite3_open("database.db",&db);

    if(rc != SQLITE_OK){
        printf("File didnt open");
    }
    else{
        printf("File opened");
    }
    return 2;
}
