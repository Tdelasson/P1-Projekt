#include "../Main/main.h"

#ifndef DATABASE_DB_PILLBOX_H
#define DATABASE_DB_PILLBOX_H

#endif //DATABASE_DB_PILLBOX_H

#define ROWS 4
#define COLUMNS 8

typedef enum box_place {none, monday, tuesday, wednesday, thursday, friday, saturday, sunday,
    morning, noon, evening,
    empty, actual_morning, actual_noon, actual_evening} box_place;

void print_box_place(box_place c, double actual_morning_dose, double actual_noon_dose, double actual_evening_dose);
void print_box(box_place pill_box[][COLUMNS], double actual_morning_dose, double actual_noon_dose, double actual_evening_dose);
int update_box_1 (box_place pill_box[][COLUMNS], resident_medications medications[],
                  medicine_database medicine_details[], int medications_count);
int medication_days (resident_medications medications[], int medications_count);
void clear_pill_box(box_place pill_box[][COLUMNS]);

//void weekdays(box_place j, resident_medications medications[], int medications_count);