#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Defining constants used in functions
#define MAX_NAME_LGT 50
#define MAX_MEDICATIONS 10 // TODO: Dynamic allocation
#define MAX_MEDICATION_NAME_LGT 100
#define MAX_SEX_LGT 6
#define MAX_CONFLICTING_MEDICATIONS 10



//Making a struct type for Nursing home staff personnel
typedef struct{
    int id_key;
    char first_name [50];
    char surname [50];
}staff_record;

// Making a struct type for resident record data
typedef struct {
    int id_key;
    char first_name[MAX_NAME_LGT];
    char surname[MAX_NAME_LGT];
    double apartment_number;
    int age;
    char sex [MAX_SEX_LGT];
    int weight;
    char weight_unit [5];
    unsigned long int social_security_number;

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


// Making a struct type for medication details
typedef struct {
    int id_key;
    char name[MAX_MEDICATION_NAME_LGT];
    char type[10];
    double strength;
    char unit_of_strength[10];

}medicine_database;


// Making a struct type for medication conflicts
typedef struct {
    int id_key;
    char resident_medication[MAX_MEDICATION_NAME_LGT];
    char conflicting_medication[10][MAX_MEDICATION_NAME_LGT];
}medicine_conflicts;

// Scans and prints the staff personal information from staff_record.txt
int scan_staff_number();
int verify_staff(void);

// scans CPR input from user
unsigned long int scan_resident_number();

// Scans and prints the resident personal information from resident_record.txt
resident_record get_resident_record(void);
int scan_resident_database(FILE *resident_record_file,resident_record* resident,unsigned long int social_security_number);
void print_resident_record(resident_record resident);

// Scans and prints the resident medication information from resident_record_medicine.txt
int get_resident_record_medicine(resident_medications medications[], int resident_id_key);

// Checks for conflicts in medications for the resident
bool get_resident_medication_conflict(medicine_database medicine_details[], int number_of_medications);
void print_conflicting_medications(medicine_database medicine_details[],
                                   char conflicting_medications[MAX_MEDICATIONS]
                                   [MAX_CONFLICTING_MEDICATIONS][MAX_MEDICATION_NAME_LGT], int number_of_medications);

void get_medication_details(medicine_database medicine_details [],
                            resident_medications medications[], int number_of_medications);
void print_medicine_detail_info(medicine_database medicine_details[], int number_of_medications);

char program_restart();