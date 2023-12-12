#include "../infusion/infusion.h"

int main(void) {

    verify_staff();

    //get patient data from resident_record
    resident_record resident;
    resident = get_resident_record();
    print_resident_record(resident);

    resident_medications medications[MAX_MEDICATIONS];
    int medications_count = get_resident_record_medicine(medications, resident.id_key);

    // TODO: Erstat med pillbox funktioner
    //print_resident_medication(medications, medications_count);

    medicine_database medicine_details[MAX_MEDICATIONS];
    get_medication_details(medicine_details, medications, medications_count);

    // TODO: Erstat med pillbox funktioner
    print_medicine_detail_info(medicine_details, medications_count);


    infusion(resident);

    program_restart();

    return 0;
}