#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
/* -------------------------------------------------------------------------- */

int main(int argc, char ** argv){

    std::ifstream fin("toto.txt");
    if (fin.is_open()){
        std::cout << "Reading file 'toto.txt' ..." << std::endl;
        double x,y,z;
        fin >> x >> y >> z;
        std::cout << "x= "<< x << std::endl << "y= " << y << std::endl << "z= " << z << std::endl;
    } else {
        std::cerr << "File 'toto.txt' not opened or missing!" << std::endl;
        std::ofstream fout("toto.txt");
        fout << "1.0 " << "2.0 " << "3.0 " << std::endl;
        fout.close();
    }

  return EXIT_SUCCESS;
}



