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
        //double actual_morning_dose = (medications[i].total_weekly_dose * medications[i].morning_dose) / medicine_details[i].strength;
        //double actual_noon_dose = (medications[i].total_weekly_dose * medications[i].afternoon_dose) / medicine_details[i].strength;
        //double actual_evening_dose = (medications[i].total_weekly_dose * medications[i].evening_dose) / medicine_details[i].strength;

        int days = 0;

        int number_of_days = medication_days(medications, medications_count);

        for (int j = 0; j < 7; j++) {
            if (medications[i].weekdays[j] == 1) {


                printf("%d \n", days);
                double actual_morning_dose = (medications[i].total_weekly_dose / (double) number_of_days * medications[i].morning_dose);
                double actual_noon_dose = (medications[i].total_weekly_dose / (double) number_of_days * medications[i].afternoon_dose);
                double actual_evening_dose = medications[i].total_weekly_dose / (double) number_of_days * medications[i].evening_dose;

                pill_box[1][j + 1] = actual_morning;
                pill_box[2][j + 1] = actual_noon;
                pill_box[3][j + 1] = actual_evening;

                //printf("actual morning dose: %.2lf %s\n", actual_morning_dose, medicine_details[i].unit_of_strength);
                //printf("actual noon dose: %.2lf %s\n", actual_noon_dose, medicine_details[i].unit_of_strength);
                //printf("actual evening dose: %.2lf %s\n \n", actual_evening_dose, medicine_details[i].unit_of_strength);

                print_box(pill_box,  actual_morning_dose,  actual_noon_dose,  actual_evening_dose);

            }
        }
        clear_pill_box(pill_box);

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

void print_box_place(box_place c, double actual_morning_dose, double actual_noon_dose, double actual_evening_dose){
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
            printf("%.2lf     ", actual_morning_dose);
            break;
        case actual_noon:
            printf("%.2lf     ", actual_noon_dose);
            break;
        case actual_evening:
            printf("%.2lf     ", actual_evening_dose);
            break;
        default:
            printf("invalid");
            exit(-1);
    }
}

void print_box(box_place pill_box[][COLUMNS], double actual_morning_dose, double actual_noon_dose, double actual_evening_dose) {
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLUMNS; y++) {
            printf("  ");
            print_box_place(pill_box[x][y],  actual_morning_dose,  actual_noon_dose,  actual_evening_dose);
        }
        printf("\n");
    }
}

int medication_days (resident_medications medications[], int medications_count) {

    int days_1 = 0;

    for (int i = 0; i < medications_count; i++) {
        for (int j = 0; j < 7; j++) {
            if (medications[i].weekdays[j] == 1) {
                days_1++;
            }
        }
    }
    return days_1;
}


void clear_pill_box(box_place pill_box[][COLUMNS]) {
    for (int x = 1; x < ROWS; x++) {
        for (int y = 1; y < COLUMNS; y++) {
            pill_box[x][y] = empty;
        }
    }
}


/*
int update_box_1 (box_place pill_box[][COLUMNS], resident_medications medications[],
                  medicine_database medicine_details[], int medications_count) {

   for (int i = 0; i < medications_count; i++) {

   }
    return 0;
}
 */