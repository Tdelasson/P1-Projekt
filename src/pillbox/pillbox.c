#include "pillbox.h"
#include <stdio.h>
#include <stdlib.h>

void dispensing() {
    box_place pill_box[ROWS][COLUMNS] = {{none,   monday, tuesday, wednesday, thursday, friday, saturday, sunday},
                                         {morning, empty,  empty,   empty,     empty,    empty,  empty,    empty},
                                         {noon,    empty,  empty,   empty,     empty,    empty,  empty,    empty},
                                         {evening, empty,  empty,   empty,     empty,    empty,  empty,    empty}};
    int ny;

    check_patient();

    update_box_1(pill_box);

    print_box(pill_box);

    clear_pill_box(pill_box);

    printf("\n>");
    scanf("%d", &ny);

    update_box_2(pill_box);

    print_box(pill_box);
}

void check_patient() {
    patient_journal patients[MAX_PATIENTS];
    get_patient_journal(patients);
    int patient_number;

    int run = 1;
    while (run == 1){
        // Ask for patient number
        printf("Type the patients number\n>");
        scanf("%d", &patient_number);
        // Compare patient number to id_key from patient_journal.txt
        for (int i = 0; i < MAX_PATIENTS; i++) {
            if (patient_number == patients[i].id_key) {
                printf("Patient registered\n");
                run = 0;
                i = MAX_PATIENTS;
            }
        }
        if (run == 1) {
            printf("Patient not registered\n");
        }
    }

}

void check_medicine () {
    printf("Type the ");
}


void print_box_place(box_place c){
    switch (c) {
        case monday:
            printf(" mon");
            break;
        case tuesday:
            printf("tue");
            break;
        case wednesday:
            printf("wed");
            break;
        case thursday:
            printf("thu");
            break;
        case friday:
            printf("fri");
            break;
        case saturday:
            printf("sat");
            break;
        case sunday:
            printf("sun");
            break;
        case morning:
            printf("morn");
            break;
        case noon:
            printf("noon");
            break;
        case evening:
            printf("even");
            break;
        case empty:
            printf("___");
            break;
        case none:
            printf("   ");
            break;
        case one:
            printf(" 1 ");
            break;
        case two:
            printf(" 2 ");
            break;
        case three:
            printf(" 3 ");
            break;
        case four:
            printf(" 4 ");
            break;
        case five:
            printf(" 5 ");
            break;
        default:
            printf("invalid");
            exit(-1);
    }
}

void print_box(box_place pill_box[][COLUMNS]) {
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLUMNS; y++) {
            printf("  ");
            print_box_place(pill_box[x][y]);
        }
        printf("\n");
    }
}

void clear_pill_box(box_place pill_box[][COLUMNS]) {
    for (int x = 1; x < ROWS; x++) {
        for (int y = 1; y < COLUMNS; y++) {
            pill_box[x][y] = empty;
        }
    }
}

int update_box_1 (box_place pill_box[][COLUMNS]) {
    pill_box[1][1] = one;
    pill_box[1][2] = one;
    pill_box[1][3] = one;
    pill_box[1][4] = one;
    pill_box[1][5] = one;
    pill_box[1][6] = one;
    pill_box[1][7] = one;

    return 0;
}

int update_box_2 (box_place pill_box[][COLUMNS]) {
    pill_box[3][1] = one;
    pill_box[3][3] = one;
    pill_box[3][5] = one;
    pill_box[3][7] = one;

    return 0;
}