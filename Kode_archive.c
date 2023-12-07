
staff_record get_staff_record(staff_record staffs[]) {
    // Open the resident record file in read mode
    FILE *nursing_home_file = fopen("nursing_home_staff.txt", "r");

    // Check if the file was successfully opened
    if (nursing_home_file == NULL) {
        printf("Could not open file \n");
        exit(EXIT_FAILURE);
    }
    int i=0;

    for (i; i < MAX_STAFF; i++) {

        int staff_result = fscanf(nursing_home_file, ": %d, %[^,], %[^,],");

        if (staff_result !=3){
            break;
        }
    }
        nursing_home_file[MAX_STAFF];
        get_staff_record(staffs);
        int staff_number;

        int run = 1;
        while (run == 1){
            // Ask for patient number
            printf("Type the staffs number\n>");
            scanf("%d", &staff_number);
            // Compare patient number to id_key from patient_journal.txt
            for (int i = 0; i < MAX_STAFF; i++) {
                if (staff_number == staffs[i].id_key) {
                    printf("Staff checked in\n");
                    // print the patient name for the id_key that matches
                    printf("%s %s\n", staffs[i].first_name, staffs[i].surname);
                    // exit the loop when patient is found
                    i = MAX_STAFF;
                    run = 0;
                }
            }
            if (run == 1) {
                printf("Staff not registered\n");
            }
        }

    }