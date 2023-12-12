#include "infusion.h"



void infusion(resident_record resident){
    // Declaring of variables entered by the nurse
    double *stock_solution_strength, *dose_prescribed, *strength_of_solution, *time_in_hours;

    // Declaring of variables calculated
    double total_dose, dose_in_ml, total_amount_solution, total_amount_infusion, drops_pr_min;



    //aquire information from employee
    scan_information(stock_solution_strength, dose_prescribed,
                     strength_of_solution, time_in_hours);

    //check if the strength of the stock solution is in percent
    is_percent(stock_solution_strength);

    //calculate the dose of medicine needed in mg
    total_dose = dose(resident.weight, dose_prescribed);
    printf("The dose for the resident is: %0.3lf mg\n", total_dose);

    //calculate quantity of stock solution needed in ml.
    dose_in_ml = amount_of_stock_solution(total_dose, stock_solution_strength);
    printf("Amount of stock solution needed: %0.3lf ml\n", dose_in_ml);

    //calculate the amount of solution in total
    total_amount_solution = amount_of_solution(total_dose, strength_of_solution);

    //calculate the amount of infusion liquid needed
    total_amount_infusion = amount_of_infusion_liquid(total_amount_solution, dose_in_ml);

    printf("Amount of infusion liquid needed: %0.3lf ml\n", total_amount_infusion);
    printf("Amount of total infusion: %0.3lf ml\n", total_amount_solution);

    //calculate drops pr. min.
    drops_pr_min = speed_of_infusion(total_amount_solution, time_in_hours);
    printf("speed of infusion %0.3lf dr/min\n", drops_pr_min);
}

void scan_information(double* stock_solution_strength, double* dose_prescribed,
                      double* strength_of_solution, double* time_in_hours){
    //get the strength of stock solution
    printf("Enter the strength of the stock solution: \n>");
    scanf("%lf", stock_solution_strength);

    //get prescribed dose in mg/kg
    printf("Enter the prescribed dose in mg/kg: \n>");
    scanf("%lf", dose_prescribed);

    //get the wanted strength of solution after the stock solution is diluted using infusion liquid
    printf("Enter the wanted strength of the solution in mg/ml: \n>");
    scanf("%lf", strength_of_solution);

    //get the number of hours the infusion should last
    printf("Enter number of hours the infusion should last: \n>");
    scanf("%lf", time_in_hours);
}

void is_percent(double* stock_solution_strength){
    //checks if the strength of the stock solution is in %
    char unit;
    do {
        printf("Is the strength in percent? write Y or N \n>");
        scanf(" %c", &unit);
        if (unit == 'Y' || unit == 'y') {
            *stock_solution_strength = *stock_solution_strength / CONVERSION_TO_MGML;
            printf("Strength: %lf mg/mL \n", *stock_solution_strength);
        }
        else if (unit == 'N' || unit == 'n')
            break;
        else
            printf("invalid input \n");
    } while (unit != 'Y' && unit != 'y' && unit != 'N' && unit != 'n');
}

double dose(double resident_weight, double* dose_prescribed){
    return resident_weight * (*dose_prescribed);
}

double amount_of_stock_solution(double stock_solution_dose, double* stock_solution_strength){
    return stock_solution_dose / (*stock_solution_strength);
}

double amount_of_solution(double stock_solution_dose, double* strength_of_infusion){
    return stock_solution_dose / (*strength_of_infusion);
}

double amount_of_infusion_liquid(double total_amount_solution, double total_amount_stock){
    return total_amount_solution - total_amount_stock;
}

double speed_of_infusion(double total_amount_solution, double* hours){
    double speed;
    speed = total_amount_solution / (*hours);
    return speed / CONVERT_FACTOR;
}