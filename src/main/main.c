#include "main.h"

int main(void) {
    resident_record resident;
    resident.id_key = scan_resident_number();
    resident = get_resident_record(resident.id_key);
    print_resident_record(resident);

    resident_medications medications[MAX_MEDICATIONS];

    get_resident_record_medicine(medications, resident.id_key);
    print_resident_medication(medications);

    // Print the medication for Adam
    //printf("Medication for Adam: %s\n", medications->medication[0]);

    //free(medications);

    return 0;
}