#include "pillbox.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void dispensing(resident_medications medications[], medicine_database medicine_details[], int medications_count) {
    box_place pill_box[ROWS][COLUMNS] = {{none,    monday, tuesday, wednesday, thursday, friday, saturday, sunday},
                                         {morning, empty,  empty,   empty,     empty,    empty,  empty,    empty},
                                         {noon,    empty,  empty,   empty,     empty,    empty,  empty,    empty},
                                         {evening, empty,  empty,   empty,     empty,    empty,  empty,    empty}};


    for (int i = 0; i < medications_count; i++) {
        int number_of_days = medication_days(medications[i]);

        if (strcmp(medicine_details[i].type, "Liquid") == 0) {
            double actual_morning_dose = (medications[i].total_weekly_dose / (double) number_of_days * medications[i].morning_dose);
            double actual_noon_dose = (medications[i].total_weekly_dose / (double) number_of_days * medications[i].afternoon_dose);
            double actual_evening_dose = medications[i].total_weekly_dose / (double) number_of_days * medications[i].evening_dose;

            for (int j = 0; j < 7; j++) {
                if (medications[i].weekdays[j] == 1) {

                    pill_box[1][j + 1] = actual_morning;
                    pill_box[2][j + 1] = actual_noon;
                    pill_box[3][j + 1] = actual_evening;

                }
            }
            char strength_type[10];
            strcpy(strength_type, medicine_details[i].unit_of_strength);

            print_box(pill_box,  actual_morning_dose,  actual_noon_dose,  actual_evening_dose, strength_type);
            clear_pill_box(pill_box);

        } else{
            double actual_morning_dose = ((medications[i].total_weekly_dose / (double) number_of_days) * medications[i].morning_dose) / medicine_details[i].strength;
            double actual_noon_dose = ((medications[i].total_weekly_dose / (double) number_of_days) * medications[i].afternoon_dose) / medicine_details[i].strength;
            double actual_evening_dose = ((medications[i].total_weekly_dose / (double) number_of_days) * medications[i].evening_dose) / medicine_details[i].strength;
            for (int j = 0; j < 7; j++) {
                if (medications[i].weekdays[j] == 1) {

                    pill_box[1][j + 1] = actual_morning;
                    pill_box[2][j + 1] = actual_noon;
                    pill_box[3][j + 1] = actual_evening;

                }
            }
            char strength_type[10] = "tbl";

            print_box(pill_box,  actual_morning_dose,  actual_noon_dose,  actual_evening_dose, strength_type);
            clear_pill_box(pill_box);
        }


        // printf("%s", medicine_details[i].unit_of_strength);
        /*
        for (int j = 0; j < 7; j++) {
            if (medications[i].weekdays[j] == 1) {

                pill_box[1][j + 1] = actual_morning;
                pill_box[2][j + 1] = actual_noon;
                pill_box[3][j + 1] = actual_evening;

            }
        }
        */
        //print_box(pill_box,  actual_morning_dose,  actual_noon_dose,  actual_evening_dose);
        //clear_pill_box(pill_box);

        printf("\n");
        char y;
        printf("new medication? y/n\n->");
        scanf("%s", &y);
        if (y == 'y') {
            continue;
        } else {
            break;
        }
    }

}

void print_box_place(box_place c, double actual_morning_dose, double actual_noon_dose, double actual_evening_dose, char strength_type[]){
    switch (c) {
        case monday:
            printf(" monday   ");
            break;
        case tuesday:
            printf("tuesday  ");
            break;
        case wednesday:
            printf("wednesday");
            break;
        case thursday:
            printf("thursday ");
            break;
        case friday:
            printf("friday   ");
            break;
        case saturday:
            printf("saturday ");
            break;
        case sunday:
            printf("sunday");
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
            printf("_____    ");
            break;
        case none:
            printf("   ");
            break;
        case actual_morning:
            printf("%.2lf   %s  ", actual_morning_dose, strength_type);
            break;
        case actual_noon:
            printf("%.2lf   %s  ", actual_noon_dose, strength_type);
            break;
        case actual_evening:
            printf("%.2lf   %s  ", actual_evening_dose, strength_type);
            break;
        default:
            printf("invalid");
            exit(-1);
    }
}

void print_box(box_place pill_box[][COLUMNS], double actual_morning_dose, double actual_noon_dose, double actual_evening_dose, char strength_type[]) {
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLUMNS; y++) {
            printf("  ");
            print_box_place(pill_box[x][y],  actual_morning_dose,  actual_noon_dose,  actual_evening_dose, strength_type);
        }
        printf("\n");
    }
}

int medication_days (resident_medications medications) {
    int days = 0;

    for (int j = 0; j < 7; j++) {
        if (medications.weekdays[j] == 1) {
            days++;
        }
    }
    return days;
}


void clear_pill_box(box_place pill_box[][COLUMNS]) {
    for (int x = 1; x < ROWS; x++) {
        for (int y = 1; y < COLUMNS; y++) {
            pill_box[x][y] = empty;
        }
    }
}
