#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <array>
/* -------------------------------------------------------------------------- */

int main(int argc, char ** argv){

    std::ifstream fin("toto.txt");
    if (fin.is_open()){
        std::cout << "Reading file 'toto.txt' ..." << std::endl;
        std::array<double, 3> coord;
        fin >> coord[0] >> coord[1] >> coord[2];
        std::cout << "x= "<< coord[0] << std::endl << "y= " << coord[1] << std::endl << "z= " << coord[2] << std::endl;
    } else {
        std::cerr << "File 'toto.txt' not opened or missing!" << std::endl;
        std::ofstream fout("toto.txt");
        fout << "1.0 " << "2.0 " << "3.0 " << std::endl;
        fout.close();
    }

  return EXIT_SUCCESS;
}



