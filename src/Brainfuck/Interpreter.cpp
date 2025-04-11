#include <algorithm>
#include <array>
#include <iostream>
#include <random>

#include "BFHeader.h"

void interpreter(std::string& bfcode, const bool random, const bool clear) {
	std::string loopCode;
	std::uint16_t level = 0;
	static std::uint16_t pointer = 0;
	static std::uint8_t cells[65536] = {};
		if (clear) {
			for (std::uint8_t &c : cells)
				c = 0;
			pointer = 0;
			loopCode.clear();
		}

	std::random_device seed;
	auto gen = std::mt19937{ seed() };
	auto dist = std::uniform_int_distribution<std::uint16_t>{ 0, 255 };
	for (std::uint32_t i = 0; i < bfcode.length(); i++) {
		switch (bfcode[i]) {
		case '+':
			cells[pointer]++;
			break;
		case '-':
			cells[pointer]--;
			break;
		case '>':
			pointer++;
			break;
		case '<':
			pointer--;
			break;
		case '.':
			putchar(cells[pointer]);
			break;
		case ',':
			cells[pointer] = getchar();
			break;
		case '[':
			++i;
			if (i + 1 < bfcode.length()) {
				if (bfcode.substr(i, 2) == "-]" || bfcode.substr(i, 2) == "+]") {
					cells[pointer] = 0;
					++i;
					break;
				}
			}
			while (true) {
				loopCode += bfcode[i];
				if (bfcode[i] == '[') {
					++level;
				}
				else if (bfcode[i] == ']') {
					if (level == 0) {
						break;
					}
					--level;
				}
				++i;
			}
			while (cells[pointer] != 0) {
				interpreter(loopCode, random);
			}
			loopCode.clear();
			break;
		case '?':
			if (random) {
				cells[pointer] = dist(gen);
			}
			break;
		}
	}
}