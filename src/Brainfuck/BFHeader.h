#pragma once

void interpreter(std::string &bfcode, const bool random, const bool clear = false);
bool loopsCorrect(std::string &bfcode);
void aheadOfTime(std::string &bfcode, std::string &path, const bool random);
void byteInterpreter(std::string &path, const bool clear = false);
bool byteGenerator(std::string &bfcode, std::string &path, const bool random);