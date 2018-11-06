#include "csv_reader.hh"
#include "particles_factory_interface.hh"
#include <fstream>
#include <sstream>
/* -------------------------------------------------------------------------- */
CsvReader::CsvReader(const std::string& filename) : filename(filename) {
    // open the input 
    // TODO: this won't work if fstream is not a member !!
    std::ifstream fstream;
    if ( !fstream.is_open() ){
        fstream.open(filename);
    } else {
        std::cerr << "Error opening filename " << filename << std::endl;
    }
}
/* -------------------------------------------------------------------------- */
void CsvReader::read(System& system) { this->compute(system); }
/* -------------------------------------------------------------------------- */

void CsvReader::compute(System& system) {
    std::sstream ss;
    std::string line;
    while (fstream.good()){
        getline(fstream, line);
        ss.clear(); ss<<line;
    }

}

/* -------------------------------------------------------------------------- */
