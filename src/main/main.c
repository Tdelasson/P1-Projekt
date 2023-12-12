#include "../infusion/infusion.h"

int main(void) {

    verify_staff();

    //get patient data from resident_record
    resident_record resident;
    resident = get_resident_record();

    infusion(resident);

    program_restart();

    return 0;
}