//
// Created by Edoardo Baldi on 23.10.18.
// Very simple input parser
//

#ifndef HOMEWORK2_INPUTPARSER_HH
#define HOMEWORK2_INPUTPARSER_HH

#include <algorithm>
#include <string>
#include <vector>

class InputParser {
private:
    std::vector<std::string> options;

public:
    InputParser (int argc, char **argv);

    // Check & get an option's argument
    bool getOptionArgument (const std::string &option, std::string &option_argument, bool is_optional) const;
    bool getOptionArgument (const std::string &option, unsigned int &option_argument, bool is_optional) const;

    // Check if a given option exist
    bool commandOptionExists (const std::string &option) const;
};

// Constructor: should fill-up the options vector with command-line arguments
InputParser::InputParser(int argc, char **argv) {
    for (unsigned int i = 1; i < argc; ++i){
        this->options.push_back(std::string(argv[i]));
    }
}

// Returns true if a given option is present
bool InputParser::commandOptionExists(const std::string &option) const {
    // std::begin() and std::end() again return two iterators
    return std::find(this->options.begin(), this->options.end(), option) != this->options.end();
}

// A couple of overloaded versions of getOptionArgument
// 1) if the option argument is a string
bool InputParser::getOptionArgument(const std::string &option, std::string &option_argument, bool is_optional = false) const {
    auto elem = std::find(this->options.begin(), this->options.end(), option);
    if (elem != this->options.end() && ++elem != this->options.end()) {
        // This is a workaround if a \t is passed as separator
        if ( *elem == "\\t" ) {
            option_argument = "\t";
            return true;
        } else { option_argument = *elem; return true; }
    } else {
        return (is_optional || false);
    }
}

// 2) if the option argument is an integer
bool InputParser::getOptionArgument(const std::string &option, unsigned int &option_argument, bool is_optional = false) const {
    auto elem = std::find(this->options.begin(), this->options.end(), option);
    if (elem != this->options.end() && ++elem != this->options.end()) {
        try { // Attempt string-to-integer conversion
            option_argument = std::stoi(*elem);
            return true;
        } catch (const std::invalid_argument &err) {
            std::cerr << "ERROR: Option " << option << " accepts only integer values!\n"
                      << err.what() << std::endl;
            return false;
        }
    } else {
        return (is_optional || false);
    }
}


#endif //HOMEWORK2_INPUTPARSER_HH
