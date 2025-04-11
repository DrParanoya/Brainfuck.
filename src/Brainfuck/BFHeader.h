#pragma once

void interpreter(std::string &bfcode, const bool random, const bool clear = false);

void transpile_c_cpp(std::string &bfcode, std::string &path, const bool random, const bool cpp);

bool loopsCorrect(std::string &bfcode);
void cleanup(std::string& bfcode);