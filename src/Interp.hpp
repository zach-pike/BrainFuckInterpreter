#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <iostream>

#include "stdio.h"
#include "math.h"

#define TAPE_SIZE 10000

typedef unsigned char Byte;

class BFInterp {
    private:
        //Tape array
        std::array<Byte, TAPE_SIZE> tape;
        //Current tape position
        size_t tapePos = 0;
        
        bool replOn;
        bool unFuck;

        std::vector<size_t> loopStarts;
    public:
        std::vector<char> getRecognizedSymbols() {
            if (unFuck)
                return std::vector<char>{ '+', '-', '<', '>', '[', ']', '.', ',', '?', '!', '#' };
            else
                return std::vector<char>{ '+', '-', '<', '>', '[', ']', '.', ',' };
        }

        BFInterp(bool replOn, bool unFuck) {
            // Fill tape with all zeros
            tape.fill(0);

            BFInterp::replOn = replOn;
            BFInterp::unFuck = unFuck;
        }

        void HandleExtended(const char command, int& i, std::string& code) {
            switch (command) {
                // My contributions
                    
                // Print raw int of current cell
                case '!': {
                    if (replOn)
                        std::cout << (int)tape[tapePos] << std::endl;
                    else
                        std::cout << (int)tape[tapePos] << std::flush;
                } break;

                case '#': {
                    int i;
                    std::cin >> i;
                    tape[tapePos] = fabs(i);
                } break;
                    
                // For debugging
                case '?': {
                    std::cout 
                    << "[DEBUG] "
                    << "Cell index: "
                    << tapePos
                    << " Current cell value (int): "
                    << (int)tape[tapePos]
                    << std::endl;
                } break;
            }
        }

        void HandleCommand(const char command, int& i, std::string& code) {
            // Handle a command
                switch (command) {
                    
                // Add/Subtract from current tape index
                case '+': {
                    tape[tapePos]++;
                } break;
                case '-': {
                    tape[tapePos]--;
                } break;
                    
                // Increment/Decrement the tape index
                case '>': {
                    if (tapePos < TAPE_SIZE) tapePos++;
                } break;
                case '<': {
                    if (tapePos != 0) tapePos--;
                } break;
                    
                // Print out the char
                case '.': {
                    if (replOn)
                        std::cout << (char)tape[tapePos] << std::endl;
                    else
                        std::cout << (char)tape[tapePos] << std::flush;
                } break;
                    
                // Take one char of input
                case ',': {
                    char inp;
                    std::cin >> inp;
                    tape[tapePos] = inp;
                } break;
                    
                // Start loop
                case '[': {
                    // If value is zero them jump to end of loop
                    if (tape[tapePos] == 0) {
                        size_t jmpTo;
                        size_t openingLoops = 0;

                        for (int j=i; j < code.size(); j++) {
                            if (code[j] == '[') openingLoops++;
                            if (code[j] == ']') openingLoops--;

                            if (code[j] == ']' && openingLoops == 0) {
                                jmpTo = j;

                                break;
                            }
                        }

                        i = jmpTo;
                    }
                } break;
                    
                // Stop loop
                case ']': {
                    // If value is nonzero then jump to the beginning and
                    // continue executing
                    if (tape[tapePos] != 0 ) {
                        // Restart at last loop start
                        size_t jmpTo;
                        size_t closingLoops = 0;

                        for (int j=i; j >= 0; j--) {
                            if (code[j] == ']') closingLoops++;
                            if (code[j] == '[') closingLoops--;

                            if (code[j] == '[' && closingLoops == 0) {
                                jmpTo = j;

                                break;
                            }
                        }

                        i = jmpTo;
                    }
                } break;

                default: {
                    if (unFuck) {
                        HandleExtended(command, i, code);
                    }
                } break;
            }
        }
        
        void Run(std::string& code) {
            // Loop thru chars
            for (int i=0; i < code.length(); i++) {
                // Command to parse
                char command = code[i];

                HandleCommand(code[i], i, code);
            }   
        }
};