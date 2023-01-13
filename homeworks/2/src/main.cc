#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
#include <memory>

#include "InputParser.hh"
#include "ComputeArithmetic.hh"
#include "ComputePi.hh"
#include "PrintSeries.hh"
#include "WriteSeries.hh"

// Print help
void help_banner() {
    std::cerr << "USAGE:\n"
              << "  Available options:\n"
              << "      -h: Print this help and exit;\n"
              << "      -t [pi | ari]: Type of series to compute;\n"
              << "         pi = Pi series; ari = Arithmetic series;\n"
              << "      -s [separator]: Delimiter for output file;\n" 
              << "      -n [number]: Upper bound for sum;\n"
              << "      -f [frequency]: Stride with which to print/write the series;\n"
              << "      -o [output]: Prefix of output file for writing the series (optional);\n" 
              << "      -p [precision]: Decimal precision of output (optional).\n" << std::endl;
}

// Function to format the output based on the user inputs
void output_series(Series &series_class, int maxiter, int freq, const std::string &filename, const std::string &separator, unsigned int precision) {

    // If filename supplied, write to that file
    if (!filename.empty()) {
        auto dump_class = std::make_unique<WriteSeries>(series_class, maxiter, freq);

	// Set precision and delimiter
        dump_class->setPrecision(precision);
        dump_class->setSeparator(separator);
        std::cerr << "Outputting to file with prefix '" << filename << "'" << std::endl;
        std::cerr << "# FIELDS: iteration | series result | analytic prediction/error" << std::endl;
        std::string ext;

	// Default to .txt file if separator not a comma or bar
        if (separator == ",") {
            ext = ".csv";
        } else if (separator == "|") {
            ext = ".psv";
        } else {
            ext = ".txt";
        }

	// Write to the output file
        std::ofstream outfile;
        outfile.open(filename + ext);
        dump_class->dump(outfile);
        outfile.close();

    // If no filename supplied, print to screen
    } else {
        auto dump_class = std::make_unique<PrintSeries>(series_class, maxiter, freq);

	// Set precision and output to stdout
        dump_class->setPrecision(precision);
        dump_class->dump(std::cout);
    }
}


int main(int argc, char **argv) {
    // New CLI object
    InputParser cli(argc, argv);
    // Arguments for passed options
    std::string seriesType, filename, separator;
    unsigned int freq, maxiter, precision;
    // Parse command line
    // Help?
    // Last argument of getCommandOption specifies if an option is optional (true) or compulsory (false, default)
    bool fhelp = cli.commandOptionExists("-h");
    bool fok =  cli.getOptionArgument("-t", seriesType) &&
                cli.getOptionArgument("-f", freq) &&
                cli.getOptionArgument("-n", maxiter) &&
                cli.getOptionArgument("-s", separator) &&
                cli.getOptionArgument("-p", precision, true) &&
                cli.getOptionArgument("-o", filename, true);

    if ( fhelp || ! fok ) { help_banner(); return EXIT_SUCCESS; }

    // Invalid input series type
    if (seriesType != "pi" && seriesType != "ari") {
        std::cerr << "Type of series '" << seriesType << "' unknown!" << std::endl;
        help_banner();
        return EXIT_FAILURE;

    // Do arithmetic series
    } else if (seriesType == "ari") {
        auto series_class = std::make_unique<ComputeArithmetic>();
        output_series(*series_class, maxiter, freq, filename, separator, precision);

    // Do pi series
    } else {
        auto series_class = std::make_unique<ComputePi>();
        output_series(*series_class, maxiter, freq, filename, separator, precision);
    }

    return EXIT_SUCCESS;
} 
