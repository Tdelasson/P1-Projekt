#include <stdio.h>
#include <stdlib.h>
#include "..\main\main.h"
#include "string.h"


int scan_staff_number() {
    int id_key;
    printf("Enter Personnel ID_Key: ");
    scanf("%d", &id_key);
    return id_key;
}

int verify_staff(void) {
    int staff_id;
    FILE *nursing_home_file = fopen("nursing_home_staff.txt", "r");
    staff_record staff;

    if (nursing_home_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    int i;
    while(1) {
        rewind(nursing_home_file);
        staff_id = scan_staff_number();

        for (i = 0; 1; i++) {
            int staff_result = fscanf(nursing_home_file, "%d, %49[^,], %49[^\n]\n",
                                      &staff.id_key, staff.first_name, staff.surname);
            if (staff.id_key == staff_id) {
                printf("\nStaff checked in\n");
                printf("Name: %s %s\n\n", staff.first_name, staff.surname);
                fclose(nursing_home_file);
                return 1;

            } else if (staff_result != 3) {
                break;
            }
        }
        fclose(nursing_home_file);
        printf("Staff not registered\n");
    }

}


// Function to retrieve resident information from a file and display it
resident_record get_resident_record(void) {
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
        resident.social_security_number = scan_resident_number();
        record_found = scan_resident_database(resident_record_file,&resident,resident.social_security_number);
    }

    // Return the resident information
    fclose(resident_record_file);
    return resident;
}

int scan_resident_number(){
    //Prompts and scans the resident id key
    int social_security_number;
    printf("Enter Resident CPR: \n-> ");
    scanf("%d", &social_security_number);
    return social_security_number;
}

int scan_resident_database(FILE *resident_record_file,resident_record* resident,int social_security_number){
    rewind(resident_record_file); // Move the file pointer to the beginning of the file

    while (fscanf(resident_record_file, "%d, %[^,], %[^,], %lf, %d, %[^,], %d, %[^,], %d",
                  &resident->id_key, resident->first_name, resident->surname,
                  &resident->apartment_number, &resident->age,
                  resident->gender, &resident->weight,
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


void get_resident_medication_conflict(medicine_database medicine_details[], int number_of_medications) {
    FILE *resident_record_conflict_file = fopen("medicine_conflicts.txt", "r");

    // Check if the file was successfully opened
    if (resident_record_conflict_file == NULL) {
        fprintf(stderr, "Error opening resident_record_conflict file.\n");
        exit(EXIT_FAILURE);
    }

    // Create an array to store resident records
    medicine_conflicts conflicts[MAX_CONFLICTING_MEDICATIONS];
    int social_security_number = 0;
    char resident_medication[MAX_MEDICATION_NAME_LGT];
    int conflict_count = 0;


    // Loop through the array of medication
    for (int i = 0; i < number_of_medications; i++) {
        // Move the file pointer to the beginning
        rewind(resident_record_conflict_file);

        // Reset counters for each medication
        conflict_count = 0;

        // Iterate through the file to find conflicts for the current medication
        while (fscanf(resident_record_conflict_file, "%d, %[^,],", &social_security_number, resident_medication) == 2) {

            if (strcmp(resident_medication, medicine_details[i].name) == 0) {

                char line[1024]; // remember to adjust the buffer size accordingly
                if (fgets(line, sizeof(line), resident_record_conflict_file) != NULL) {
                    // Tokenize the line using strtok
                    char *token = strtok(line, ",");
                    while (token != NULL) {
                        // Remove newline character if present in the last token
                        size_t len = strlen(token);
                        if (len > 0 && token[len - 1] == '\n') {
                            token[len - 1] = '\0';
                        }

                        // Process the token (save it to your data structure, etc.)
                        strcpy(conflicts[i].conflicting_medication[conflict_count], token);

                        // Increment counters
                        conflict_count++;

                        // Get the next token
                        token = strtok(NULL, ",");
                    }
                }
            } else {
                // Skip the rest of the line for medications of other residents
                while (fgetc(resident_record_conflict_file) != '\n' &&
                       !feof(resident_record_conflict_file)) {
                    // Keep reading characters until the end of the line
                }

            }
            // Process the conflicts for each medication

        }
        /*printf("\nConflicting medications for: %s\n", medicine_details[i].name);
        for (int j = 0; j < conflict_count; j++) {
            printf("%s\n", conflicts[i].conflicting_medication[j]);
        }*/

        // TODO: Make sure conflicting medications dont get printed twice
        for (int j = 0; j < conflict_count; j++) {
            for (int k = 0; k < number_of_medications; k++) {
                if (strcmp(conflicts[i].conflicting_medication[j], medicine_details[k].name) == 0) {
                    printf("Conflicting medication found: %s and %s\n", medicine_details[i].name,
                           medicine_details[k].name);
                }
            }
        }

    }
    fclose(resident_record_conflict_file);

    printf("\n");
}





void get_medication_details(medicine_database medicine_details[],
                            resident_medications medications[], int number_of_medications) {
    FILE *medicine_database_file = fopen("medicine_database.txt", "r");

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
               "Medicine strength: %.2lf\n"
               "Medicine unit of strength: %s\n\n",
               medicine_details[i].id_key, medicine_details[i].name, medicine_details[i].type,
               medicine_details[i].strength, medicine_details[i].unit_of_strength);
    }
}





medicine_database* get_resident_medicine_data(medicine_database residents[]);

medicine_conflicts* get_medicine_conflicts(medicine_conflicts residents[]);