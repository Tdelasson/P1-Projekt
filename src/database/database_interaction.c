#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <stdbool.h>
#include "database_interaction.h"

// Functions for staff verification. Checks if the staff id is in the database nursing_home_staff.txt
int scan_staff_number(void) {
    int staff_id;
    printf("Enter staff ID\n->");

    // Check if the input is a valid integer
    if (scanf("%d", &staff_id) != 1) {
        printf("Invalid input. Please enter a valid integer.\n");
        // Clear the input buffer to prevent an infinite loop
        while (getchar() != '\n');
        // You may also choose to return an error code or handle it as appropriate
        // For simplicity, I'll return a value of -1 to indicate an error
        return -1;
    }

    return staff_id;
}

int verify_staff(void) {
    FILE *nursing_home_file = fopen("nursing_home_staff.txt", "r");

    if (nursing_home_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    staff_record staff;
    bool validStaffFound = false;

    while (!validStaffFound) {
        int staff_id = -1;

        rewind(nursing_home_file);
        while (staff_id == -1) {
            staff_id = scan_staff_number();
        }

        for (int i = 0; fscanf(nursing_home_file, "%d, %49[^,], %49[^\n]\n",
                               &staff.id_key, staff.first_name, staff.surname) == 3; i++) {
            if (staff.id_key == staff_id) {
                printf("\nStaff checked in\n");
                printf("Name: %s %s\n\n", staff.first_name, staff.surname);
                validStaffFound = true;
                break;  // Exit the inner loop
            }
        }

        if (!validStaffFound) {
            printf("Invalid staff ID. Try again.\n\n");
        }
    }

    fclose(nursing_home_file);

    return 1;  // Indicate success
}


// Functions to retrieve resident information from resident_record.txt and display it
resident_record get_resident_record() {
    resident_record resident;

    // Open the resident record file in read mode
    FILE *resident_record_file = fopen("resident_record.txt", "r");

    // Check if the file was successfully opened
    if (resident_record_file == NULL) {
        fprintf(stderr, "Error opening resident record file.\n");
        exit(EXIT_FAILURE);
    }

    int record_found = 0;

    while(record_found == 0){
        // Loop through the file as long as there are records to read;
        resident.social_security_number = -1;
        while (resident.social_security_number == -1) {
            resident.social_security_number = scan_resident_number();
        }

        record_found = scan_resident_database(resident_record_file,&resident,resident.social_security_number);
    }

    // Return the resident information
    fclose(resident_record_file);
    return resident;
}

unsigned long int scan_resident_number(){
    unsigned long int social_security_number;
    printf("Enter resident CPR number\n->");

    // Check if the input is a valid integer
    if (scanf("%lu", &social_security_number) != 1) {
        printf("Invalid input. Please enter a valid integer.\n");
        // Clear the input buffer to prevent an infinite loop
        while (getchar() != '\n');
        // You may also choose to return an error code or handle it as appropriate
        // For simplicity, I'll return a value of -1 to indicate an error
        return -1;
    }

    return social_security_number;
}

int scan_resident_database(FILE *resident_record_file,resident_record* resident,unsigned long int social_security_number){
    rewind(resident_record_file); // Move the file pointer to the beginning of the file

    while (fscanf(resident_record_file, "%d, %[^,], %[^,], %lf, %d, %[^,], %d, %[^,], %lu",
                  &resident->id_key, resident->first_name, resident->surname,
                  &resident->apartment_number, &resident->age,
                  resident->sex, &resident->weight,
                  resident->weight_unit, &resident->social_security_number) == 9) {
        // Check if the ID key matches
        if (resident->social_security_number == social_security_number) {
            return 1;
        }

    }
    printf("ERROR! Resident not found\n");
    return 0;

}

void print_resident_record(resident_record resident) {
    printf("Name: %s %s\n"
           "Apartment number: %.2lf\n"
           "Age: %d\n"
           "Sex: %s\n"
           "Weight: %d %s\n"
           "Social Security Number: %lu\n\n",
           resident.first_name, resident.surname,
           resident.apartment_number, resident.age, resident.sex,
           resident.weight, resident.weight_unit, resident.social_security_number);

}


// Functions to retrieve resident medication information from a resident_record_medicine.txt and display it
int get_resident_record_medicine(resident_medications medications[], int resident_id_key) {
    FILE *file = fopen("../database_textfiles/resident_record_medicine.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening resident_record_medicine file.\n");
        return -1;
    }

    int patientId, medicalId;
    int medications_count = 0;

    while (fscanf(file, "%d,%d,", &medicalId, &patientId) == 2) {
        if (patientId == resident_id_key) {
            while (medications_count < MAX_MEDICATIONS &&
                   fscanf(file, " %d, %lf, %[^,],%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,",
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
                          &medications[medications_count].evening_dose) == 13)
            {

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
        printf("Weekly dose: %.2lf\n\n", medications[i].total_weekly_dose);

        printf("Weekdays to dose: \n");
        for (int j = 0; j < 7; j++) {
            if (medications[i].weekdays[j] == 1) {
                switch (j) {
                    case 0:
                        printf("Monday ");
                        break;
                    case 1:
                        printf("Tuesday ");
                        break;
                    case 2:
                        printf("Wednesday ");
                        break;
                    case 3:
                        printf("Thursday ");
                        break;
                    case 4:
                        printf("Friday ");
                        break;
                    case 5:
                        printf("Saturday ");
                        break;
                    case 6:
                        printf("Sunday ");
                        break;
                }

                // Print dose information for the day
                printf("\nMorning dose: %.2lf\n", medications[i].morning_dose);
                printf("Noon dose: %.2lf\n", medications[i].afternoon_dose);
                printf("Evening dose: %.2lf\n", medications[i].evening_dose);
                printf("\n\n");
            }
        }

    }
}

bool get_resident_medication_conflict(medicine_database medicine_details[], int number_of_medications) {
    FILE *resident_record_conflict_file = fopen("../database_textfiles/medicine_conflicts.txt", "r");

    if (resident_record_conflict_file == NULL) {
        fprintf(stderr, "Error opening resident_record_conflict file.\n");
        exit(EXIT_FAILURE);
    }

    medicine_conflicts conflicts[MAX_MEDICATIONS];
    unsigned long int social_security_number = 0;
    char resident_medication[MAX_MEDICATION_NAME_LGT];
    int conflict_count;
    char conflicting_medications[MAX_MEDICATIONS][MAX_CONFLICTING_MEDICATIONS][MAX_MEDICATION_NAME_LGT];
    int conflicting_medications_count;
    bool conflict_found = false;

    for (int i = 0; i < number_of_medications; i++) {
        rewind(resident_record_conflict_file);
        conflict_count = 0;

        while (fscanf(resident_record_conflict_file, "%lu , %[^,],", &social_security_number, resident_medication) == 2) {

            if (strcmp(resident_medication, medicine_details[i].name) == 0) {
                char line[MAX_CONFLICTING_MEDICATIONS * MAX_MEDICATION_NAME_LGT];
                if (fgets(line, sizeof(line), resident_record_conflict_file) != NULL) {
                    char *token = strtok(line, ",");
                    while (token != NULL) {
                        strcpy(conflicts[i].conflicting_medication[conflict_count], token);
                        conflict_count++;
                        token = strtok(NULL, ",");
                    }
                }
            } else {
                while (fgetc(resident_record_conflict_file) != '\n') {
                }
            }
        }


        // Save conflicting medications for later printing

        for (int l = 0; l < number_of_medications; l++) {
            conflicting_medications_count = 0;

            for (int k = 0; k < number_of_medications; k++) {
                if (strcmp(conflicts[i].conflicting_medication[l], medicine_details[k].name) == 0) {
                    strcpy(conflicting_medications[i][conflicting_medications_count], medicine_details[k].name);
                    conflicting_medications_count++;
                    conflict_found = true;
                }
            }
        }


    }


    fclose(resident_record_conflict_file);

    if (conflict_found == true)
    {
        print_conflicting_medications(medicine_details, conflicting_medications, number_of_medications);
        return conflict_found;
    } else {
        return conflict_found;
    }
}


void print_conflicting_medications(medicine_database medicine_details[],
                                   char conflicting_medications[MAX_MEDICATIONS]
                                   [MAX_CONFLICTING_MEDICATIONS][MAX_MEDICATION_NAME_LGT],
                                   int number_of_medications) {


    printf("Conflicting medications:\n");

    for (int i = 0; i < number_of_medications; i++) {

        // Check if there are conflicting medications for the current medicine
        if (conflicting_medications[i][0][0] != '\0') {
            for (int j = 0; j < MAX_CONFLICTING_MEDICATIONS && conflicting_medications[i][j][0] != '\0'; j++) {
                printf("\n%s and %s are conflicting medications.\n", medicine_details[i].name, conflicting_medications[i][j]);
            }
        }
        printf("\n");
    }

}



// Functions to retrieve medication details information from medicine_database.txt and display it
void get_medication_details(medicine_database medicine_details[],
                            resident_medications medications[], int number_of_medications) {
    FILE *medicine_database_file = fopen("../database_textfiles/medicine_database.txt", "r");

    // Check if the file was successfully opened
    if (medicine_database_file == NULL) {
        fprintf(stderr, "Error opening medicine database file.\n");
        exit(EXIT_FAILURE);
    }


    // Loop through resident medications
    for (int i = 0; i < number_of_medications; i++) {
        rewind(medicine_database_file);  // Move the file pointer to the beginning of the file

        // Reset ID_Key found flag for each resident medication
        int medicine_id_key_found = 0;

        // Loop through the medicine database
        while (fscanf(medicine_database_file, "%d,%[^,],%[^,],%lf,%s",
                      &medicine_details[i].id_key, medicine_details[i].name,
                      medicine_details[i].type, &medicine_details[i].strength,
                      medicine_details[i].unit_of_strength) == 5) {
            if (medicine_details[i].id_key == medications[i].medication) {
                // ID_Key found, set the flag
                medicine_id_key_found = 1;
                break;  // Break out of the loop after finding a match
            }
        }

        // Check if the social_security_number is not found for the current resident medication
        if (!medicine_id_key_found) {
            fprintf(stderr,"Id key for medicine %d not found in the database.\n",
                    medications[i].medication);
            fclose(medicine_database_file);  // Close the file before exiting
            exit(EXIT_FAILURE);
        }

    }

    fclose(medicine_database_file);
}


void print_medicine_detail_info(medicine_database medicine_details[], int number_of_medications) {
    for (int i = 0; i < number_of_medications; i++) {
        printf("Medicine ID: %d\n"
               "Medicine name: %s\n"
               "Medicine type: %s\n"
               "Medicine strength: %.2lf %s\n\n",
               medicine_details[i].id_key, medicine_details[i].name, medicine_details[i].type,
               medicine_details[i].strength, medicine_details[i].unit_of_strength);
    }
}

// Function to restart the program if needed
char program_restart() {
    char restart_program;
    while(1) {
        printf("Next resident? (y/n)\n->");
        scanf(" %c", &restart_program);

        if (restart_program == 'y' || restart_program == 'n') {
            break;
        }
        else {
            printf("Invalid input. Try again.\n");
        }
    }
    return restart_program;
}