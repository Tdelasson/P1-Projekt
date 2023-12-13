#include "test_database.h"


int main(void){
    test_scan_resident_database();
    test_medicine_count();

}

void test_scan_resident_database(){
    // Open the resident record file in read mode
    FILE *resident_record_file = fopen("../database_textfiles/resident_record.txt", "r");

    // Check if the file was successfully opened
    if (resident_record_file == NULL) {
        fprintf(stderr, "Error opening resident record file.\n");
        exit(EXIT_FAILURE);
    }

    resident_record resident;
    unsigned long int social_security_number;


    //test_scan_resident_database should return 0 if the resident is not found
    social_security_number = 0000000000;
    assert((scan_resident_database(resident_record_file,&resident,social_security_number)==0));

    //test_scan_resident_database should return 1 if the resident is found
    social_security_number = 1111471111;
    assert((scan_resident_database(resident_record_file,&resident,social_security_number)==1));

    //test if correct data is scanned from database using resident 10049 as example
    social_security_number = 3004651987;
    scan_resident_database(resident_record_file,&resident,social_security_number);
    assert(strcmp(resident.first_name,"Noah") == 0);
    assert(strcmp(resident.surname,"Lewis") == 0);
    assert(resident.apartment_number == 1.11);
    assert(resident.age == 77);
    assert(strcmp(resident.sex,"Male") == 0);
    assert(resident.weight == 100);
    assert(resident.social_security_number == 3004651987);

}

void test_medicine_count(void){
    resident_medications medications[MAX_MEDICATIONS];
    assert((get_resident_record_medicine(medications,10001)) == 5);
    assert((get_resident_record_medicine(medications,10004)) == 4);
    assert((get_resident_record_medicine(medications,10049)) == 3);
}

