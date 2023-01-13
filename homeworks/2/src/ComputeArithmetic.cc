//
// Created by Edoardo Baldi on 23.10.18.
//

#include "ComputeArithmetic.hh"
#include <cmath>

// Constructor: initialize the result here?
ComputeArithmetic::ComputeArithmetic() : Series("arithmetic") {}

// ComputeArithmetic::~ComputeArithmetic() {}; // "empty" destructor. CLion suggested the following:
ComputeArithmetic::~ComputeArithmetic() = default;

// Compute method: start at current_index and
// add to current_result to avoid re-computing the
// whole series
double ComputeArithmetic::compute(unsigned int N) {
    for (unsigned int i = this->current_index; i <= N; ++i) {
        this->current_result += i;
        this->current_index += 1;
    }
    return this->current_result;
}

double ComputeArithmetic::getAnalyticPrediction() {
    return nan("");
}
