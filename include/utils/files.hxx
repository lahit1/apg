#pragma once

#include <fstream>

namespace Files {

std::ifstream* openi(const char* filename);
std::ofstream* openo(const char* filename);
std::fstream* openio(const char* filename);

}
