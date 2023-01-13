#include <iostream>
#include <iomanip>
#include <cmath>
#include "PrintSeries.hh"

// Constructor definition
PrintSeries::PrintSeries(Series &s, int m, int f) : DumperSeries(s), maxiter(m), freq(f), precision(6) {}

// Destructor definition
PrintSeries::~PrintSeries() = default;

// Set precision if valid value specified by user
void PrintSeries::setPrecision(unsigned int p) {
    if (p > 0) {
        this->precision = p;
    }
}

// Print to the ostream
void PrintSeries::dump(std::ostream &os) {
    
    // Initialize partial sum and analytical prediction
    double Sn;
    double ap = this->series.getAnalyticPrediction();

    // Compute series sum and print to ostream
    // with tab separator
    std::cerr << "# FIELDS: iteration | series result | analytic prediction/error" << std::endl;
    for (int i = 1; i <= this->maxiter; i += this->freq) {
        Sn = this->series.compute(i);
        os  << i << "\t"
            << std::setprecision(this->precision)
            << Sn << "\t";

	// If analytical prediction exists, 
	// print error to the ostream
        if (!std::isnan(ap)) {
            os << "\t" << ap-Sn;
        }
        os << std::endl; 
    }
}
