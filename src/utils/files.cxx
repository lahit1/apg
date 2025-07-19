#include <utils/files.hxx>
#include <fstream>

namespace Files {

std::istream* openi(const char *filename) {
	std::ifstream* ifs = new std::ifstream(filename);
	return ifs;
};
std::ostream* openo(const char *filename) {
	std::ofstream* ofs = new std::ofstream(filename);
        return ofs;
};
std::iostream* openio(const char *filename) {
	std::fstream* iofs = new std::fstream(filename);
        return iofs;
};

}
