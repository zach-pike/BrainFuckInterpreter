#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <iostream>

#include "stdio.h"

#define TAPE_SIZE 10000

class BFInterp {
    private:
        //Tape array
        std::array<int, TAPE_SIZE> tape;
        //Current tape position
        size_t tapePos = 0;
        
        //string holding code
        std::string code;
        
        // Stuff for looping
        std::vector<size_t> loopStarts;
    public:
        static std::vector<char> getRecognizedSymbols() {
            return std::vector<char>{ '+', '-', '<', '>', '[', ']', '.', ',', '?', '!' };
        }

        BFInterp(std::string code) {
            //Store code for later
            BFInterp::code = code;
            
            // Fill tape with all zeros
            tape.fill(0);
        }
        
        void go() {
            // Loop thru chars
            for (int i=0; i < code.length(); i++) {
                // Command to parse
                char command = code[i];
                
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
                        tapePos++;
                    } break;
                    case '<': {
                        tapePos--;
                    } break;
                    
                    // Print out the char
                    case '.': {
                        std::cout << (char)tape[tapePos] << std::flush;
                    } break;
                    
                    // Take one char of input
                    case ',': {
                        char inp;
                        std::cin >> inp;
                        tape[tapePos] = (int)inp;
                    } break;
                    
                    // Start loop
                    case '[': {
                        // Add the loop start to the stack
                        loopStarts.push_back(i);
                    } break;
                    
                    // Stop loop
                    case ']': {
                        if (tape[tapePos] != 0 ) {
                            // Restart at last loop start
                            i = loopStarts[loopStarts.size() - 1];   
                        }
                        else {
                            // Pop the loop start off the stack
                            loopStarts.pop_back();
                        }
                    } break;
                    
                    // My contributions
                    
                    // Print raw int of current cell
                    case '!': {
                        std::cout << tape[tapePos] << std::flush;
                    } break;
                    
                    // For debugging
                    case '?': {
                        std::cout 
                        << "[DEBUG] "
                        << "Cell index: "
                        << tapePos
                        << " Current cell value (int): "
                        << tape[tapePos]
                        << std::endl;
                    } break;
                }
            }   
        }
};