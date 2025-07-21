#include<vector>
#include<string>
#include<glad/glad.h>
#include<iostream>

struct Texture {

	GLuint ptr;
	
	int width, height, channels;

	~Texture() {
		if(ptr != 0) {
			glDeleteTextures(1, &ptr);
			ptr = 0;
		}
	}

	inline void bind(int unit = 0) {
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, ptr);
	};

	bool load(std::istream& in);
};








