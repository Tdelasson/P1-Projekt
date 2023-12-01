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

    // Loop through the file until the end
    // Feof checks if the end of the file has been reached
    while (!feof(resident_record_file)) {
        // Read data from the file using the corrected format specifier
        int result = fscanf(resident_record_file, ": %d, %[^,], %[^,], %lf, %d, %[^,], %d, %[^,], %d",
                            &resident.id_key,
                            resident.first_name,
                            resident.surname, &resident.apartment_number, &resident.age,
                            resident.gender, &resident.weight,
                            resident.weight_unit, &resident.social_security_number);

        // Check if the expected number of fields (9) were successfully read
        if (result == 9 && resident.id_key == id_key) {
            // If the ID key matches, break out of the loop
            break;
        }
    }

    // Close the file as it is no longer needed
    fclose(resident_record_file);

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

// Function to retrieve resident medication information from a file and display it
resident_medications *get_resident_record_medicine(int resident_id_key) {
    FILE *resident_record_medicine_file = fopen("resident_record_medicine.txt", "r");

    if (resident_record_medicine_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    // Dynamically allocate memory for an array of medications
    resident_medications *medications = malloc(MAX_MEDICATIONS * sizeof(resident_medications));
    if (medications == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the medication array index
    int i = 0;

    while (fscanf(resident_record_medicine_file, ": %d, %d", &medications[i].id_key, &medications[i].resident_id_key) == 2) {
        // Check if the current resident is the one we're looking for
        if (medications[i].resident_id_key == resident_id_key) {
            for (int j = 0; j < MAX_MEDICATIONS; j++) {
                // Read medication details
                if (fscanf(resident_record_medicine_file, "%[^,], %[^,], %d, %d, %d, %d,",
                           medications[i].medication[j], medications[i].medication_unit[j],
                           &medications[i].total_daily_dose[j], &medications[i].morning_dose[j],
                           &medications[i].noon_dose[j], &medications[i].evening_dose[j]) != 6) {
                    break;
                }

                // Print the medication for debugging
                printf("Medication: %s\n", medications[i].medication[j]);
            }
            break;  // Exit the loop since we found the resident's medication
        }

        i++;

        // Break if the array is full
        if (i >= MAX_MEDICATIONS) {
            break;
        }
    }

    fclose(resident_record_medicine_file);

    return medications;  // Return the pointer to the dynamically allocated array
}

void print_resident_medication(resident_medications *medications) {
    //printf("Medication: %s\n", medications->medication[0]);
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