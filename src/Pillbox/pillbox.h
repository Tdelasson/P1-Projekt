#ifndef DATABASE_DB_PILLBOX_H
#define DATABASE_DB_PILLBOX_H

#endif //DATABASE_DB_PILLBOX_H

#define ROWS 4
#define COLUMNS 8

typedef enum box_place {none, monday, tuesday, wednesday, thursday, friday, saturday, sunday,
    morning, noon, evening,
    empty, one, two, three, four, five} box_place;

void print_box_place(box_place c);
void print_box(box_place pill_box[][COLUMNS]);
int update_box_1 (box_place pill_box[][COLUMNS]);
void clear_pill_box(box_place pill_box[][COLUMNS]);