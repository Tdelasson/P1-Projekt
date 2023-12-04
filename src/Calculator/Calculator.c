#include "Calculator.h"
#include <stdio.h>
#include <stdlib.h>

int medicine_calculator(){
    
}

int name_calculator(){

}

int unit_calculator(double dose, char rm_unit, char md_unit){
    int rm_name, rm_strength;
    int md_name, md_strength;

    if (rm_unit == 'm' && md_unit == 'g') {
        return dose / 1000.0; // mg to g
    } else if (rm_unit == 'g' && md_unit == 'm') {
        return dose * 1000.0; // g to mg
    } else if (rm_unit == 'm' && md_unit == 'c') {
        return dose * 1000.0; // mg to mcg
    } else if (rm_unit == 'c' && md_unit == 'm') {
        return dose / 1000.0; // mcg to mg
    } else if (rm_unit == 'g' && md_unit == 'c') {
        return dose * 1000000.0; // g to mcg
    } else if (rm_unit == 'c' && md_unit == 'g') {
        return dose / 1000000.0; // mcg to g
    } else {
        printf("Invalid conversion!\n");
        return -1; // Invalid conversion
    }
    
    
    //her er styrken på den medicin patienten skal have og det som plejehjemmet har ens
    if ((rm_name && rm_strength && rm_unit)== (md_name && md_strength && md_unit)) {
        return 1;
    }

}


int strength_calculator(){
    
}
