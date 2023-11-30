#include <stdio.h>
#include <stdlib.h>

// Defining constants used in functions
#define MAX_PATIENTS 50
#define MAX_NAME_LGT 50
#define MAX_MEDICATIONS 15 // TODO: Dynamic allocation
#define MAX_MEDICATION_NAME_LGT 50
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
}nursing_home_personnel;

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
    int id_key;
    char first_name[MAX_NAME_LGT];
    char surname[MAX_NAME_LGT];
    // Making space for residents to take multiple medications
    char medication[MAX_MEDICATIONS][MAX_MEDICATION_NAME_LGT];
    char medication_type[MAX_MEDICATIONS][MAX_MEDICATION_TYPE_NAME_LGT];
    char medication_strength[MAX_MEDICATIONS][MAX_MEDICATION_TYPE_NAME_LGT];
    char medication_unit[MAX_MEDICATIONS][MAX_MEDICATION_UNIT_NAME_LGT];

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

Nursing_Home_personnel* get_staff_record(staff_record staffs[]);
resident_record* get_resident_record(resident_record residents[]);
resident_medications* resident_record_medicine(resident_medications residents[]);
