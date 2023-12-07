#include "pillbox.h"
#include "..\main\main.h"
#include <stdlib.h>
#include <stdio.h>

void dispensing() {
    box_place pill_box[ROWS][COLUMNS] = {{none,    monday, tuesday, wednesday, thursday, friday, saturday, sunday},
                                         {morning, empty,  empty,   empty,     empty,    empty,  empty,    empty},
                                         {noon,    empty,  empty,   empty,     empty,    empty,  empty,    empty},
                                         {evening, empty,  empty,   empty,     empty,    empty,  empty,    empty}};

    print_box(pill_box);

    clear_pill_box(pill_box);

    update_box_1 (pill_box);



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

int update_box_1 (box_place pill_box[][COLUMNS]) {

    double medications[medications_count].total_weekly_dose,

    

    pill_box[1][1] = one;
    pill_box[1][2] = one;
    pill_box[1][3] = one;
    pill_box[1][4] = one;
    pill_box[1][5] = one;
    pill_box[1][6] = one;
    pill_box[1][7] = one;

    return 0;
}

void clear_pill_box(box_place pill_box[][COLUMNS]) {
    for (int x = 1; x < ROWS; x++) {
        for (int y = 1; y < COLUMNS; y++) {
            pill_box[x][y] = empty;
        }
    }
}