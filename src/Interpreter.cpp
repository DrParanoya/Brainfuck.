#include <array>
#include <iostream>
#include <random>
#include <algorithm>
#include "BFHeader.h"

void interpreter(const std::string bfcode, const bool random, const bool clear) {
	std::string loopCode; 
	std::int64_t change = 0;
	static std::uint16_t pointer = 0;
	static std::array<uint8_t, 65536> cells{};
	if (clear) {
		std::fill(cells.begin(), cells.end(), 0);
		pointer = 0;
		loopCode.clear();
	}

	std::random_device seed;
	auto gen = std::mt19937{ seed() };
	auto dist = std::uniform_int_distribution<std::uint16_t>{ 0, 127 };

	for (std::uint32_t i = 0; i < bfcode.length(); i++) {
		switch (bfcode[i]) {
		case '+':
		case '-':
			while (bfcode[i] == '+' || bfcode[i] == '-') {
				change = bfcode[i] == '+' ? change + 1 : change - 1;
				i = i < bfcode.length() ? i + 1 : i;
			}
			--i;
			cells[pointer] += change;
			change = 0;
			break;
		case '>':
		case '<':
			while (bfcode[i] == '>' || bfcode[i] == '<') {
				change = bfcode[i] == '>' ? change + 1 : change - 1;
				i = i < bfcode.length() ? i + 1 : i;
			}
			--i;
			pointer += change;
			change = 0;
			break;
		case '.':
			std::cout << static_cast<char>(cells[pointer] & 127);
			break;
		case ',':
			while (bfcode[i] == ',' && i < bfcode.length()) {
				++i;
			}
			cells[pointer] = std::getchar();
			break;
		case '[':
			++i;
			while (bfcode[i] != ']') {
				loopCode += bfcode[i];
				++i;
			}
			while (cells[pointer] != 0) {
				interpreter(loopCode, random);
			}
			loopCode.clear();
			break;
		case '?':
			if (random) {
				while (bfcode[i] == '?' && i < bfcode.length()) {
					++i;
				}
				cells[pointer] = dist(gen);
			}
			break;
		}
	}
}
