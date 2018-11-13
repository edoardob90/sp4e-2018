#ifndef __CSV_READER__HH__
#define __CSV_READER__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include <string>
/* I added the following include here
 * I think that this class needs a (private or protected) member for the input strem
 */ 
#include <fstream>
#include <sstream>

//! Read system from csv input file
class CsvReader : public Compute {

  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  //! Construct from filename
  CsvReader(const std::string& filename);

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:
  //! Left here for convenience (calls compute)
  void read(System& system);
  //! Read input file into system
  void compute(System& system);

protected:
  std::string filename;
  std::ifstream input_stream;
};

/* -------------------------------------------------------------------------- */
#endif  //__CSV_READER__HH__
