//
// Created by Edoardo Baldi on 23.10.18.
//

#ifndef HOMEWORK2_COMPUTEARITHMETIC_HH
#define HOMEWORK2_COMPUTEARITHMETIC_HH

#include "Series.hh"

class ComputeArithmetic : public Series {
public:

    // Constructor
    ComputeArithmetic();

    // Destructor
    virtual ~ComputeArithmetic();

    // Compute method
    double compute (unsigned int N) override;
    double getAnalyticPrediction() override;

};

#endif //HOMEWORK2_COMPUTEARITHMETIC_HH
