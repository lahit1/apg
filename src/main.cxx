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

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

const char *vertexShaderSource = R"(
	#version 330 core

	layout(location = 0) in vec3 aPos;         // 3D position
	layout(location = 1) in vec3 aColor;       // RGB color

	uniform mat4 mvpU;

	out vec3 vColor;  // Pass color to fragment shader

	void main()
	{
		gl_Position = mvpU * vec4(aPos, 1.0); // convert to 4D vec
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


Camera* c_cam;

void framebuffer_size_callback(GLFWwindow* win, int w, int h) {
	glViewport(0, 0, w, h);
	c_cam->aspect = static_cast<float>(w) / h;
	c_cam->updateProjection();
	c_cam->updateVP();

	std::cout << glm::to_string(c_cam->vp) << std::endl;
}

float valuee;

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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

	c_cam = new Camera();
	c_cam->dist.z = 5;
	c_cam->updateView();
	c_cam->updateVP();


	Model* mmodel = Models::createCube(0,0,0);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glDisable(GL_CULL_FACE);

	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RENDERER::USE(program);

		glEnable(GL_DEPTH_TEST);
		// 3D renders...

		// glFrontFace(GL_CW);

		c_cam->dist.z = 5 * glm::cos(valuee += 0.01f);
		c_cam->dist.x = 5 * glm::sin(valuee);
		c_cam->updateView();
		c_cam->updateVP();

		RENDERER::BEGIN(c_cam);
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
