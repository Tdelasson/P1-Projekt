#include "main.h"

int main(void) {
   /* staff_record staffs[10];
    get_staff_record(staffs);
    for (int i = 0; i < 10; i++) {
        print_staff_record(staffs[i]);
    }
*/
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

    medicine_database medicine_details[MAX_MEDICATIONS];
    get_medication_details(medicine_details,medications, number_of_medications);
    print_medicine_info(medicine_details, number_of_medications);

    get_resident_medication_conflict(medicine_details, number_of_medications);

    return 0;
}