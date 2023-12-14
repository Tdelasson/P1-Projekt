#include "tests.h"


int main(void){

    // Database tests
    test_scan_resident_database();
    test_get_resident_record_medicine();
    test_get_resident_medication_conflict();
    test_get_medication_details();


    // Pillbox tests
    test_calculate_actual_dose();
    test_showcased_unit();
    test_convert();

    // Infusion tests
    test_dose();
    test_amount_of_stock_solution();
    test_amount_of_solution();
    test_amount_of_infusion_liquid();
    test_speed_of_infusion();


}

// Database tests
void test_scan_resident_database(){
    // Open the resident record file in read mode
    FILE *resident_record_file = fopen("../database_textfiles/resident_record.txt", "r");

    // Check if the file was successfully opened
    if (resident_record_file == NULL) {
        fprintf(stderr, "Error opening resident record file.\n");
        exit(EXIT_FAILURE);
    }

    resident_record resident;
    unsigned long int social_security_number;


    //test_scan_resident_database should return 0 if the resident is not found
    social_security_number = 0000000000;
    assert((scan_resident_database(resident_record_file,&resident,social_security_number)==0));

    //test_scan_resident_database should return 1 if the resident is found
    social_security_number = 1111471111;
    assert((scan_resident_database(resident_record_file,&resident,social_security_number)==1));

    //test if correct data is scanned from database using resident 10049 as example
    social_security_number = 3004651987;
    scan_resident_database(resident_record_file,&resident,social_security_number);
    assert(strcmp(resident.first_name,"Noah") == 0);
    assert(strcmp(resident.surname,"Lewis") == 0);
    assert(resident.apartment_number == 1.11);
    assert(resident.age == 77);
    assert(strcmp(resident.sex,"Male") == 0);
    assert(resident.weight == 100);
    assert(resident.social_security_number == 3004651987);

    //test if correct data is scanned from database using resident 10033 as example
    social_security_number = 3106534973;
    scan_resident_database(resident_record_file,&resident,social_security_number);
    assert(strcmp(resident.first_name,"Mason") == 0);
    assert(strcmp(resident.surname,"Brown") == 0);
    assert(resident.apartment_number == 0.04);
    assert(resident.age == 75);
    assert(strcmp(resident.sex,"Male") == 0);
    assert(resident.weight == 90);
    assert(resident.social_security_number == 3106534973);

}

void test_get_resident_record_medicine(){

    resident_medications medications[MAX_MEDICATIONS];
    int resident_id_key;

    //tests if get_resident_record_medicine returns the correct number of medications
    // for residents 10001, 10004 and 10049
    assert((get_resident_record_medicine(medications,10001)) == 5);
    assert((get_resident_record_medicine(medications,10004)) == 4);
    assert((get_resident_record_medicine(medications,10049)) == 3);

    //tests if get_resident_record_medicine correctly scans the medication
    // from id_key
    resident_id_key = 10001;
    get_resident_record_medicine(medications,resident_id_key);
    // For medications
    assert(medications[0].medication == 20001);
    assert(medications[1].medication == 20002);
    assert(medications[2].medication == 20036);
    assert(medications[3].medication == 20049);
    assert(medications[4].medication == 20035);

    // For total weekly dose
    assert(medications[0].total_weekly_dose == 1750);
    assert(medications[1].total_weekly_dose == 1400);
    assert(medications[2].total_weekly_dose == 1200);
    assert(medications[3].total_weekly_dose == 1000);
    assert(medications[4].total_weekly_dose == 1000);

    // For medication unit
    assert(strcmp(medications[0].medication_unit,"mg") == 0);
    assert(strcmp(medications[1].medication_unit,"mg") == 0);
    assert(strcmp(medications[2].medication_unit,"mg") == 0);
    assert(strcmp(medications[3].medication_unit,"mg") == 0);
    assert(strcmp(medications[4].medication_unit,"mg") == 0);

    // For weekdays
    assert(medications[0].weekdays[0] == 1);
    assert(medications[0].weekdays[1] == 1);
    assert(medications[0].weekdays[2] == 1);
    assert(medications[0].weekdays[3] == 1);
    assert(medications[0].weekdays[4] == 1);
    assert(medications[0].weekdays[5] == 1);
    assert(medications[0].weekdays[6] == 1);

    assert(medications[1].weekdays[0] == 1);
    assert(medications[1].weekdays[1] == 1);
    assert(medications[1].weekdays[2] == 1);
    assert(medications[1].weekdays[3] == 1);
    assert(medications[1].weekdays[4] == 1);
    assert(medications[1].weekdays[5] == 1);
    assert(medications[1].weekdays[6] == 1);

    assert(medications[2].weekdays[0] == 1);
    assert(medications[2].weekdays[1] == 1);
    assert(medications[2].weekdays[2] == 1);
    assert(medications[2].weekdays[3] == 1);
    assert(medications[2].weekdays[4] == 1);
    assert(medications[2].weekdays[5] == 1);
    assert(medications[2].weekdays[6] == 1);

    assert(medications[3].weekdays[0] == 1);
    assert(medications[3].weekdays[1] == 1);
    assert(medications[3].weekdays[2] == 1);
    assert(medications[3].weekdays[3] == 1);
    assert(medications[3].weekdays[4] == 1);
    assert(medications[3].weekdays[5] == 1);
    assert(medications[3].weekdays[6] == 1);

    assert(medications[4].weekdays[0] == 1);
    assert(medications[4].weekdays[1] == 0);
    assert(medications[4].weekdays[2] == 1);
    assert(medications[4].weekdays[3] == 0);
    assert(medications[4].weekdays[4] == 1);
    assert(medications[4].weekdays[5] == 0);
    assert(medications[4].weekdays[6] == 1);

    // For morning dose
    assert(medications[0].morning_dose == 0.50);
    assert(medications[1].morning_dose == 1.00);
    assert(medications[2].morning_dose == 1.00);
    assert(medications[3].morning_dose == 1.00);
    assert(medications[4].morning_dose == 0.00);

    // For afternoon dose
    assert(medications[0].afternoon_dose == 0.50);
    assert(medications[1].afternoon_dose == 0.00);
    assert(medications[2].afternoon_dose == 0.00);
    assert(medications[3].afternoon_dose == 0.00);
    assert(medications[4].afternoon_dose == 0.00);

    // For evening dose
    assert(medications[0].evening_dose == 0.00);
    assert(medications[1].evening_dose == 0.00);
    assert(medications[2].evening_dose == 0.00);
    assert(medications[3].evening_dose == 0.00);
    assert(medications[4].evening_dose == 1.00);



}

