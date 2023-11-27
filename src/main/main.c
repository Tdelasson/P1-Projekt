#include "main.h"

int main (void){
    get_patient_journal();
    int number_of_patients_read = get_patient_journal();
    return number_of_patients_read;
}