#include "pillbox.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void dispensing(resident_medications medications[], medicine_database medicine_details[], int medications_count) {
    box_place pill_box[ROWS][COLUMNS] = {{none,    monday, tuesday, wednesday, thursday, friday, saturday, sunday},
                                         {morning, empty,  empty,   empty,     empty,    empty,  empty,    empty},
                                         {noon,    empty,  empty,   empty,     empty,    empty,  empty,    empty},
                                         {evening, empty,  empty,   empty,     empty,    empty,  empty,    empty}};

    double actual_morning_dose, actual_noon_dose, actual_evening_dose;
    char strength_type[MAX_TYPE_LGT];

    for (int i = 0; i < medications_count; i++) {
        check_medicine(medications, medicine_details, i);

        double actual_weekly_dose = convert(medications[i].total_weekly_dose, medications[i].medication_unit,
                                            medicine_details[i].unit_of_strength);

        int number_of_days = medication_days(medications[i]);
        calculate_actual_dose(&actual_morning_dose, &actual_noon_dose, &actual_evening_dose,
                              actual_weekly_dose, number_of_days, medications,
                              medicine_details, i);

        for (int j = 0; j < WEEKDAYS; j++) {
            if (medications[i].weekdays[j] == 1) {
                fill_day(actual_morning_dose, actual_noon_dose, actual_evening_dose, pill_box, medications[j]);
            }
        }


        showcased_unit(strength_type, medicine_details, i);

        print_box(pill_box, actual_morning_dose, actual_noon_dose, actual_evening_dose, strength_type);
        clear_pill_box(pill_box);

        char d;
        printf("\n");

        printf("New medication? (y/n)\n->");
        scanf("%s", &d);

        if (d == 'n' || d == 'N')
            break;
        else
            continue;
    }
    printf("There's no more medication to dispense to this resident\n");
}


void check_medicine(resident_medications medications[], medicine_database medicine_details[], int i) {

    int bar_code;
    printf("Enter the bar code for %s\n->", medicine_details[i].name);
    scanf("%d", &bar_code);

    while (1) {
        if (medications[i].medication == bar_code) {
            printf("\n%s\n", medicine_details[i].name);
            break;
        } else {
            printf("Incorrect bar code\n\n");
            printf("Enter the bar code for %s\n->", medicine_details[i].name);
            scanf("%d", &bar_code);
        }
    }
}

double convert(double dose, const char *from_unit, const char *to_unit) {
    struct Conversion {
        const char *unit_pair;
        double multiplier;
    };

    struct Conversion conversions[] = {
            {"mcg->mg/ml", 0.001 }, {"mg->g/l", 0.001 },
            {"mg->mcg/ml", 1000}, {"g->mg/ml", 1000},
            {"mg->mg/ml", 1}, {"g->g/ml", 1},
            {"mcg->mcg/ml", 1}, {"mcg->mg", 0.001},
            {"mg->mcg", 1000}, {"g->mg", 1000},
            {"mg->g", 0.001}
            // Add more conversions as needed
    };

    for (int i = 0; i < sizeof(conversions) / sizeof(conversions[0]); ++i) {
        // Create a temporary buffer to hold a copy of unit_pair
        char temp_unit_pair[20]; // Adjust the size according to your maximum string length
        strcpy(temp_unit_pair, conversions[i].unit_pair);

        char *token = strtok(temp_unit_pair, "->");
        char *from = token;
        token = strtok(NULL, "->");
        char *to = token;

        if ((strcmp(from, from_unit) == 0) && (strcmp(to, to_unit) == 0)) {
            double result = dose * conversions[i].multiplier;
            return result;
        }
    }
    double result = dose;
    return result;
}


int medication_days (resident_medications medications) {
    int days = 0;

    for (int j = 0; j < WEEKDAYS; j++) {
        if (medications.weekdays[j] == 1) {
            days++;
        }
    }
    return days;
}

void calculate_actual_dose (double* actual_morning_dose, double* actual_noon_dose, double* actual_evening_dose,
                             double actual_weekly_dose, double number_of_days, resident_medications medications[],
                             medicine_database medicine_details[], int i){
    *actual_morning_dose =
            ((actual_weekly_dose / number_of_days) * medications[i].morning_dose) / medicine_details[i].strength;
    *actual_noon_dose =
            ((actual_weekly_dose / number_of_days) * medications[i].afternoon_dose) / medicine_details[i].strength;
    *actual_evening_dose =
            ((actual_weekly_dose / number_of_days) * medications[i].evening_dose) / medicine_details[i].strength;

}

void showcased_unit (char strength_type[], medicine_database medicine_details[], int i) {
    if (strcmp(medicine_details[i].unit_of_strength, "mg") == 0 ||
        strcmp(medicine_details[i].unit_of_strength, "mcg") == 0 ||
        strcmp(medicine_details[i].unit_of_strength, "g") == 0) {
        strcpy(strength_type, "pill");
    } else {
        char *token = strtok(medicine_details[i].unit_of_strength, "/"); // Split the string by "/"
        char *last_part = NULL;

        while (token != NULL) {
            last_part = token; // Keep updating to get the last part after each split
            token = strtok(NULL, "/"); // Move to the next token
        }
        strcpy(strength_type, last_part);
        // Now last_part contains the last segment after "/"
    }
}

void fill_day (double actual_morning_dose, double actual_noon_dose, double actual_evening_dose,
               box_place pill_box[][COLUMNS], resident_medications medications) {

    for (int j = 0; j < 7; j++) {
        if (medications.weekdays[j] == 1) {
            if (actual_morning_dose > 0) {
                pill_box[1][j + 1] = actual_morning;
            } else {
                pill_box[1][j + 1] = empty;
            }
            if (actual_noon_dose > 0) {
                pill_box[2][j + 1] = actual_noon;
            } else {
                pill_box[2][j + 1] = empty;
            }
            if (actual_evening_dose > 0) {
                pill_box[3][j + 1] = actual_evening;
            } else {
                pill_box[3][j + 1] = empty;
            }
        }
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

void clear_pill_box(box_place pill_box[][COLUMNS]) {
    for (int x = 1; x < ROWS; x++) {
        for (int y = 1; y < COLUMNS; y++) {
            pill_box[x][y] = empty;
        }
    }
}

void print_box_place(box_place c, double actual_morning_dose, double actual_noon_dose, double actual_evening_dose, char strength_type[]){
    switch (c) {
        case monday:
            printf("%-15s", " Monday");
            break;
        case tuesday:
            printf("%-14s", "Tuesday");
            break;
        case wednesday:
            printf("%-14s", "Wednesday");
            break;
        case thursday:
            printf("%-14s", "Thursday");
            break;
        case friday:
            printf("%-14s", "Friday");
            break;
        case saturday:
            printf("%-14s", "Saturday");
            break;
        case sunday:
            printf("%-14s", "Sunday");
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
            printf("%-14s", "_____");
            break;
        case none:
            printf("   ");
            break;
        case actual_morning:
            printf("%-9.4lf %-4s", actual_morning_dose, strength_type);
            break;
        case actual_noon:
            printf("%-9.4lf %-4s", actual_noon_dose, strength_type);
            break;
        case actual_evening:
            printf("%-9.4lf %-4s", actual_evening_dose, strength_type);
            break;
        default:
            printf("invalid");
            exit(-1);
    }
}