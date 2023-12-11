#include "../Main/main.h"

#ifndef DATABASE_DB_PILLBOX_H
#define DATABASE_DB_PILLBOX_H

#endif //DATABASE_DB_PILLBOX_H

#define ROWS 4
#define COLUMNS 8

typedef enum box_place {none, monday, tuesday, wednesday, thursday, friday, saturday, sunday,
    morning, noon, evening,
    empty, actual_morning, actual_noon, actual_evening} box_place;

void print_box_place(box_place c, double actual_morning_dose, double actual_noon_dose,
                     double actual_evening_dose, char strength_type[]);

void print_box(box_place pill_box[][COLUMNS], double actual_morning_dose, double actual_noon_dose,
               double actual_evening_dose, char strength_type[]);

int medication_days (resident_medications medications);

void clear_pill_box(box_place pill_box[][COLUMNS]);

double convert(double dose, const char *from_unit, const char *to_unit);
