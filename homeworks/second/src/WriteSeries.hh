#include "DumperSeries.hh"
#include <string>
#include <fstream>

#ifndef HOMEWORK2_WRITESERIES_HH
#define HOMEWORK2_WRITESERIES_HH

class WriteSeries : public DumperSeries {
    public:
        // Constructor
        WriteSeries(Series &s, int m, int f);

        // Destructor
        virtual ~WriteSeries();

    private:

	// Attribute declarations
        int maxiter;
        int freq;
        std::string separator;
        unsigned int precision;

    public:

	// Member function declarations
        void setSeparator(std::string s); 
	void dump(std::ostream &os) override;
        void setPrecision(unsigned int precision) override;
};

#endif
