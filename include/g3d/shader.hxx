struct Shader {
	unsigned int ptr;
	inline Shader compile();
}

namespace Shader {
	inline Shader create(char* code);
}
