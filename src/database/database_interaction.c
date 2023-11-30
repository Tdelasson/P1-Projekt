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

                printf("Medication: %d\n", medications[medications_count].medication);
                printf("Total Weekly Dose: %lf\n", medications[medications_count].total_weekly_dose);

                printf("Morning Dose: %lf\n", medications[medications_count].morning_dose);
                printf("Afternoon Dose: %lf\n", medications[medications_count].afternoon_dose);
                printf("Evening Dose: %lf\n", medications[medications_count].evening_dose);

                medications_count++;
            }

            // Break out of the loop once medications for the target patient are read
            break;

        } else {
            // Skip the rest of the line for medications of other residents
            while (fgetc(file) != '\n' && !feof(file)) {
                // Keep reading characters until the end of the line
        }

        // Store the read resident information in the array
        int number_of_residents_read = i;
    }

    // Close the file as it is no longer needed
    fclose(resident_record_medicine_file);
    return medications;
}
/*
    // Display the resident information retrieved from the file
    for (int g = 0; g < MAX_PATIENTS; g++) {
        printf(" Medication information on resident no. %d: \n Name: %s %s\n", g+1,
               medications[g]., residents[g].surname);

        for (int j = 0; j < MAX_MEDICATIONS; j++){

            printf("Medication: %s, Medication type: %s Medication strength: %s %s \n\n", j+1,
                   residents[g].medication[j], residents[g].medication_type[j],
                   residents[g].medication_strength[j], residents[g].medication_unit[j]);
        }
    }

    // Return the number of residents read from the file
    //return residents;
}

medicine_conflicts * get_resident_medication_conflict(int resident_id_key) {
// Open the resident record file in read mode

    FILE *resident_record_conflict_file = fopen("medicine_conflicts.txt", "r");
    FILE *resident_record_medicine_file = fopen("resident_record_medicine.txt");

    //search for the resident in the medication database

    medicine_conflicts conflicts[];

    // Check if the file was successfully opened
    if (resident_record_conflict_file == NULL || resident_record_medicine_file) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    // Create an array to store resident records
    int i = 0;

    // Loop through the array of resident_record structures
    for (i; i < MAX_PATIENTS; i++) {

        // Read data from the file using the corrected format specifier
        int result_patient = fscanf(resident_record_file, ": %d, %[^,], %[^,], %lf, %d, %[^,], %d, %[^,], %d",
                                    &residents[i].id_key, residents[i].first_name,
                                    residents[i].surname);

        for (int j = 0; i < MAX_MEDICATIONS; i++) {

            int result_medicine = fscanf(resident_record_file, "%[^,], %[^,], %[^,], %[^,],",
                                         residents[i].medication[j], residents[i].medication_type[j],
                                         residents[i].medication_strength[j], residents[i].medication_unit[j]);
            if (result_medicine != 4) {
                break;
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
            if (medications[i].weekdays[j] == 1) {
                switch (j) {
                    case 0: printf("Monday ");
                        break;
                    case 1: printf("Tuesday ");
                        break;
                    case 2: printf("Wednesday ");
                        break;
                    case 3: printf("Thursday ");
                        break;
                    case 4: printf("Friday ");
                        break;
                    case 5: printf("Saturday ");
                        break;
                    case 6: printf("Sunday ");
                        break;
                }

                // Print dose information for the day
                printf("\nMorning dose: %.2lf\n", medications[i].morning_dose);
                printf("Afternoon dose: %.2lf\n", medications[i].afternoon_dose);
                printf("Evening dose: %.2lf\n", medications[i].evening_dose);
            }
        }

        printf("\n");
    }
}


   void get_resident_medication_conflict(resident_medications medications[], int number_of_medications) {
        FILE *resident_record_conflict_file = fopen("medicine_conflicts.txt", "r");

        // Check if the file was successfully opened
        if (resident_record_conflict_file == NULL) {
            printf("Could not open file \n");
            exit(EXIT_FAILURE);
        }

        // Create an array to store resident records
        medicine_conflicts conflicts[MAX_MEDICATIONS];
        int id_key;
        int resident_medication;

        // Loop through the array of medication
        for (int i = 0; i < number_of_medications; i++) {
            // Move the file pointer to the beginning
            rewind(resident_record_conflict_file);

            // Initialize the conflicting medications array for each iteration
            for (int j = 0; j < MAX_CONFLICTING_MEDICATIONS; j++) {
                conflicts[i].conflicting_medication[j][0] = '\0';
            }

            // Iterate through the file to find conflicts for the current medication
            while (fscanf(resident_record_conflict_file, "%d, %d,", &id_key, &resident_medication) == 2) {
                if (resident_medication == medications[i].medication) {
                    // Skip the ID and medication names
                    while (fgetc(resident_record_conflict_file) != ',');

                    // Read conflicting medications
                    int j = 0;
                    while (fscanf(resident_record_conflict_file, "%[^,],", conflicts[i].conflicting_medication[j]) ==
                           1) {
                        // Remove leading and trailing whitespace from conflicting medication names
                        char *trimmed_name = strtok(conflicts[i].conflicting_medication[j], " \t\n\r");
                        if (trimmed_name != NULL && isalpha(trimmed_name[0])) {
                            strcpy(conflicts[i].conflicting_medication[j], trimmed_name);
                            j++;
                        }
                    }

                    // Break out of the loop once the medication is found
                    break;
                } else {
                    // Skip the rest of the line for medications of other residents
                    while (fgetc(resident_record_conflict_file) != '\n' && !feof(resident_record_conflict_file)) {
                        // Keep reading characters until the end of the line
                    }
                }
            }

            // Process the conflicts for each medication
            printf("\nConflicting medication for medication: %s\n", medications[i].medication);

            for (int j = 0; j < MAX_CONFLICTING_MEDICATIONS && conflicts[i].conflicting_medication[j][0] != '\0'; j++) {
                printf("Conflicting medication: %s\n", conflicts[i].conflicting_medication[j]);
            }
        }

        fclose(resident_record_conflict_file);
    }










*/

medicine_database* get_resident_medicine_data(medicine_database residents[]);

medicine_conflicts* get_medicine_conflicts(medicine_conflicts residents[]);