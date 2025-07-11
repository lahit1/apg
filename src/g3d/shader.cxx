inline Shader Shader::create(char* code, GLenum shaderType) {
	Shader *ret = new Shader();
	ret->ptr = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ret->ptr, 1, code, NULL);
};
inline Shader Shader::compile() {
	glCompilerShader(ret->ptr);
}
