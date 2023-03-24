#pragma once

#include <math.h>

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

double square_euclidean_distance(double x1, double y1, double x2, double y2){
    return (square(x1 - x2) + square(y1 - y2));
}
double euclidean_distance(double x1, double y1, double x2, double y2){
    return sqrt(square_euclidean_distance(x1, y1, x2, y2));
}

double mod(double some_double, double the_modulo) { // TODO: The modulo must be positive?
    if(some_double<0) {
        return some_double - (int)((some_double / the_modulo)-1) * the_modulo;
    } else {
        return some_double - (int)((some_double / the_modulo)) * the_modulo;
    } // Result is positive.
}

double angle_between(double x1, double y1, double x2, double y2){
    double dx = x2 - x1;
    double dy = y2 - y1;
    return atan2(dy, dx) * 180 / M_PI;
}