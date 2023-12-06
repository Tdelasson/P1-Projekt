#include <stdio.h>
#include <stdlib.h>
#include "..\main\main.h"
#include "string.h"
#include <ctype.h>

// Function to retrieve resident information from a file and display it
resident_record get_resident_record(void) {
    resident_record resident;

    // Open the resident record file in read mode
    FILE *resident_record_file = fopen("resident_record.txt", "r");

    // Check if the file was successfully opened
    if (resident_record_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    int record_found = 0;

    while(record_found == 0){
        // Loop through the file as long as there are records to read;
        resident.id_key = scan_resident_number();
        record_found = scan_resident_database(resident_record_file,&resident,resident.id_key);
    }

    // Return the resident information
    fclose(resident_record_file);
    return resident;
}

int scan_resident_number(){
    //Prompts and scans the resident id key
    int id_key;
    printf("Enter Resident ID: \n-> ");
    scanf("%d", &id_key);
    return id_key;
}

int scan_resident_database(FILE *resident_record_file,resident_record* resident,int id_key){
    rewind(resident_record_file); // Move the file pointer to the beginning of the file

    while (fscanf(resident_record_file, "%d, %[^,], %[^,], %lf, %d, %[^,], %d, %[^,], %d",
                  &resident->id_key, resident->first_name, resident->surname,
                  &resident->apartment_number, &resident->age,
                  resident->gender, &resident->weight,
                  resident->weight_unit, &resident->social_security_number) == 9) {
        // Check if the ID key matches
        if (resident->id_key == id_key) {
            return 1;
        }

    }
    printf("ERROR! ID Key not found\n");
    return 0;

}

void print_resident_record(resident_record resident) {
    printf("Name: %s %s\n"
           "Apartment number: %.2lf\n"
           "Age: %d\n"
           "Gender: %s\n"
           "Weight: %d %s\n"
           "Social Security Number: %d\n\n",
           resident.first_name, resident.surname,
           resident.apartment_number, resident.age, resident.gender,
           resident.weight, resident.weight_unit, resident.social_security_number);

}

int get_resident_record_medicine(resident_medications medications[], int resident_id_key) {
    FILE *file = fopen("resident_record_medicine.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return -1;
    }

    int patientId, medicalId;
    int medications_count = 0;

    while (fscanf(file, "%d,%d,", &medicalId, &patientId) == 2) {
        if (patientId == resident_id_key) {
            while (medications_count < MAX_MEDICATIONS &&
                   fscanf(file, "%d, %lf, %[^,],%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,",
                          &medications[medications_count].medication,
                          &medications[medications_count].total_weekly_dose,
                          medications[medications_count].medication_unit,
                          &medications[medications_count].weekdays[0],
                          &medications[medications_count].weekdays[1],
                          &medications[medications_count].weekdays[2],
                          &medications[medications_count].weekdays[3],
                          &medications[medications_count].weekdays[4],
                          &medications[medications_count].weekdays[5],
                          &medications[medications_count].weekdays[6],
                          &medications[medications_count].morning_dose,
                          &medications[medications_count].afternoon_dose,
                          &medications[medications_count].evening_dose) == 13) {

                medications_count++;
            }

            // Break out of the loop once medications for the target patient are read
            break;
        } else {
            // Skip the rest of the line for medications of other residents
            while (fgetc(file) != '\n' && !feof(file)) {
                // Keep reading characters until the end of the line
            }
        }
    }

    fclose(file);

    // Return the number of medications read
    return medications_count;
}

void print_resident_medication(resident_medications medications[], int medications_count) {
    for (int i = 0; i < medications_count; i++) {
        printf("Medication: %d\n", medications[i].medication);
        printf("Unit: %s\n", medications[i].medication_unit);
        printf("Weekly dose: %.2lf\n", medications[i].total_weekly_dose);
        printf("Weekdays to dose: ");
        for (int j = 0; j < 7; j++) {
            printf("%d ", medications[i].weekdays[j]);
        }
        printf("\n");
        printf("Morning dose: %.2lf\n", medications[i].morning_dose);
        printf("Afternoon dose: %.2lf\n", medications[i].afternoon_dose);
        printf("Evening dose: %.2lf\n", medications[i].evening_dose);
        printf("\n");
    }
}


void get_resident_medication_conflict(medicine_database medicine_details[], int number_of_medications) {
    FILE *resident_record_conflict_file = fopen("medicine_conflicts.txt", "r");
    // Check if the file was successfully opened
    if (resident_record_conflict_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    // Create an array to store resident records
    medicine_conflicts conflicts[MAX_CONFLICTING_MEDICATIONS];
    int id_key = 0;
    char resident_medication[MAX_MEDICATION_NAME_LGT];
    int conflict_count = 0;
    int conflicting_meds = 0;

    // Loop through the array of medication
    for (int i = 0; i < number_of_medications; i++) {
        // Move the file pointer to the beginning
        rewind(resident_record_conflict_file);


        // Iterate through the file to find conflicts for the current medication
        while (fscanf(resident_record_conflict_file, "%d, %[^,],", &id_key, resident_medication) == 2) {
            printf("Resident medication: %s\n", resident_medication);

            //printf("REACHED\n");
            // Check if the ID key matches
            if (strcmp(resident_medication,medicine_details[i].name) == 0) {
                printf("REACHED\n");
                while (fscanf(resident_record_conflict_file, " %s,",
                              conflicts[i].conflicting_medication[conflict_count]) == 1) {

                    if (conflicts[i].conflicting_medication[conflict_count]) {
                        conflicting_meds++;
                    }
                    conflict_count++;
                }

            }

            // Process the conflicts for each medication



        }
        printf("\nConflicting medication for medication: %s\n", medicine_details[i].name);
    }

    fclose(resident_record_conflict_file);
}


void get_medication_details(medicine_database medicine_details[],
                            resident_medications medications[], int number_of_medications) {
    FILE *medicine_database_file = fopen("medicine_database.txt", "r");

    // Check if the file was successfully opened
    if (medicine_database_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }



    // Loop through resident medications
    for (int i = 0; i < number_of_medications; i++) {
        rewind(medicine_database_file);  // Move the file pointer to the beginning of the file

        // Reset ID_Key found flag for each resident medication
        int id_key_found = 0;

        // Loop through the medicine database
        while (fscanf(medicine_database_file, "%d,%[^,],%[^,],%lf,%s",
                      &medicine_details[i].id_key, medicine_details[i].name,
                      medicine_details[i].type, &medicine_details[i].strength,
                      medicine_details[i].unit_of_strength) == 5) {
            if (medicine_details[i].id_key == medications[i].medication) {
                // ID_Key found, set the flag
                id_key_found = 1;
                break;  // Break out of the loop after finding a match
            }
        }

        // Check if the ID_Key is not found for the current resident medication
        if (!id_key_found) {
            printf("ID_Key %d not found in the database.\n", medications[i].medication);
            fclose(medicine_database_file);  // Close the file before exiting
            exit(EXIT_FAILURE);
        }

    }

    fclose(medicine_database_file);
}


void print_medicine_info(medicine_database medicine_details[], int number_of_medications) {
    for (int i = 0; i < number_of_medications; i++) {
        printf("Medicine ID: %d\n"
               "Medicine name: %s\n"
               "Medicine type: %s\n"
               "Medicine strength: %.2lf\n"
               "Medicine unit of strength: %s\n\n",
               medicine_details[i].id_key, medicine_details[i].name, medicine_details[i].type,
               medicine_details[i].strength, medicine_details[i].unit_of_strength);
    }
}





medicine_database* get_resident_medicine_data(medicine_database residents[]);

medicine_conflicts* get_medicine_conflicts(medicine_conflicts residents[]);