void test_get_resident_medication_conflict(){
    medicine_database medicine_details[3];
    int number_of_medications = 3;

    //tests if get_resident_medication_conflict returns true if there is a conflict
    strcpy(medicine_details[0].name,"Warfarin");
    strcpy(medicine_details[1].name,"Levothyroxine");
    strcpy(medicine_details[2].name,"Fluticasone");
    assert((get_resident_medication_conflict(medicine_details,3)) == true);

    strcpy(medicine_details[0].name,"Rosuvastatin");
    strcpy(medicine_details[1].name,"Simvastatin");
    strcpy(medicine_details[2].name,"Fluoxetine");
    assert((get_resident_medication_conflict(medicine_details,3)) == true);


    strcpy(medicine_details[0].name,"Celecoxib");
    strcpy(medicine_details[1].name,"Fluoxetine");
    strcpy(medicine_details[2].name,"Simvastatin");
    //tests if get_resident_medication_conflict returns true if there is a conflict
    assert((get_resident_medication_conflict(medicine_details,3)) == false);

    strcpy(medicine_details[0].name,"Trazodone");
    strcpy(medicine_details[1].name,"Amphetamine");
    strcpy(medicine_details[2].name,"Prednisone");
    //tests if get_resident_medication_conflict returns true if there is a conflict
    assert((get_resident_medication_conflict(medicine_details,3)) == false);

}

void test_get_medication_details() {
    medicine_database medicine_details[MAX_MEDICATIONS];
    resident_medications medications[MAX_MEDICATIONS];
    int number_of_medications;

    //tests if get_medication_details correctly scans the medication details
    medications[0].medication = 20001;
    medications[1].medication = 20020;
    medications[2].medication = 20053;
    number_of_medications = 3;
    get_medication_details(medicine_details, medications, number_of_medications);

    //test if medication details are correctly scanned for medication 20001
    assert(medicine_details[0].id_key == 20001);
    assert(strcmp(medicine_details[0].name,"Aspirin") == 0);
    assert(strcmp(medicine_details[0].type,"Pill") == 0);
    assert(medicine_details[0].strength == 500);
    assert(strcmp(medicine_details[0].unit_of_strength,"mg") == 0);

    //test if medication details are correctly scanned for medication 20020
    assert(medicine_details[1].id_key == 20020);
    assert(strcmp(medicine_details[1].name,"Hydrochlorothiazide") == 0);
    assert(strcmp(medicine_details[1].type,"Pill") == 0);
    assert(medicine_details[1].strength == 25);
    assert(strcmp(medicine_details[1].unit_of_strength,"mg") == 0);

    //test if medication details are correctly scanned for medication 20053
    assert(medicine_details[2].id_key == 20053);
    assert(strcmp(medicine_details[2].name,"Amoxicillin") == 0);
    assert(strcmp(medicine_details[2].type,"Pill") == 0);
    assert(medicine_details[2].strength == 500);
    assert(strcmp(medicine_details[2].unit_of_strength,"mg") == 0);
}

