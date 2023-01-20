#pragma once

double max(double a_double, double another_double) {
    if(a_double>another_double) {
        return a_double;
    } else {
        return another_double;
    }
}

double min(double a_double, double another_double) {
    if(a_double<another_double) {
        return a_double;
    } else {
        return another_double;
    }
}

double abs(double some_double){
    if(some_double>=0) {
        return some_double;
    } else {
        return -some_double;
    }
}

double abs_min(double a_double, double another_double) { // That whose absolute value is minimal
    if(abs(a_double) < abs(another_double)) {
        return a_double;
    } else {
        return another_double;
    }
}

double square(double some_double){
    return some_double*some_double;
}


double mod(double some_double, double the_modulo) { // TODO: The modulo must be positive?
    if(some_double<0) {
        return some_double - (int)((some_double / the_modulo)-1) * the_modulo;
    } else {
        return some_double - (int)((some_double / the_modulo)) * the_modulo;
    } // Result is positive.
}