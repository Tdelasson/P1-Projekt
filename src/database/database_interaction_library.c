#include "database_interaction.h"
#include <stdio.h>

// Function to read patient information from a file and store it in an array of patient_journal structures
int read_all_patients_from_file(FILE* input_file, patient_journal patients[]) {
    int i;

    // Loop through the array of patient_journal structures
    for (i = 0; i < MAX_PATIENTS; i++) {
        patient_journal new_patient;

        // Read data from the file using the corrected format specifier
        int result = fscanf(input_file, ".%d, %[^,], %[^,], %d, %[^,], %d, %[^,], %d",
                            &new_patient.id_key, new_patient.first_name, new_patient.surname, &new_patient.age,
                            new_patient.gender, &new_patient.weight, new_patient.weight_unit, &new_patient.social_security_number);

        // Check if the expected number of fields (8) were successfully read
        if (result != 8) {
            // If not, break out of the loop indicating the end of file or a read error
            break;
        }

        // Store the read patient information in the array
        patients[i] = new_patient;
    }

    // Return the number of patients successfully read from the file
    return i;
}
