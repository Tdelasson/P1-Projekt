#include <stdio.h>
#include "sqlite3.h"

int main() {
    sqlite3 *db;
    
    int rc = sqlite3_open("FMK.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table if not exists
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS FMK ("
                                 "SOCIAL_SECURITY_NUMBER INTEGER PRIMARY KEY,"
                                 "NAME_OF_PATIENT TEXT,"
                                 "MEDICINE_NAME TEXT,"
                                 "MEDICINE_STRENGTH INTEGER,"
                                 "MEDICATION_SCHEDULE TEXT);";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Insert data
    // You can customize the data to your needs
    const char *insertDataSQL = "INSERT INTO FMK (SOCIAL_SECURITY_NUMBER, NAME_OF_PATIENT, MEDICINE_NAME, MEDICINE_STRENGTH, MEDICATION_SCHEDULE) "
                                "VALUES (123456789, 'John Doe', 'Aspirin', 50, 'Morning, Noon, Evening, Sat, Sun');";

    rc = sqlite3_exec(db, insertDataSQL, 0, 0, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);
    return 0;
}
