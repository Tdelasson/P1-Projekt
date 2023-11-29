#include <stdio.h>
#include <stdlib.h>
#include "..\main\main.h"


// Function to retrieve patient information from a file and display it
patient_journal* get_patient_journal(patient_journal patients[])
{
    // Open the patient journal file in read mode
    FILE* patient_journal_file = fopen("patient_record.txt", "r");

    // Check if the file was successfully opened
    if (patient_journal_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    // Create an array to store patient records
    int i=0;

    // Loop through the array of patient_journal structures
    for (i; i < MAX_PATIENTS; i++) {

        // Read data from the file using the corrected format specifier
        int result = fscanf(patient_journal_file, ": %d, %[^,], %[^,], %lf, %d, %[^,], %d, %[^,], %d",
                            &patients[i].id_key, patients[i].first_name,
                            patients[i].surname, &patients[i].apartment_number, &patients[i].age,
                            patients[i].gender, &patients[i].weight,
                            patients[i].weight_unit, &patients[i].social_security_number);

        // Check if the expected number of fields (9) were successfully read
        if (result != 9) {
            // If not, break out of the loop indicating the end of file or a read error
            break;
        }

        // Store the read patient information in the array
        int number_of_patients_read = i;
    }

    // Close the file as it is no longer needed
    fclose(patient_journal_file);

    // Display the patient information retrieved from the file
    for (int j = 0; j < MAX_PATIENTS; j++) {
        printf(" Information on resident no. %d: \n Name: %s %s\n Apartment number: %.2lf \n Age: %d\n "
               "Gender: %s\n Weight: %d %s\n Social Security Number: %d\n\n", j+1,
               patients[j].first_name, patients[j].surname, patients[j].apartment_number, patients[j].age,
               patients[j].gender,patients[j].weight, patients[j].weight_unit, patients[j].social_security_number);
    }

    // Return the number of patients read from the file
    return patients;
}

patient_medications* get_patient_journal_medicine(patient_medications patients[]){

}

