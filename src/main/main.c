#include "main.h"

int main(void) {
    while(1) {
        verify_staff();

        // Get the resident's personal information and print it
        resident_record resident;
        resident = get_resident_record();
        print_resident_record(resident);

        // Get the resident's medication information and print it
        resident_medications medications[MAX_MEDICATIONS];
        int number_of_medications = get_resident_record_medicine(medications, resident.id_key);

        if (number_of_medications > 0) {
            printf("Medications for Resident: %s %s\n", resident.first_name, resident.surname);
            print_resident_medication(medications, number_of_medications);
        } else {
            printf("No medications found for Resident: %s %s\n", resident.first_name, resident.surname);
        }

        medicine_database medicine_details[MAX_MEDICATIONS];
        get_medication_details(medicine_details, medications, number_of_medications);
        print_medicine_detail_info(medicine_details, number_of_medications);

        get_resident_medication_conflict(medicine_details, number_of_medications);

        if (program_restart()== 'y'){
            printf("\n");
        }

        else {
            break;
        }

    }
    return 0;
}