#include <algorithm>
#include <iostream>

#include "BFHeader.h"

bool loopsCorrect(std::string &bfcode) {
	std::uint64_t open = 0;
	std::uint64_t closed = 0;
	for (std::size_t i = 0; i < bfcode.length(); i++) {
			if (bfcode[i] == '[') {
				++open;
			}
			else if (bfcode[i] == ']') {
				++closed;
			}
			if (closed > open) {
				std::cout << "ERROR: brainfuck loops are incorrect!\n";
				return false;
			}
	}
	if (closed != open) {
		std::cout << "ERROR: brainfuck loops are incorrect!\n";
		return false;
	}
	return true;
}

void cleanup(std::string& bfcode) {
	static constexpr std::string allowed("+-<>[],.?");
	std::erase_if(bfcode, [](const auto c) { return !allowed.contains(c); });
}