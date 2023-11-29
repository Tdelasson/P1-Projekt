#include "main.h"

int main (void){
    patient_journal patients[50];
    get_patient_journal(patients);
    printf("\n\n%s",patients[0].first_name);
    //patient_journal * patient = get_patient_journal();
    //return number_of_patients_read;

}
