#include <iostream>
#include <fstream>
#include <random>
#include <array>
#include <string>
#include <stdio.h>
#include "BFHeader.h"

void byteInterpreter(std::string path, const bool clear) {
	std::string loopCode;
	std::string btcode;
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
	
	std::ifstream file(path);
	if (file.fail()) {
		std::cout << "ERROR: failed to open a file at\"" << path << "\"!\n";
		return;
	}
	
	while (getline(file, btcode)) {
		switch (btcode[0]) {
		case 'c':
			btcode.erase(0, 3);
			cells[pointer] += std::stoi(btcode);
			break;
		case 'm':
			btcode.erase(0, 3);
			pointer += std::stoi(btcode);
			break;
		case 'o':
			std::cout << static_cast<char>(cells[pointer] & 127);
			break;
		case 'i':
			std::cin >> cells[pointer];
			break;
		case 'r':
			cells[pointer] = dist(gen);
			break;
		case 's':
			loopCode.clear();
			std::ofstream loopFile(path += "tmp");
			if (file.fail()) {
				std::cout << "ERROR: failed to create temporary file at \"" << path << "\"!\n";
				return;
			}
			while (getline(file, btcode)) {
				if (btcode[0] == 'e') {
					break;
				}
				loopFile << btcode << '\n';
			}
			loopFile.close();
			while (cells[pointer] != 0) {
				byteInterpreter(path);
			}
			break;
		}
	}
	file.close();
}
