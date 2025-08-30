#include<g/texture.hxx>

#define STB_IMAGE_IMPLEMENTATION
#include<stb/stb_image.h>

bool Texture::load(std::istream& in) {
	std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(in)),
                                                        std::istreambuf_iterator<char>());

        if(buffer.empty()) {
                std::cerr << "Stream empty, couldn't load texture..." <<std::endl;
                return false;
        }

        unsigned char* data = stbi_load_from_memory(buffer.data(), buffer.size(), &width, &height, &channels, 0);

        if(!data) {
                std::cerr << "Broken data, couldn't load texture..." <<std::endl;
                return false;
        }

        GLenum format = GL_RGB;
        if(channels == 1) format = GL_RED;
	else if (channels == 3) format = GL_RGB;
        else if(channels == 4) format = GL_RGBA;

        glGenTextures(1, &ptr);
        glBindTexture(GL_TEXTURE_2D, ptr);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

        return true;
};
