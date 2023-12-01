#include <stdio.h>
#include <stdlib.h>

// Defining constants used in functions
#define MAX_RESIDENTS 50
#define MAX_NAME_LGT 50
#define DOSE_LGT 10
#define MAX_MEDICATIONS 15 // TODO: Dynamic allocation
#define MAX_MEDICATION_NAME_LGT 100
#define MAX_MEDICATION_TYPE_NAME_LGT 20
#define MAX_MEDICATION_UNIT_NAME_LGT 4
#define MAX_AGE_LGT 3
#define MAX_GENDER_LGT 6
#define MAX_SOCIAL_SECURITY_NUMBER_LGT 10
#define MAX_STAFF 10

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
    char medication[MAX_MEDICATION_NAME_LGT];
    char medication_unit[MAX_MEDICATION_NAME_LGT];

    int total_daily_dose;
    int morning_dose;
    int noon_dose;
    int evening_dose;

}resident_medications;

typedef struct {
    int id_key;
    char name[50];
    char type[10];
    double strength;
    char unit_of_strength[10];

}medicine_database;

typedef struct {
    int id_key;
    char resident_medication[50];
    double strength;
    char unit[10];

}medicine_conflicts;

//Nursing_Home_personnel* get_staff_record(staff_record staffs[]);
int scan_resident_number();

resident_record get_resident_record(int id_key);
void print_resident_record(resident_record resident);

void get_resident_record_medicine(resident_medications medications[],int resident_id_key);
void print_resident_medication(resident_medications *medications);

//resident_medications_conflicts* get_resident_medication_conflict(int medication_id_key);