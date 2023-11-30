#include <stdio.h>
#include <stdlib.h>
#include "..\main\main.h"

Nursing_Home_personnel* get_staff_record(staff_record staffs[]) {
    // Open the resident record file in read mode
    FILE *Nursing_Home_file = fopen("Nursing_Home_personnel.txt", "r");

    // Check if the file was successfully opened
    if (Nursing_Home_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }
    int i=0;

    for (i; i < MAX_STAFF; i++) {

        int staff_result = fscanf(Nursing_Home_file, ": %d, %[^,], %[^,],");

        if (staff_result !=3){
            break;
        }
    }


}

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

    // Display the resident information retrieved from the file
    for (int j = 0; j < MAX_PATIENTS; j++) {
        printf(" Information on resident no. %d: \n Name: %s %s\n Apartment number: %.2lf \n Age: %d\n "
               "Gender: %s\n Weight: %d %s\n Social Security Number: %d\n\n", j+1,
               residents[j].first_name, residents[j].surname, residents[j].apartment_number, residents[j].age,
               residents[j].gender,residents[j].weight, residents[j].weight_unit, residents[j].social_security_number);
    }

    // Return the number of residents read from the file
    return residents;
}

resident_medications* get_resident_record_medicine(resident_medications residents[]){
    
}

medicine_database* get_resident_medicine_data(medicine_database residents[]);

medicine_conflicts* get_medicine_conflicts(medicine_conflicts residents[]);