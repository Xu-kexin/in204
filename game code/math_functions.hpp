#pragma once

double abs(double some_double){
    if(some_double>=0) {
        return some_double;
    } else {
        return -some_double;
    }
}

double square(double some_double){
    return some_double*some_double;
}