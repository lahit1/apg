#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <g3d/shader.hxx>
#include <g3d/program.hxx>
#include <g3d/model.hxx>
#include <g3d/renderer.hxx>

const char *vertexShaderSource = R"(
	#version 330 core

	layout(location = 0) in vec2 aPos;         // 2D position
	layout(location = 1) in vec3 aColor;       // RGB color

	out vec3 vColor;  // Pass color to fragment shader

	void main()
	{
		gl_Position = vec4(aPos, 0.0, 1.0); // convert to 4D vec
		// gl_Position.z = 5;
		// vColor = aColor;  // pass through to fragment
		vColor = vec3(1,0,0);
	}

)";

const char *fragmentShaderSource = R"(
#version 330 core

in vec3 vColor;          // Interpolated from vertex shader
out vec4 FragColor;      // Output color

void main()
{
    FragColor = vec4(vColor, 1.0); // RGBA: color + full opacity
}

)";

int main(void) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Simple program", NULL, NULL);
	if (window == NULL) {
        	std::cout << "Couldn't create the window" << std::endl;
        	glfwTerminate();
        	return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        	std::cout << "Couldn't load GLAD(library)" << std::endl;
        	return -1;
	}

	Shader *vertex = Shaders::create(&vertexShaderSource, GL_VERTEX_SHADER)->compile();
	Shader *fragment = Shaders::create(&fragmentShaderSource, GL_FRAGMENT_SHADER)->compile();

	Program* program = Programs::create();
	program->attach(vertex);
	program->attach(fragment);
	program->link();

	Model* mmodel = Models::createCube(0,0,0);

	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program->use();

		glEnable(GL_DEPTH_TEST);
		// 3D renders...

		RENDERER::DRAW(mmodel);


		glDisable(GL_DEPTH_TEST);
		// 2D renders, like GUI...
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Shaders::freeAll();
	glfwTerminate();
	return 0;
}
