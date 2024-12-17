#include <iostream>
#include <fstream>;
#include <string>
#include "BFHeader.h"

bool byteGenerator(const std::string bfcode, std::string path, const bool random) {
	std::ofstream file(path);
	std::uint64_t change = 0;
	std::uint64_t move = 0;
	if (random) {
		for (std::uint64_t i = 0; i <= bfcode.length(); i++) {
			switch (bfcode[i]) {
			case '?':
				while (bfcode[i + 1] == '?') {
					++i;
				}
				file << "rng";
				break;
			case '[':
				file << "slp";
				break;
			case ']':
				file << "elp";
				break;
			case '+':
			case '-':
				while (bfcode[i + 1] == '+' || bfcode[i] == '-') {
					++i;
					change = bfcode[i] == '+' ? change + 1 : change - 1;
				}
				file << "chg" << (change < 0 ? "-" + std::to_string((change * -1) % 127) : "+" + std::to_string(change % 127));
				change = 0;
				break;
			case '>':
			case '<':
				while (bfcode[i + 1] == '>' || bfcode[i] == '<') {
					++i;
					change = bfcode[i] == '>' ? change + 1 : change - 1;
				}
				file << "mov" << (change < 0 ? "-" + std::to_string(change * -1) : "+" + std::to_string(change));
				change = 0;
				break;
			case '.':
				file << "out";
				break;
			case ',':
				file << "inp";
				break;
			}
			file << "\n";
		}
	}
	else {
		for (std::uint32_t i = 0; i <= bfcode.length(); i++) {
			for (std::uint64_t i = 0; i <= bfcode.length(); i++) {
				switch (bfcode[i]) {
				case '?':
					while (bfcode[i + 1] == '?') {
						++i;
					}
					file << "rng";
					break;
				case '[':
					file << "slp";
					break;
				case ']':
					file << "elp";
					break;
				case '+':
				case '-':
					while (bfcode[i + 1] == '+' || bfcode[i] == '-') {
						++i;
						change = bfcode[i] == '+' ? change + 1 : change - 1;
					}
					file << "chg" << (change < 0 ? "-" + std::to_string((change * -1) % 127) : "+" + std::to_string(change % 127));
					change = 0;
					break;
				case '>':
				case '<':
					while (bfcode[i + 1] == '>' || bfcode[i] == '<') {
						++i;
						change = bfcode[i] == '>' ? change + 1 : change - 1;
					}
					file << "mov" << (change < 0 ? "-" + std::to_string(change * -1) : "+" + std::to_string(change));
					change = 0;
					break;
				case '.':
					file << "out";
					break;
				case ',':
					file << "inp";
					break;
				}
				file << "\n";
			}
		}
	}
	file.close();
	return true;
}
