#include "../pillbox/pillbox.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>

// Database tests
void test_get_resident_record_medicine();
void test_scan_resident_database();
void test_get_resident_medication_conflict();
void test_get_medication_details();

// Pillbox tests
void test_calculate_actual_dose();
void test_convert();

// Infusion tests
void test_dose();
void test_amount_of_stock_solution();
void test_amount_of_solution();
void test_amount_of_infusion_liquid();
void test_speed_of_infusion();