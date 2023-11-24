#include <stdio.h>
#include <stdlib.h>
#include "database_interaction.h"

// Function to retrieve patient information from a file and display it
int get_patient_journal()
{
    // Open the patient journal file in read mode
    FILE* patient_journal_file = fopen("patient_journal.txt", "r");

    // Check if the file was successfully opened
    if (patient_journal_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }

    // Create an array to store patient records
    patient_journal patients[50];

    // Read patient information from the file into the array
    int number_of_patients_read = read_all_patients_from_file(patient_journal_file, patients);

    // Close the file as it is no longer needed
    fclose(patient_journal_file);

    // Display the patient information retrieved from the file
    for (int i = 0; i < MAX_PATIENTS; i++) {
        printf(" %d, %s, %s, %d, %s, %d\n",
               patients[i].id_key, patients[i].first_name, patients[i].surname, patients[i].age,
               patients[i].gender, patients[i].social_security_number);
    }

    // Return the number of patients read from the file
    return number_of_patients_read;
}
