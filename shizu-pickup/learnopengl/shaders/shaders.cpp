#include <glad\glad.h> // attention here glad.h must be in front of glfw3.h
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void procesInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

const char* vertexShaderSource =
		"#version 400 core\n"
		"layout (location = 0) in vec3 aPos;"
    	"layout (location = 1) in vec3 aColor;"
		//"out vec4 vertexColor;"
	    "out vec3 ourColor;"
		"void main() {"
		"gl_Position = vec4(aPos, 1.0);"
		//"vertexColor = vec4(0.5,0.0,0.0,1.0); }";
	    "ourColor = aColor; }";

const char* fragmentShaderSource =
		"#version 400 core\n"
		"out vec4 FragColor;"
		//"in vec4 vertexColor;"
		//"uniform vec4 ourColor;"
		"in vec3 ourColor;"
		"void main() {"
		//"FragColor = vertexColor; }";
		"FragColor = vec4(ourColor, 1.0); }";



int main()
{
	//init the window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << " Failed to creat GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}
	//unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	//// check
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	////check
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	//}
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	// user our shader class
	Shader ourShader("4.0.shader.vs", "4.0.shader.fs"); // you can name your shader files however you like
	float offset = 0.5f;

	glUniform1f(glGetUniformLocation(ourShader.ID, "xOffset"), offset);
	//float vertices[] =
	//{
	//	0.0f,0.5f,0.0f,
	//	-0.5f,0.0f,0.0f,
	//	0.5f,0.0f,0.0f
	//};

	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) //render loop
	{
		//input
		procesInput(window);
		//rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		ourShader.setFloat("xOffset", 0.5f); // ? here 0.5f and the above 0ffset is nonsense??

		/*glUseProgram(shaderProgram);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); 

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
