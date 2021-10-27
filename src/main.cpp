#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Interp.hpp"

std::string LoadStringFromFile(const char* filename) {
    std::stringstream ss;
    ss << std::ifstream(filename).rdbuf();
    
    return ss.str();
}

template <typename T>
bool vectIncludes(const std::vector<T>& haystack, const T needle) {
    return std::count(haystack.begin(), haystack.end(), needle) > 0;
}

int main(int _argc, const char** _args) {
    auto args = std::vector<std::string>{ _args + 1, _args + _argc };

    if (args[0] == "--minify") {
        // check if we have enough arguments
        if (args.size() < 3) return 1;

        //  Load the code to minify
        auto code = LoadStringFromFile(args[1].c_str());

        // To store the final string
        std::string finalCode = "";

        // Where to write the output file
        auto writeTo = args[2];

        // All valid symbols
        auto symbols = BFInterp::getRecognizedSymbols();

        // Loop thru each char and determine if we keep it ot not
        for (auto letter : code) {
            if (vectIncludes(symbols, letter)) finalCode += letter;
        }

        // Write it to the specified output dest
        std::ofstream outfile(writeTo);
        outfile << finalCode;
        outfile.close();

    }
    else if (args[0] == "-repl") {
        // To implement repl later
    }
    else {
        auto code = LoadStringFromFile(args[0].c_str());
        printf("Interp started!\n");
        
        BFInterp interp(code);
        interp.go();
    }

    return 0;
}