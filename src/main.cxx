#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <ape/g/shader.hxx>
#include <ape/g/program.hxx>
#include <ape/g3d/mesh.hxx>
#include <ape/g/renderer.hxx>
#include <ape/g3d/materialbuilder.hxx>

#include <ape/g/texturemanager.hxx>
#include <ape/utils/files.hxx>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>



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

	std::shared_ptr<ShaderProgram> program = ShaderProgram::mk();
	{
		std::ifstream *t = Files::openi("res/vertex.glsl");
		std::string str;

		t->seekg(0, std::ios::end);   
		str.reserve(t->tellg());
		t->seekg(0, std::ios::beg);

		str.assign((std::istreambuf_iterator<char>(*t)),
			std::istreambuf_iterator<char>());

		const char * shader_data = str.c_str();
		std::shared_ptr<Shader> vertex = Shaders::create(&shader_data, GL_VERTEX_SHADER)->compile();
		t->close();
		delete t;

		t = Files::openi("res/fragment.glsl");

		t->seekg(0, std::ios::end);   
		str.reserve(t->tellg());
		t->seekg(0, std::ios::beg);

		str.assign((std::istreambuf_iterator<char>(*t)),
			std::istreambuf_iterator<char>());

		
		shader_data = str.c_str();
		std::shared_ptr<Shader> fragment = Shaders::create(&shader_data, GL_FRAGMENT_SHADER)->compile();
		t->close();
		delete t;

		program->attach(vertex);
		program->attach(fragment);
		program->link();
	}
	c_cam = new Camera();
	c_cam->dist.z = 200;
	c_cam->dist.y = 25;
	c_cam->updateView();

	c_cam->farPlane = 300;
	c_cam->updateProjection();
	c_cam->updateVP();

	std::ifstream* is = Files::openi("res/model.obj");
	std::shared_ptr<Model> bmodel = Models::loadObjModel(is);

	{
		std::shared_ptr<MaterialBuilder> matb = std::make_shared<MaterialBuilder>();
		matb->add("materialAmbientC", glm::vec3(1, 0, 0));
	        matb->add("materialDiffuseC", glm::vec3(1, 1, 1));
	        matb->add("materialShininess", 64.f);

		std::shared_ptr<Texture> tex = TextureManager::load("res/texture.png");
		matb->add("materialDiffuseT", tex);

		bmodel->material = matb->build(program);
	}
	is->close();
	delete is;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RENDERER::USE(program);


		c_cam->dist.z = 200 * glm::cos(valuee += 0.01f);
		c_cam->dist.x = 200 * glm::sin(valuee);
		c_cam->updateView();
		c_cam->updateVP();

		RENDERER::BEGIN(c_cam);
		glEnable(GL_DEPTH_TEST);
		// 3D renders...


		RENDERER::DRAW(bmodel);

		glDisable(GL_DEPTH_TEST);
		// 2D renders...
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
