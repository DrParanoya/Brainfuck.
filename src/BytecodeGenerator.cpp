#include <iostream>
#include <fstream>
#include <string>
#include "BFHeader.h"

bool byteGenerator(const std::string bfcode, std::string path, const bool random) {
	std::ofstream file(path);
	if (file.fail()) {
		std::cout << "ERROR: failed to create a file at \"" << path << "\"!\n";
		return false;
	}
	std::int64_t change = 0;
	std::int64_t move = 0;
	for (std::uint64_t i = 0; i < bfcode.length(); i++) {
		switch (bfcode[i]) {
		case '?':
			if (random) {
				while (bfcode[i] == '?' && i < bfcode.length()) {
					++i;
				}
				file << "rng";
			}
			break;
		case '[':
			file << "slp";
			break;
		case ']':
			file << "elp";
			break;
		case '+':
		case '-':
			while (bfcode[i] == '+' || bfcode[i] == '-') {
				change = bfcode[i] == '+' ? change + 1 : change - 1;
				i = i < bfcode.length() ? i + 1 : i;
			}
			--i;
			file << "chg" << (change < 0 ? "-" + std::to_string((change * -1) % 127) : "+" + std::to_string(change % 127));
			change = 0;
			break;
		case '>':
		case '<':
			while (bfcode[i] == '>' || bfcode[i] == '<') {
				change = bfcode[i] == '>' ? change + 1 : change - 1;
				i = i < bfcode.length() ? i + 1 : i;
			}
			--i;
			file << "mov" << (change < 0 ? "-" + std::to_string(change * -1) : "+" + std::to_string(change));
			change = 0;
			break;
		case '.':
			file << "out";
			break;
		case ',':
			while (bfcode[i] == ',' && i < bfcode.length()) {
				++i;
			}
			file << "inp";
			break;
		}
		file << "\n";
	}

	file.close();
	return true;
}
