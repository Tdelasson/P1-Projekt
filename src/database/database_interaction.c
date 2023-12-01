#include <stdio.h>
#include <stdlib.h>
#include "..\main\main.h"

// Function to retrieve resident information from a file and display it
resident_record get_resident_record(int id_key) {
    resident_record resident;

    // Open the resident record file in read mode
    FILE *resident_record_file = fopen("resident_record.txt", "r");

    // Check if the file was successfully opened
    if (resident_record_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    // Initialize a variable to check if the record was found
    int record_found = 0;

    // Loop through the file as long as there are records to read
    while (fscanf(resident_record_file, "%d, %[^,], %[^,], %lf, %d, %[^,], %d, %[^,], %d",
                  &resident.id_key,
                  resident.first_name,
                  resident.surname, &resident.apartment_number, &resident.age,
                  resident.gender, &resident.weight,
                  resident.weight_unit, &resident.social_security_number) == 9) {
        // Check if the ID key matches
        if (resident.id_key == id_key) {
            record_found = 1;
            break;
        }
    }

    // Close the file as it is no longer needed
    fclose(resident_record_file);

    // If the record was not found, you might want to handle it appropriately
    if (!record_found) {
        // Handle the case where the record with the given ID key was not found
        // For example, you might set some default values or print an error message
        // and exit the program.
        printf("Record with ID %d not found.\n", id_key);
        exit(EXIT_FAILURE);
    }

    // Return the resident information
    return resident;
}


void print_resident_record(resident_record resident) {
    printf("Name: %s %s\n Apartment number: %.2lf\n Age: %d\n Gender: %s\n "
           "Weight: %d %s\n Social Security Number: %d\n\n",
           resident.first_name, resident.surname,
           resident.apartment_number, resident.age, resident.gender,
           resident.weight, resident.weight_unit, resident.social_security_number);

}


void get_resident_record_medicine(resident_medications medications[], int resident_id_key) {
    FILE *file = fopen("resident_record_medicine.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    int patientId, medicalId;
    int medications_count = 0;

    // Find the resident and start reading medications
    while (fscanf(file, "%d, %d,", &medicalId, &patientId) == 2) {
        // Skip over medications for other patients
        if (patientId != resident_id_key) {
            char buffer[256]; // Adjust the buffer size as needed
            fgets(buffer, sizeof(buffer), file);
            continue;
        }

        // Make a for loop that stores each medication in the medications array

       /* while (medications_count < MAX_MEDICATIONS &&
               fscanf(file, "%49[^,], %49[^,], %d, %d, %d, %d,",
                      medications[medications_count].medication,
                      medications[medications_count].medication_unit,
                      &medications[medications_count].total_daily_dose,
                      &medications[medications_count].morning_dose,
                      &medications[medications_count].noon_dose,
                      &medications[medications_count].evening_dose) == 6) {

            // Null-terminate the strings
            medications[medications_count].medication[MAX_MEDICATION_NAME_LGT] = '\0';
            medications[medications_count].medication_unit[MAX_MEDICATION_NAME_LGT] = '\0';

            medications_count++;
        }

        // Break out of the loop once medications for the target patient are read
        break;
    }*/

    fclose(file);
}









void print_resident_medication(resident_medications medications[]) {
    printf("Medication:\n");
    for (int i = 0; i < MAX_MEDICATIONS; i++) {
        printf("%s\n", medications[i].medication);
    }
}

/*
medicine_conflicts * get_resident_medication_conflict(int resident_id_key) {
// Open the resident record file in read mode

    FILE *resident_record_conflict_file = fopen("medicine_conflicts.txt", "r");
    FILE *resident_record_medicine_file = fopen("resident_record_medicine.txt");

    //search for the resident in the medication database

    // Check if the file was successfully opened
    if (resident_record_conflict_file == NULL || resident_record_medicine_file) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    // Create an array to store resident records
    resident_record residents[50];
    medicine_conflicts conflicts[50];
    int conflict_count = 0;

    // Loop through the array of resident_record structures
    for (int i; i < MAX_RESIDENTS; i++) {

        // Read data from the file using the corrected format specifier
        int result_RESIDENT = fscanf(resident_record_file, ": %d, %[^,], %[^,], %lf, %d, %[^,], %d, %[^,], %d",
                                     &residents[i].id_key, residents[i].first_name,
                                     residents[i].surname);

        if (result_RESIDENT != 3) {
            break;
        }


        for (int j = 0; j < MAX_MEDICATIONS; j++) {

            int result_medicine = fscanf(resident_record_file, "%[^,], %[^,], %[^,], %[^,],",
                                         residents[i].medication[j], residents[i].medication_type[j],
                                         residents[i].medication_strength[j], residents[i].medication_unit[j]);
            if (result_medicine != 4) {
                break;
            }
        }
    }

    fclose(resident_record_medicine_file);
    fclose(resident_record_conflict_file);

    return conflicts;
}
*/
medicine_database* get_resident_medicine_data(medicine_database residents[]);

medicine_conflicts* get_medicine_conflicts(medicine_conflicts residents[]);