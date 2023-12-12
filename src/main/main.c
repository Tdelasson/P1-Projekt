#include <string.h>
#include "main.h"
#include "../pillbox/pillbox.h"

int main(void) {
    verify_staff();

    while (1) {

        //infusion(resident);

        //get patient data from resident_record
        resident_record resident;
        resident = get_resident_record();
        print_resident_record(resident);

        //get patient medication data from resident_record_medicine
        resident_medications medications[MAX_MEDICATIONS];
        int number_of_medications = get_resident_record_medicine(medications, resident.id_key);

        //get medication details from medicine_database
        medicine_database medicine_details[MAX_MEDICATIONS];
        get_medication_details(medicine_details, medications, number_of_medications);
        print_medicine_detail_info(medicine_details, number_of_medications);


        //check for medication conflicts
        char conflict;
        while (get_resident_medication_conflict(medicine_details, number_of_medications) == true
               && conflict != 'y') {
            fprintf(stderr, "Medication conflict detected\n");
            printf("Would you like to continue? (y/n)\n");
            scanf("%c", &conflict);

            if (conflict == 'n') {
                return 0;
            }
        }

        //weekdays(medications, number_of_medications);

        //print medication dispense information

        dispensing(medications, medicine_details, number_of_medications);

        /*if (strcmp(medicine_details[i].type, "Liquid") == 0) {
            // TODO implement Liquids
        } else if (strcmp(medicine_details[i].type, "pills") == 0) {
            // TODO implement pillbox
        }*/


        //check for new resident
        if (program_restart() == 'y') {

        } else {
            break;
        }

    }
    return 0;
}