// Pillbox tests
void test_calculate_actual_dose() {
    double actual_morning_dose;
    double actual_noon_dose;
    double actual_evening_dose;

    double actual_weekly_dose, number_of_days;
    resident_medications medications[MAX_MEDICATIONS];
    medicine_database medicine_details[MAX_MEDICATIONS];
    int i;

    //test if calculate_actual_dose correctly calculates the actual dose
    actual_morning_dose = 0.0;
    actual_noon_dose = 0.0;
    actual_evening_dose = 0.0;
    actual_weekly_dose = 1000.0;
    number_of_days = 5.0;
    medications[0].morning_dose = 0.5;
    medications[0].afternoon_dose = 0.0;
    medications[0].evening_dose = 0.5;
    i = 0;
    medicine_details[0].strength = 100;
    calculate_actual_dose(&actual_morning_dose, &actual_noon_dose, &actual_evening_dose,
                          actual_weekly_dose, number_of_days, medications, medicine_details, i);

    // number of pills morning noon and evening should be 1, 0 and 1 respectively
    assert(actual_morning_dose == 1.0);
    assert(actual_noon_dose == 0.0);
    assert(actual_evening_dose == 1.0);


    // Second test
    actual_morning_dose = 0.0;
    actual_noon_dose = 0.0;
    actual_evening_dose = 0.0;
    actual_weekly_dose = 1600.0;
    number_of_days = 4.0;
    medications[0].morning_dose = 0.5;
    medications[0].afternoon_dose = 0.5;
    medications[0].evening_dose = 0.0;
    i = 0;
    medicine_details[0].strength = 50;
    calculate_actual_dose(&actual_morning_dose, &actual_noon_dose, &actual_evening_dose,
                          actual_weekly_dose, number_of_days, medications, medicine_details, i);


    // number of pills morning noon and evening should be 1, 0 and 1 respectively
    assert(actual_morning_dose == 4.0);
    assert(actual_noon_dose == 4.0);
    assert(actual_evening_dose == 0.0);
}

void test_showcased_unit(){
    char strength_type[10];
    medicine_database medicine_details[MAX_MEDICATIONS];
    int i = 0;

    strcpy(medicine_details[0].unit_of_strength,"mg");
    showcased_unit (strength_type, medicine_details, i);
    assert(strcmp(strength_type,"pill") == 0);

    strcpy(medicine_details[0].unit_of_strength,"mg/ml");
    showcased_unit (strength_type, medicine_details, i);
    assert(strcmp(strength_type,"ml") == 0);
}

void test_convert(){
    double dose;
    char from_unit[10];
    char to_unit[10];


    dose = 100;
    strcpy(from_unit,"mg");
    strcpy(to_unit,"mcg");
    dose = convert(dose,from_unit,to_unit);
    assert(dose ==(100*1000));

    dose = 5000;
    strcpy(from_unit,"mcg");
    strcpy(to_unit,"mg");
    dose = convert(dose,from_unit,to_unit);
    assert(dose ==(5000.0/1000));

    dose = 150;
    strcpy(from_unit,"mcg");
    strcpy(to_unit,"mg/ml");
    dose = convert(dose,from_unit,to_unit);
    assert(dose ==(150.0/1000.0));
}


// Infusion tests
void test_dose(){
    double resident_weight, dose_prescribed;

    resident_weight = 100;
    dose_prescribed = 1000;
    assert(dose(resident_weight,&dose_prescribed) == 100000);

    resident_weight = 75;
    dose_prescribed = 250;
    assert(dose(resident_weight,&dose_prescribed) == 75*250);
}

void test_amount_of_stock_solution(){
    double stock_solution_dose, stock_solution_strength;

    stock_solution_dose = 1000;
    stock_solution_strength = 100;
    assert(amount_of_stock_solution(stock_solution_dose,&stock_solution_strength) == 1000.0/100);

    stock_solution_dose = 500;
    stock_solution_strength = 300;
    assert(amount_of_stock_solution(stock_solution_dose,&stock_solution_strength) == 500.0/300.0);
}

void test_amount_of_solution(){
    double stock_solution_dose, strength_of_infusion;

    stock_solution_dose = 1000;
    strength_of_infusion = 100;
    assert(amount_of_solution(stock_solution_dose,&strength_of_infusion) == 1000.0/100);

    stock_solution_dose = 500;
    strength_of_infusion = 300;
    assert(amount_of_solution(stock_solution_dose,&strength_of_infusion) == 500.0/300.0);
}

void test_amount_of_infusion_liquid(){
    double total_amount_solution, total_amount_stock;

    total_amount_solution = 1000;
    total_amount_stock = 100;
    assert(amount_of_infusion_liquid(total_amount_solution,total_amount_stock) == 1000.0-100);

    total_amount_solution = 500;
    total_amount_stock = 300;
    assert(amount_of_infusion_liquid(total_amount_solution,total_amount_stock) == 500.0-300.0);
}

void test_speed_of_infusion(){
    double total_amount_solution, hours;

    total_amount_solution = 1000;
    hours = 5;
    assert(speed_of_infusion(total_amount_solution,&hours) == (1000.0/5)/CONVERT_FACTOR);

    total_amount_solution = 200;
    hours = 8;
    assert(speed_of_infusion(total_amount_solution,&hours) == (200.0/8)/CONVERT_FACTOR);
}