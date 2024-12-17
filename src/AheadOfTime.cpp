#include <iostream>
#include <fstream>
#include "BFHeader.h"

void aheadOfTime(std::string bfcode, std::string path, bool random) {
	path += ".cpp";
	std::ofstream file(path);
	if (file.fail()) {
		std::cout << "ERROR: failed to create a file at the given path \"" << path << "\"!\n";
		return;
	}
	else {
		file
			<< "#include <iostream>\n"
			<< "#include <vector>\n";
		if (random) {
			file << "#include <random>\n";
		}
		file
			<< "int main() {\n";
		if (random) {
			file
				<< "std::random_device seed;\n"
				<< "auto gen = std::mt19937{ seed() };\n"
				<< "auto dist = std::uniform_int_distribution<std::uint16_t>{ 0, 255 };\n";
		}
		file
			<< "static auto cells = std::vector<char>(65536, 0);\n"
			<< "std::uint16_t pointer = 0;";

		for (std::uint32_t i = 0; i <= bfcode.length(); i++) {
			switch (bfcode[i]) {
			case '+':
				file << "++cells[pointer];\n";
				break;
			case '-':
				file << "--cells[pointer];\n";
				break;
			case '>':
				file << "++pointer;\n";
				break;
			case '<':
				file << "--pointer;\n";
				break;
			case '.':
				file << "std::cout << static_cast<char>(cells[pointer]);\n";
				break;
			case ',':
				file << "std::cin >> cells[pointer];\n";
				break;
			case '[':
				file << "while (cells[pointer] != 0) {\n";
				break;
			case ']':
				file << "}\n";
				break;
			case '?':
				if (random) {
					file << "cells[pointer] = dist(gen);\n";
				}
				break;
			}
		}

		file
			<< "    return 0;\n"
			<< "}";
	}
	file.close();
	return;
}