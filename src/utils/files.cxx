#include <utils/files.hxx>

namespace Files {

std::ifstream* openi(const char *filename) {
	return new std::ifstream(filename);
}
std::ofstream* openo(const char *filename) {
	return new std::ofstream(filename);
}
std::fstream* openio(const char *filename) {
	return new std::fstream(filename);
}

}
