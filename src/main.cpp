#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Interp.hpp"
#include "argparse.hpp"

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

    auto pArgs = parseArgs(args);

    bool unFuck = vectIncludes(pArgs.flags, std::string{"unfuck"});

    if (vectIncludes(pArgs.flags, std::string{"minify"})) {
        //  Load the code to minify
        auto code = LoadStringFromFile(pArgs.settings["in"].c_str());

        // To store the final string
        std::string finalCode = "";

        // Where to write the output file
        auto writeTo = pArgs.settings["out"];

        // All valid symbols
        auto symbols = BFInterp{false, unFuck}.getRecognizedSymbols();

        // Loop thru each char and determine if we keep it ot not
        for (auto letter : code) {
            if (vectIncludes(symbols, letter)) finalCode += letter;
        }

        // Write it to the specified output dest
        std::ofstream outfile(writeTo);
        outfile << finalCode;
        outfile.close();

    }

    else if (pArgs.text.size() == 0) {
        // Start REPL mode
        printf("REPL started\n");

        BFInterp interp(true, unFuck);

        while(true) {
            std::string inp;
            
            // Print prompt string
            std::cout << ":" << std::flush;
            
            // Get input
            std::cin >> inp;

            interp.Run(inp);
        }
    }

    else if (pArgs.text.size() == 1) {
        printf("Interp started!\n");

        auto code = LoadStringFromFile(args[0].c_str());

        BFInterp interp(false, unFuck);

        interp.Run(code);
    }

    return 0;
}