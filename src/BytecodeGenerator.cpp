#include <iostream>
#include "BFHeader.h"

bool byteGenerator(std::string bfcode, std::string path, bool random) {
	for (std::uint32_t i = 0; i <= bfcode.length(); i++) {
		if (!random) {
			bfcode[i] = bfcode[i] == '?' ? ' ' : bfcode[i];
		}
	}
	return true;
}