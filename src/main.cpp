#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "BFHeader.h"

int main() {
    
    while (true) {
        std::string input;
        std::string path;
        std::string bfcode;
        std::uint16_t i = 0;
        char mode = 'i';
        bool random = false;
        std::getline(std::cin, input);
        while (true) {
            if (input.length() == i) {
                break;
            }
            else if ((input[i] == ' ' && input[i + 1] == '-')) {
                if (input[i + 2] == '?') {
                    random == true;
                }
                else if (input[i + 2] == 'i' || input[i + 2] == 'e' || input[i + 2] == 'c' || input[i + 2] == 'r' || input[i + 2] == 'a' || input[i + 2] == 's') {
                    mode = input[i + 2];
                }
                else {
                    std::cout << "Expected an identifier!\n";
                }
                break;
            }
            path = path + static_cast<char>(input[i]);
            ++i;
        }
        ++i;

        std::ifstream file(path);

        if (file.fail()) {
            std::cout << "ERROR: failed to open a file at the given path \"" << path << "\"!\n";
        }
        else {
            while (getline(file, bfcode)) {}
        }
        file.close();
        if (loopsCorrect(bfcode)) {
            switch (mode) {
            case 'i':
                interpreter(bfcode, random);
                break;
            case 'a':
                aheadOfTime(bfcode, path + ".cpp", random);
                break;
            case 'e':
                if (byteGenerator(bfcode, path + ".bfbc", random)) {
                    byteInterpreter(path);
                }
                break;
            case 'c':
                byteGenerator(bfcode, path + ".bfbc", random);
                break;
            case 'r':
                byteInterpreter(path);
                break;
            }
        }

    }
}
