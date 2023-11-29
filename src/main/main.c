#include "main.h"


int main(void) {
    // Get the resident's personal information and print it
    resident_record resident;
    resident = get_resident_record();
    print_resident_record(resident);


    // Get the resident's medication information and print it
    resident_medications medications[MAX_MEDICATIONS];
    int number_of_medications = get_resident_record_medicine(medications, resident.id_key);

    if (number_of_medications > 0) {
        printf("Medications for Resident ID %d:\n", resident.id_key);
        print_resident_medication(medications, number_of_medications);
    } else {
        printf("No medications found for Resident ID %d.\n", resident.id_key);
    }


 //(Program kan scanne patient id key og sammenligne det med et inputtet id key fra user)

    get_resident_medication_conflict(medications, number_of_medications);

    return 0;
