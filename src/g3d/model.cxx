#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<g3d/renderable.hxx>
#include<g3d/model.hxx>

namespace Models {

void drawModel(Model* m) {
	glBindVertexArray(m->VAO);
	glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);
}


Model* createCube(int w, int h, int d) {
	float vertices[] = {
        	0.5f, 0.5f, 0.5f, // Top - F R
		-0.5f, 0.5f, 0.5f, // F L
		0.5f, 0.5f, -0.5f, // B R
		-0.5f, 0.5f, -0.5f, // B L
	
		0.5f, -0.5f, 0.5f, // Bottom - F R
        	-0.5f, -0.5f, 0.5f, // F L
	        0.5f, -0.5f, -0.5f, // B R
	        -0.5f, -0.5f, -0.5f, // B L
    	};

	int indices[] = {
			0, 4, 1, // front
			1, 5, 4,

			0, 1, 2, // top
			2, 3, 1,

			2, 6, 3, // back
			3, 7, 6,

			0, 4, 2, // right
			2, 6, 4,

			4, 5, 6, // bottom
			6, 7, 5,

			3, 7, 1, // left
			1, 5, 3
			};


	Model *ret = new Model();
	glGenVertexArrays(1, &ret->VAO);
	glGenBuffers(1, &ret->VBO);
	glGenBuffers(1, &ret->EBO);

	glBindVertexArray(ret->VAO); // Use the buffer

	glBindBuffer(GL_ARRAY_BUFFER, ret->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ret->indexCount = sizeof(indices), indices, GL_STATIC_DRAW);


	// Set pointer
	glVertexAttribPointer(0, // layout = 0
				3,  // vec3
				GL_FLOAT,
				GL_FALSE,
				3 * sizeof(float), // sizeof(vec3)
				(void*)0); // ofset per vertex

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return ret;
}



}
