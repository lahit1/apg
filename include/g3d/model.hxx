#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<g3d/renderable.hxx>

struct Model : public Renderable {
	unsigned int VBO, // Buffer array (Vertices data)
		     VAO,
		     EBO;
	size_t indexCount;
	int matrix[16];
};


namespace Models {

Model* createCube(int w, int h, int d);

}
