#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "BFHeader.h"

int main() {
    std::string input;
    std::smatch match;

    std::string tmp;
    std::string bfcode;
    char mode = 'i';
    bool cpp = false;
    bool random = false;

    const static std::regex flagsr(" -[ialc] -?");
    const static std::regex flags(" -[ialc]");

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
            std::cout <<
"Usage:\nEnter a filepath. If no flags are specified, it will be treated as a brainfuck source file and interpretet.\n"      <<
"The following flags are valid: -i -a -l -c -?\n\n-i\nSets the mode to interpreting.\n\n-a\nTranspiles brainfuck to C/C++.\n"<<
"C++ is only recommended for true randomness (std::random_device), because C tends to be slightly faster.\n\n"               <<
"-l\nChecks if the loops inside a Brainfuck source file are balanced. Runs automatically with every other mode.\n\n"         <<
"-c\nRemoves every non-brainfuck character inside a source file. Can improve performance on heavily commented programs\n\n." <<
"-?\nEvery \'?\' inside brainfuck source files will set the current cell with to random value.\n\n";
            continue;
        }

        std::ifstream file(input);
        if (!file.is_open()) {
            std::cout << "ERROR: failed to open file at \"" << input << "\"!\n";
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
                auto started = std::chrono::steady_clock::now();
                interpreter(bfcode, random, true);
                auto done = std::chrono::steady_clock::now();
                std::cout
                    << "\nTook " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count()
                    << " milliseconds.\n";
            }
            break;
        case 'a':
            if (loopsCorrect(bfcode)) {
                auto started = std::chrono::steady_clock::now();
                transpile_c_cpp(bfcode, input += (cpp ? ".cpp" : ".c"), random, cpp);
                auto done = std::chrono::steady_clock::now();
                std::cout
                    << "Took " << std::chrono::duration_cast<std::chrono::microseconds>(done - started).count()
                    << " microseconds.\n";
            }
            break;
        case 'l':
        {
            auto started = std::chrono::steady_clock::now();
            if (loopsCorrect(bfcode)) {
                std::cout << "Loops inside the file \"" << input << "\" are correct.\nTook ";
            }
            auto done = std::chrono::steady_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::microseconds>(done - started).count() << " microseconds.\n";
        }
        break;
        case 'c':
        {
            auto started = std::chrono::steady_clock::now();
            cleanup(bfcode);
            std::size_t found = input.find_last_of("/\\");
            std::ofstream cleaned_up(input.substr(0, found + 1) + "clean_" + input.substr(found + 1));
            if (!cleaned_up.is_open()) {
                std::cout
                    << "ERROR: failed to open file at \"" << input.substr(0, found + 1) << "clean_"
                    << input.substr(found + 1) << "\"!\n";
            }
            cleaned_up << bfcode;
            cleaned_up.close();
            auto done = std::chrono::steady_clock::now();
            std::cout
                << '\"' << input << "\" was cleaned up!\nTook "
                << std::chrono::duration_cast<std::chrono::microseconds>(done - started).count()<< " microseconds.\n";
        }
        break;
        }

        mode = 'i';
        random = false;
        tmp.clear();
        bfcode.clear();
        input.clear();
    }
}