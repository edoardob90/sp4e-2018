#include "series.hh"

using namespace std;

int computeSeries(int Niterations){
    int sum = 0;
    //cerr << "SUM variable is " << sum << endl;
    for (int i=0; i<=Niterations; ++i) {
        //cerr << "Iteration # " << i << endl;
        sum += i;
        //cerr << "SUM variable is " << sum << endl;
    }
    return sum;
}
