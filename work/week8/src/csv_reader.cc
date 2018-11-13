#include "csv_reader.hh"
#include "particles_factory_interface.hh"

/* -------------------------------------------------------------------------- */
CsvReader::CsvReader(const std::string& filename) : filename(filename) {
    // open the input 
    if ( !input_stream.is_open() ){
        input_stream.open(filename);
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
    while (input_stream.good()){
        getline(fstream, line);
        ss.clear(); // clear the stringstream
        ss<<line; // fill the stream with the current line
        // system.
    }

}

/* -------------------------------------------------------------------------- */
