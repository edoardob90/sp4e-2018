//
// Created by Edoardo Baldi on 23.10.18.
//

#ifndef HOMEWORK2_COMPUTEPI_HH
#define HOMEWORK2_COMPUTEPI_HH

#include "Series.hh"

class ComputePi : public Series {
public:

    // Constructor
    ComputePi();

    // Destructor
    virtual ~ComputePi();

    // Compute method
    double compute (unsigned int N) override;
    double getAnalyticPrediction() override;

};

#endif //HOMEWORK2_COMPUTEPI_HH
