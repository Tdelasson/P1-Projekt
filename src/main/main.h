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

// Making a struct type for patient journal data
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

}patient_journal;

// Making a struct type for patient medication data
typedef struct {
    int id_key;
    char first_name[MAX_NAME_LGT];
    char surname[MAX_NAME_LGT];
    // Making space for patients to take multiple medications
    char medication[MAX_MEDICATIONS][MAX_MEDICATION_NAME_LGT];
    char medication_type[MAX_MEDICATIONS][MAX_MEDICATION_TYPE_NAME_LGT];
    char medication_strength[MAX_MEDICATIONS][MAX_MEDICATION_TYPE_NAME_LGT];
    char medication_unit[MAX_MEDICATIONS][MAX_MEDICATION_UNIT_NAME_LGT];

}patient_medications;

typedef struct {
    int id_key;
    char first_name[MAX_NAME_LGT];
    char surname[MAX_NAME_LGT];
    // Making space for patients to take multiple medications
    char medication[MAX_MEDICATIONS][MAX_MEDICATION_NAME_LGT];
    char medication_type[MAX_MEDICATIONS][MAX_MEDICATION_TYPE_NAME_LGT];
    char medication_strength[MAX_MEDICATIONS][MAX_MEDICATION_TYPE_NAME_LGT];
    char medication_unit[MAX_MEDICATIONS][MAX_MEDICATION_UNIT_NAME_LGT];

}medicine_data;

typedef struct {
    int id_key;
    char first_name[MAX_NAME_LGT];
    char surname[MAX_NAME_LGT];
    // Making space for patients to take multiple medications
    char medication[MAX_MEDICATIONS][MAX_MEDICATION_NAME_LGT];
    char medication_type[MAX_MEDICATIONS][MAX_MEDICATION_TYPE_NAME_LGT];
    char medication_strength[MAX_MEDICATIONS][MAX_MEDICATION_TYPE_NAME_LGT];
    char medication_unit[MAX_MEDICATIONS][MAX_MEDICATION_UNIT_NAME_LGT];

}medicine_conflicts;



patient_journal* get_patient_journal(patient_journal patients[]);
patient_medications* patient_journal_medicine(patient_medications patients[]);
