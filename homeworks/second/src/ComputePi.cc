//
// Created by Edoardo Baldi on 23.10.18.
//

#include <math.h> // sqrt and pow functions
#include "ComputePi.hh"
#include <iostream>

// Constructor
ComputePi::ComputePi() : Series("Pi") {}

//Destructor
ComputePi::~ComputePi() = default;

// Compute method: start at current_index and
// add to current_result to avoid re-computing the
// whole series
double ComputePi::compute(unsigned int N) {
    for (unsigned int i = this->current_index; i <= N; ++i) {
        // I think that the usage of static_cast here is safe
        this->current_result += 6./ pow(static_cast<double>(i), 2.) ;
        this->current_index += 1;
    }
    return sqrt(this->current_result);
}

double ComputePi::getAnalyticPrediction() {
    return M_PI;
}

