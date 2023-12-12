#include "../infusion/infusion.h"
#include <string.h>

int main(void) {

    verify_staff();

    //infusion(resident);

    //get patient data from resident_record
    resident_record resident;
    resident = get_resident_record();
    print_resident_record(resident);

    //get patient medication data from resident_record_medicine
    resident_medications medications[MAX_MEDICATIONS];
    int medications_count = get_resident_record_medicine(medications, resident.id_key);

    //get medication details from medicine_database
    medicine_database medicine_details[MAX_MEDICATIONS];
    get_medication_details(medicine_details, medications, medications_count);
    print_medicine_detail_info(medicine_details, medications_count);

    //check for medication conflicts
    if (get_resident_medication_conflict(medicine_details, medications_count) == true) {
        fprintf(stderr, "Medication conflict detected\n");
        return EXIT_FAILURE;
    }

    //print medication dispense information
    for (int i = 0; i < medications_count; i++) {

        if (strcmp(medicine_details[i].type, "Liquid") == 0) {
            // TODO implement Liquids
        }

        else if (strcmp(medicine_details[i].type, "pills") == 0) {
            // TODO implement pillbox
        }
    }

    //check for new resident
    program_restart();

    return 0;
}