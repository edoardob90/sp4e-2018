#include "Series.hh"
#include <ostream>

#ifndef HOMEWORK2_DUMPERSERIES_HH
#define HOMEWORK2_DUMPERSERIES_HH

class DumperSeries {
    public:

	// Constructor
        DumperSeries(Series &s) : series(s) {};

        // Destructor
        virtual ~DumperSeries() {};

    public:

        // Member function declarations
        virtual void dump(std::ostream &os) = 0;
        virtual void setPrecision(unsigned int precision) = 0;

    protected:

	// Member declaration
        Series &series;
};

// Operator definition permitting general ostream use
inline std::ostream &operator <<(std::ostream &stream, DumperSeries &_this) {
    _this.dump(stream);
    return stream;
}

#endif
