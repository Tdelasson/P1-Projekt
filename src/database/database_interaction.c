#include <stdio.h>
#include <stdlib.h>
#include "..\main\main.h"

// Function to retrieve resident information from a file and display it
resident_record* get_resident_record(resident_record residents[])
{
    // Open the resident record file in read mode
    FILE* resident_record_file = fopen("resident_record.txt", "r");

    // Check if the file was successfully opened
    if (resident_record_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    // Create an array to store resident records
    int i=0;

    // Loop through the array of resident_record structures
    for (i; i < MAX_PATIENTS; i++) {

        // Read data from the file using the corrected format specifier
        int result = fscanf(resident_record_file, ": %d, %[^,], %[^,], %lf, %d, %[^,], %d, %[^,], %d",
                            &residents[i].id_key, residents[i].first_name,
                            residents[i].surname, &residents[i].apartment_number, &residents[i].age,
                            residents[i].gender, &residents[i].weight,
                            residents[i].weight_unit, &residents[i].social_security_number);

        // Check if the expected number of fields (9) were successfully read
        if (result != 9) {
            // If not, break out of the loop indicating the end of file or a read error
            break;
        }

        // Store the read resident information in the array
        int number_of_residents_read = i;
    }

    // Close the file as it is no longer needed
    fclose(resident_record_file);
/*
    // Display the resident information retrieved from the file
    for (int j = 0; j < MAX_PATIENTS; j++) {
        printf(" Information on resident no. %d: \n Name: %s %s\n Apartment number: %.2lf \n Age: %d\n "
               "Gender: %s\n Weight: %d %s\n Social Security Number: %d\n\n", j+1,
               residents[j].first_name, residents[j].surname, residents[j].apartment_number, residents[j].age,
               residents[j].gender,residents[j].weight, residents[j].weight_unit, residents[j].social_security_number);
    }
*/
    // Return the number of residents read from the file
    return residents;
}

resident_medications* get_resident_record_medicine(resident_medications medications[]) {
// Open the resident record file in read mode

    FILE *resident_record_medicine_file = fopen("resident_record_medicine.txt", "r");

    //search for the resident in the medication database
    //resident_medications medications[50];

    // Check if the file was successfully opened
    if (resident_record_medicine_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    // Create an array to store resident records
    int i = 0;

    // Loop through the array of resident_record structures
    for (i; i < MAX_PATIENTS; i++) {
        // Read data from the file using the corrected format specifier
        int result_patient = fscanf(resident_record_medicine_file, ": %d, %d",
                                    &medications[i].id_key, &medications[i].patient_id_key);

        for (int j = 0; i < MAX_MEDICATIONS; j++) {

            int result_medicine = fscanf(resident_record_medicine_file, "%[^,], %[^,], %d, %d, %d, %d,",
                                         medications[i].medication[j], medications[i].medication_unit[j],
                                         &medications[i].total_daily_dose[j], &medications[i].morning_dose[j],
                                         &medications[i].noon_dose[j], &medications[i].evening_dose[j]);

            if (result_medicine != 6) {
                break;
            }
        }

        // Check if the expected number of fields (9) were successfully read
        if (result_patient != 2) {
            // If not, break out of the loop indicating the end of file or a read error
            break;
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
}
*/
medicine_database* get_resident_medicine_data(medicine_database residents[]);

medicine_conflicts* get_medicine_conflicts(medicine_conflicts residents[]);