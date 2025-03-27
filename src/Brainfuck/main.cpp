#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <chrono>
#include <string>
#include "BFHeader.h"

int main() {
    std::string input;
    std::smatch match;

    std::string tmp;
    std::string bfcode;
    char mode = 'i';
    bool random = false;

    const static std::regex flagsr(" -[iecral] -?");
    const static std::regex flags(" -[iecral]");

    while (true) {
        std::cin.sync();
        std::getline(std::cin, input);

        if (std::regex_search(input, match, flagsr)) {
            mode = input[match.position() + 2];
            input.erase(match.position(), 6);
            random = true;
        }
        else if (std::regex_search(input, match, flags)) {
            mode = input[match.position() + 2];
            input.erase(match.position(), 3);
        }

        if (input[0] == '\"' && input[input.length() - 1] == '\"') {
            input.erase(0, 1);
            input.erase(input.length() - 1, 1);
        }

        if (input == "exit") {
            return 0;
        }
        else if (input == "help") {
            // print help
            continue;
        }

        std::ifstream file(input);
        if (file.fail()) {
            std::cout << "ERROR: invalid file path/command \"" << input << "\"!\n";
            file.close();
            continue;
        }
        else {
            
            while (getline(file, tmp)) {
                bfcode += tmp;
            }
        }
        file.close();

        switch (mode) {
        case 'i':
            if (loopsCorrect(bfcode)) {
                auto started = std::chrono::high_resolution_clock::now();
                interpreter(bfcode, random, true);
                auto done = std::chrono::high_resolution_clock::now();
                std::cout << '\n' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';
            }
            break;
        case 'a':
            if (loopsCorrect(bfcode)) {
                auto started = std::chrono::high_resolution_clock::now();
                aheadOfTime(bfcode, input += ".cpp", random);
                auto done = std::chrono::high_resolution_clock::now();
                std::cout << '\n' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';
            }
            break;
        case 'e':
            if (loopsCorrect(bfcode)) {
                if (byteGenerator(bfcode, input += ".bfbc", random)) {
                    auto started = std::chrono::high_resolution_clock::now();
                    byteInterpreter(input, true);
                    auto done = std::chrono::high_resolution_clock::now();
                    std::cout << '\n' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';
                }
            }
            break;
        case 'c':
            if (loopsCorrect(bfcode)) {
                auto started = std::chrono::high_resolution_clock::now();
                byteGenerator(bfcode, input += ".bfbc", random);
                auto done = std::chrono::high_resolution_clock::now();
                std::cout << '\n' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';
            }
            break;
        case 'r':
        {
            auto started = std::chrono::high_resolution_clock::now();
            byteInterpreter(input, true);
            auto done = std::chrono::high_resolution_clock::now();
            std::cout << '\n' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';
            break;
        }
        case 'l':
        {
                auto started = std::chrono::high_resolution_clock::now();
                if (loopsCorrect(bfcode)) {
                    std::cout << "Loops inside the file " << input << " are correct.\n";
                }
                auto done = std::chrono::high_resolution_clock::now();
                std::cout << '\n' << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << '\n';
                break;
            }
        }

        mode = 'i';
        random = false;
        tmp.clear();
        bfcode.clear();
    }
}