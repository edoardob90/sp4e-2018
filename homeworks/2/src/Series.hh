//
// Created by Edoardo Baldi on 23.10.18.
//

#ifndef HOMEWORK2_SERIES_HH
#define HOMEWORK2_SERIES_HH

#include <string>
#include <iostream>

class Series {
private:
    std::string series_kind;

public:
    /* My version of this constructor was
     *   Series(const std::string &series_choice) : series_kind(series_choice) {};
     * but Clang-tidy suggested to pass-by-value and use std::move. Why?
     * It also suggested to declare the constructor as 'explicit'. Why??
     */
    explicit Series(std::string series_choice) : series_kind(std::move(series_choice)) {
        current_result = 0.;
        current_index = 1;
        std::cerr << "Computing '" << this->series_kind << "' series" <<  std::endl;

    }

    virtual double compute(unsigned int N) = 0;
    virtual double getAnalyticPrediction() = 0;

    // Series kind:
    // if I want to access this from the main, I cannot label it as protected (?)
    //std::string series_kind;

    double current_result;
    unsigned int current_index;
};

#endif //HOMEWORK2_SERIES_HH
