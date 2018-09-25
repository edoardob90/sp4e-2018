#include <cstdlib>
#include <iostream>
#include "series.hh"
/* -------------------------------------------------------------------------- */

using namespace std;

int main(int argc, char ** argv){
    int maxN = atoi(argv[1]);
    cout << "Will compute the sum up to " << maxN << endl;
    cout << "Hello, the result is: " << computeSeries(maxN) << endl;
    return EXIT_SUCCESS;
}
