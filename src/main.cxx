#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <g3d/shader.hxx>
#include <g3d/program.hxx>
#include <g3d/mesh.hxx>
#include <g3d/renderer.hxx>

#include <utils/files.hxx>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

const char *vertexShaderSource = R"(
	#version 330 core

	layout(location = 0) in vec3 aPos;         // 3D position
	layout(location = 1) in vec3 aNorm;         // Surface normal
        layout(location = 2) in vec2 aTexCoord;       // Texture Coordinate
//	layout(location = 3) in vec4 aColor;       // RGBA color

	uniform mat4 vpU;
	uniform mat4 modelU;
	uniform mat4 normalU;

	out vec3 FragPos;
	out vec3 Normal;
	out vec2 TexCoord;

	void main()
	{
		vec4 worldPos = modelU * vec4(aPos, 1.0);

		FragPos = vec3(worldPos);  // world-space position
		Normal = mat3(normalU) * aNorm;      // correct normal transformation
		TexCoord = aTexCoord;

		gl_Position = vpU * worldPos; // convert to 4D vec
	}

)";


const char *fragmentShaderSource = R"(
#version 330 core


uniform vec3 materialAmbientC;
uniform vec3 materialDiffuseC;
uniform vec3 materialSpecularC;
uniform float materialShininess;

uniform sampler2D materialDiffuseT;
uniform sampler2D materialSpecularT;
uniform sampler2D materialNormalT;


uniform vec3 viewPos;      // Camera position

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;      // Output color

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(1, 0, 1));
    vec3 viewDir  = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

//    vec3 ambient = materialAmbientC;
    vec3 ambient = vec3(0, 0, 0);

    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = materialDiffuseC * diff;
    vec3 diffuse = vec3(0.5f, 0, 0) * diff;


    // Specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
//    vec3 specular = materialSpecularC * spec;
    vec3 specular = vec3(0.5f, 0.1f, 0.1f) * spec;


    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(pow(result, vec3(1.0 / 2.2)), 1.0);
//	FragColor = vec4(vec3(diff), 1.0);
}

)";


Camera* c_cam;

void framebuffer_size_callback(GLFWwindow* win, int w, int h) {
	glViewport(0, 0, w, h);
	c_cam->aspect = static_cast<float>(w) / h;
	c_cam->updateProjection();
	c_cam->updateVP();
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



	Mesh* mmodel  = Meshes::createCube(0,0,0);
	std::istream* is = Files::openi("res/Car.obj");
	Mesh* mmodel2 = Meshes::loadObjMesh(is);

	Model *bmodel = new Model();
	Material* mats = new Material();
	mats->diffuseColor = glm::vec3(1, 0, 0);
	mats->specularColor = glm::vec3(1, 1, 1);
	mats->shininess = 64.0f;

	bmodel->material = mats;
	bmodel->addChild(mmodel);
	bmodel->addChild(mmodel2);

//	is->close();
	delete is;

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

		RENDERER::DRAW(bmodel);
//		RENDERER::DRAW(mmodel2);

		glDisable(GL_DEPTH_TEST);
		// 2D renders, like GUI...
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Shaders::freeAll();
	glfwTerminate();
	return 0;
}
