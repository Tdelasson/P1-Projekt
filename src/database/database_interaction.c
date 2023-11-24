#include <stdio.h>
#include <stdlib.h>
#include "database_interaction.h"


#define MAX_NAME_LGT 50
typedef struct {
    char fornavn[MAX_NAME_LGT];
    char efternavn[MAX_NAME_LGT];
}patient;

int read_all_patients_from_file(FILE* input_file, patient patients[], int max_patients);

int main(void)
{
    FILE* patient_journal_medicine= fopen("patient_journal_medicine.txt","r");
    if(patient_journal_medicine == NULL){
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    patient patients [50];
    int number_of_patients_read = read_all_patients_from_file(patient_journal_medicine, patients, 50);
    fclose(patient_journal_medicine);

    printf("%s %s",patients[1].fornavn,patients[1].efternavn);
    return number_of_patients_read;



    /*printf("Car read from file: \n");
    for (int i = 0; i < number_of_cars_read; i++) {
        print_car(input_cars[i]);
    }
    //car_t my_car = read_car_from_file(input_file);

    fclose(file);
    return 0;*/
}

int read_all_patients_from_file(FILE* input_file, patient patients[], int max_patients){
    int i;
    for (i = 0; i < max_patients; i++){
        patient new_patient;

        int result = fscanf(input_file," %[A-Za-z] %[A-Za-z],",
                            new_patient.fornavn,new_patient.efternavn);
        if (result != 6){
            break;
        }
        patients[i] = new_patient;
    }
    return i;
}
