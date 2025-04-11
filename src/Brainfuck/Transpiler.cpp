#include <cstdint>
#include <fstream>
#include <iostream>

#include "BFHeader.h"

void transpile_c_cpp(std::string &bfcode, std::string &path, const bool random, const bool cpp) {
	std::int64_t change = 0;
	std::ofstream file(path);
	if (!file.is_open()) {
		std::cout << "ERROR: failed to open file at \"" << path << "\"!\n";
		return;
	}
	else {
		if (cpp) {
			file
				<< "#include <cstdio>\n"
				<< "#include <cstdint>\n";
		}
		else file << "#include <stdio.h>\n"
				  << "#include <stdint.h>\n";
		if (random) {
			if (cpp)
				file
					<< "#include <random>\n"
					<< "std::random_device seed;\n"
					<< "auto gen = std::mt19937{ seed() };\n"
					<< "auto dist = std::uniform_int_distribution<std::uint16_t>{ 0, 255 };\n";
			else {
				file << "#include <stdlib.h>\n";
			}

		}
		file << "uint8_t cells[65536] = {};";
		file << "uint16_t pointer = 0;\n";
		file << "int main() {\n";
		if (random && !cpp) {
			file << "srand(time(NULL));\n";
		}
		file << '\n';
		for (std::size_t i = 0; i < bfcode.length(); i++) {
			switch (bfcode[i]) {
			case '+':
			case '-':
				while (bfcode[i] == '+' || bfcode[i] == '-') {
					change = bfcode[i] == '+' ? change + 1 : change - 1;
					i = i < bfcode.length() ? i + 1 : i;
				}
				--i;
				file << "cells[pointer] += " << change << ";";
				change = 0;
				break;
			case '>':
			case '<':
				while (bfcode[i] == '>' || bfcode[i] == '<') {
					change = bfcode[i] == '>' ? change + 1 : change - 1;
					i = i < bfcode.length() ? i + 1 : i;
				}
				--i;
				file << "pointer += " << change << ";";
				change = 0;
				break;
			case '.':
				file << "putchar(cells[pointer]);";
				break;
			case ',':
				while (bfcode[i] == ',' && i < bfcode.length()) {
					++i;
				}
				file << "cells[pointer] = getchar();";
				break;
			case '[':
				if (i + 2 <= bfcode.length()) {
					if (bfcode.substr(i, 3) == "[-]" || bfcode.substr(i, 3) == "[+]") {
						file << "cells[pointer] = 0;";
						i += 2;
						break;
					}
				}
				file << "while (cells[pointer] != 0) {";
				break;
			case ']':
				file << "}";
				break;
			case '?':
				if (random) {
					while (bfcode[i] == '?' && i < bfcode.length()) {
						++i;
					}
					if (cpp)
						file << "cells[pointer] = dist(gen);";
					else
						file << "cells[pointer] = rand % 256";
				}
				break;
			}
			file << '\n';
		}
		file
			<< "\nreturn 0;\n}";
	}
	file.close();
	return;
}