#include <stdio.h>
#include <stdlib.h>

// Defining constants used in functions
#define MAX_RESIDENTS 50
#define MAX_NAME_LGT 50
#define MAX_MEDICATIONS 15 // TODO: Dynamic allocation
#define MAX_MEDICATION_NAME_LGT 100
#define MAX_GENDER_LGT 6
#define MAX_CONFLICTING_MEDICATIONS 10


//Making a struct type for Nursing home staff personnel
typedef struct{
    int id_key;
    char first_name;
    char surname;
}staff_record;

// Making a struct type for resident record data
typedef struct {
    int id_key;
    char first_name[MAX_NAME_LGT];
    char surname[MAX_NAME_LGT];
    double apartment_number;
    int age;
    char gender [MAX_GENDER_LGT];
    int weight;
    char weight_unit [5];
    int social_security_number;

}resident_record;

// Making a struct type for resident medication data
typedef struct {
    // Making space for residents to take multiple medications
    int medication;
    double total_weekly_dose;
    char medication_unit[MAX_MEDICATION_NAME_LGT];
    int weekdays [7];
    double morning_dose;
    double afternoon_dose;
    double evening_dose;

}resident_medications;

typedef struct {
    int id_key;
    char name[50];
    char type[10];
    double strength;
    char unit_of_strength[10];

}medicine_database;

typedef struct {
    char conflicting_medication[10][MAX_MEDICATION_NAME_LGT];

}medicine_conflicts;

// Nursing_Home_personnel* get_staff_record(staff_record staffs[]);

// scans ID key input from user
int scan_resident_number();

// Scans and prints the resident personal information from resident_record.txt
resident_record get_resident_record(void);
int scan_resident_database(FILE *resident_record_file,resident_record* resident,int id_key);
void print_resident_record(resident_record resident);

// Scans and prints the resident medication information from resident_record_medicine.txt
int get_resident_record_medicine(resident_medications medications[], int resident_id_key);
void print_resident_medication(resident_medications medications[], int medications_count);

// Checks for conflicts in medications for the resident
void get_resident_medication_conflict(resident_medications medications[], int number_of_medications);
// check_resident_medications
