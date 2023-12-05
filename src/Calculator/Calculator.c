#include "Calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

double convert(double dose, const char *from_unit, const char *to_unit);
int strength_calculator();
int name_calculator();

int main(void){

    char mg[] = "mg", mcg[] = "mcg", g[] = "g", ml[] = "ml", l[] = "l", mcl[] = "mcl";

    char mgml[] = "mg/ml", mgmcl[] = "mg/mcl", gml[] = "g/ml", gmcl[] = "g/mcl", gl[] = "g/l";

    char vw[] = "%v/w";

    double dose = 20;

    convert(dose, vw, gml);
    convert(dose, gml, gl);

}


double convert(double dose, const char *from_unit, const char *to_unit) {
    struct Conversion {
        const char *unit_pair;
        double multiplier;
    };

    struct Conversion conversions[] = {
            { "mg->g", 0.001 }, { "g->mg", 1000.0 },
            { "mg->mcg", 1000.0 }, { "mcg->mg", 0.001 },
            { "g->mcg", 1000000.0 }, { "mcg->g", 0.000001 },
            { "ml->l", 0.001 }, { "l->ml", 1000.0 },
            { "ml->mcl", 1000.0 }, { "mcl->ml", 0.001 },
            { "l->mcl", 1000000.0 }, { "mcl->l", 0.000001 },
            {"mg/ml->g/l", 0.001}, {"g/l->mg/ml", 1000.0},
            {"g/ml->g/l", 1000.0}, {"g/l->g/ml", 0.001},

            // Add more conversions as needed
    };

    for (int i = 0; i < sizeof(conversions) / sizeof(conversions[0]); ++i) {
        char unit_pair_copy[strlen(conversions[i].unit_pair) + 1]; // Creating a copy of unit_pair
        strcpy(unit_pair_copy, conversions[i].unit_pair);

        char *from_token = strtok(unit_pair_copy, "->");
        char *to_token = strtok(NULL, "->");

        if (from_token != NULL && to_token != NULL) {
            if (strcmp(from_unit, from_token) == 0 && strcmp(to_unit, to_token) == 0) {
                double result = dose * conversions[i].multiplier;
                printf("Convert %   lf %s to %s: %lf %s\n", dose, from_unit, to_unit, result, to_unit);
                return result;            }
        }
    }
    printf("Invalid conversion!\n");
    return -1; // Invalid conversion
}

int infusion(){
    // {"%v/w->g/ml", 1.0};
    // {"%v/v->g/g", 1.0};
    // {"%w/w->ml/ml"};
}
