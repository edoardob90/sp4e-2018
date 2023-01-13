#include "DumperSeries.hh"

#ifndef HOMEWORK2_PRINTSERIES_HH
#define HOMEWORK2_PRINTSERIES_HH

class PrintSeries : public DumperSeries {
    public:
        // Constructor
        PrintSeries(Series &s, int m, int f);

        // Desctructor
        virtual ~PrintSeries();

    private:

	// Attribute declarations
        int freq;
        int maxiter;
        unsigned int precision;

    public:

	// Member function declarations
        void dump(std::ostream &os) override;
        void setPrecision(unsigned int precision) override;
};

#endif
