#pragma once

#include <istream>
#include <ostream>
#include <iostream>

namespace Files {

std::istream* openi(const char* filename);
std::ostream* openo(const char* filename);
std::iostream* openio(const char* filename);

}
