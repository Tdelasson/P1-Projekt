#include <stdio.h>

// Defining constants used in functions
#define CONVERT_FACTOR 3
#define CONVERSION_TO_MGML 100.00

//gets information from user
void scan_information(double* stock_solution_strength, double* dose_prescribed,
                      double* strength_of_solution, double* time_in_hours);

//checks if the strength of the stock solution is in percent
void is_percent(double* stock_solution_strength);

//calculates the dosage of mg/kg.
double dose(double resident_weight, double* dose_prescirbed);

//calculates quantity of stock solution needed
double amount_of_stock_solution(double stock_solution_dose, double* stock_solution_strength);

//calculates total of end solution (infusion liquid and stock solution combined)
double amount_of_solution(double stock_solution_dose, double* strength_of_infusion);

//calculates the amount of infusion liquid needed
//the input parameters in the following function will come from the two functions above.
double amount_of_infusion_liquid(double total_amount_solution, double total_amount_stock);

//Calculates speed for infusion in dr/min
double speed_of_infusion(double total_amount_solution, double* hours);