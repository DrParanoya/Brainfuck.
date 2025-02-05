#include <iostream>
#include <fstream>
#include "BFHeader.h"

void aheadOfTime(const std::string bfcode, const std::string path, const bool random) {
	std::int64_t change = 0;
	std::ofstream file(path);
	if (file.fail()) {
		std::cout << "ERROR: failed to create a file at \"" << path << "\"!\n";
		return;
	}
	else {
		file
			<< "#include <iostream>\n"
			<< "#include <array>\n";
		if (random) {
			file << "#include <random>\n";
		}
		file
			<< "int main() {\n";
		if (random) {
			file
				<< "std::random_device seed;\n"
				<< "auto gen = std::mt19937{ seed() };\n"
				<< "auto dist = std::uniform_int_distribution<std::uint16_t>{ 0, 127 };\n";
		}
		file
			<< "static std::array<uint8_t, 65536> cells{};\n"
			<< "std::uint16_t pointer = 0;\n";

		for (std::uint32_t i = 0; i < bfcode.length(); i++) {
			switch (bfcode[i]) {
			case '+':
			case '-':
				while (bfcode[i] == '+' || bfcode[i] == '-') {
					change = bfcode[i] == '+' ? change + 1 : change - 1;
					i = i < bfcode.length() ? i + 1 : i;
				}
				--i;
				file << "cells[pointer] += " << change << ";\n";
				change = 0;
				break;
			case '>':
			case '<':
				while (bfcode[i] == '>' || bfcode[i] == '<') {
					change = bfcode[i] == '>' ? change + 1 : change - 1;
					i = i < bfcode.length() ? i + 1 : i;
				}
				--i;
				file << "pointer += " << change << ";\n";
				change = 0;
				break;
			case '.':
				file << "std::cout << static_cast<char>(cells[pointer] & 127);\n";
				break;
			case ',':
				while (bfcode[i] == ',' && i < bfcode.length()) {
					++i;
				}
				file << "cells[pointer] = std::getchar();\n";
				break;
			case '[':
				file << "while (cells[pointer] % 128 != 0) {\n";
				break;
			case ']':
				file << "}\n";
				break;
			case '?':
				if (random) {
					while (bfcode[i] == '?' && i < bfcode.length()) {
						++i;
					}
					file << "cells[pointer] = dist(gen);\n";
				}
				break;
			}
		}
		file
			<< "return 0;\n"
			<< "}";
	}
	file.close();
	return;
}
