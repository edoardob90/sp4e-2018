#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "WriteSeries.hh"

// Constructor definition
WriteSeries::WriteSeries(Series &s, int m, int f) : DumperSeries(s), maxiter(m), freq(f), separator("\t"), precision(6) {}

// Destructor definition
WriteSeries::~WriteSeries() = default;

// Set precision if valid value specified by user
void WriteSeries::setPrecision(unsigned int p) {
    if (p > 0) {
        this->precision = p;
    }
}

// Set separator if supplied by user;
// otherwise defaults to tab
void WriteSeries::setSeparator(std::string s) {
    if (!s.empty()) {
        this->separator = s;
    }
}

// Write to the ostream
void WriteSeries::dump(std::ostream &os) {

    // Initialize partial sum and analytical prediction
    double ap = this->series.getAnalyticPrediction();
    double Sn;

    // Compute series and print to ostream
    // with custom separator
    for (int i = 1; i < this->maxiter; i += this->freq) {
        Sn = this->series.compute(i);
        os << i << this->separator 
            << std::setprecision(this->precision) 
            << Sn;

	// If analytical prediction exists,
	// print the prediction to the ostream
        if (!std::isnan(ap)) {
            os << this->separator << ap;
        }
        os << std::endl;
    }
}
