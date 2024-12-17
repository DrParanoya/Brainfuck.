#include <iostream>
#include "BFHeader.h"

bool loopsCorrect(std::string bfcode) {
	std::uint16_t open = 0;
	std::uint16_t closed = 0;
	for (std::uint32_t i = 0; i <= bfcode.length(); i++) {
			if (bfcode[i] == '[') {
				++open;
			}
			else if (bfcode[i] == ']') {
				++closed;
			}
			if (closed > open) {
				return false;
			}
	}
	if (closed != open) {
		std::cout << "ERROR: brainfuck loops are incorrect!\n";
		return false;
	}
	else {
		return true;
	}
}