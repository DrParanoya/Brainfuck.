#pragma once

void interpreter(std::string bfcode, bool random);
bool loopsCorrect(std::string bfcode);
void aheadOfTime(std::string bfcode, std::string path, bool random);
void byteInterpreter(std::string btcode);
bool byteGenerator(std::string bfcode, std::string path, bool random);