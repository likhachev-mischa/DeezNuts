#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

GLuint vbo = 0;
GLuint vao = 0;
GLuint vs;
GLuint fs;
GLuint shader_programm;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	}
}

void initializeProgram()
{
	float modelData[] = {
		0.0f, 0.5f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f,
		1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	const char* vertex_shader =
		"#version 400\n"
		"in vec3 in_position;"
		"in vec3 in_color;"
		"out vec3 color;"
		"void main() {"
		" gl_Position = vec4(in_position, 1.0);"
		" color = in_color;"
		"}";
	const char* fragment_shader =
		"#version 400\n"
		"in vec3 color;"
		"out vec4 frag_colour;"
		"void main() {"
		" frag_colour = vec4(color,1.0);"
		"}";

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), modelData, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	shader_programm = glCreateProgram();

	glAttachShader(shader_programm, fs);
	glAttachShader(shader_programm, vs);

	glBindAttribLocation(shader_programm, 0, "in_position");
	glBindAttribLocation(shader_programm, 1, "in_color");

	glLinkProgram(shader_programm);
	glUseProgram(shader_programm);
}

void renderPrimitive()
{
	// draw points 0-3 from the currently bound VAO with current in-use shader
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glfwSetKeyCallback(window, key_callback);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void cleanup()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &vao);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(shader_programm);
}


int main(int argc, char** argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW + GLAD", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	initializeProgram();
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		renderPrimitive();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	cleanup();
	glfwTerminate();
	return 0;
}
