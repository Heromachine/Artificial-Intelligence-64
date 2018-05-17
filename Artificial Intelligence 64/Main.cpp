
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;
using namespace std;

const GLchar *vertexShaderSource =
"#version 330 core\n "
"layout (location = 0) in vec3 position; \n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"out vec4 color; \n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5, 0.2, 1.0f);\n"
"}";


int main()
{
	glfwInit();


	//CREATE WINDOW ENVIRONMENT =====================================
	//glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "VACCUM", nullptr, nullptr);


	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);



	if (nullptr == window)
	{
		std::cout << "FAILED\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}
	else
	{
		cout << "\WINDOW CREATED";
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "\nFAILED TO GLEW\n";
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	//ITEMS CHECK ERRORS
	GLint success;
	GLchar infolog[512];





	//VERTEX SHADER CREATED
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//CHECK IF VERTEX SHADER SUCCEDED
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		cout << "ERROR: VERTEX SHADER COMILIE FAILURE\n" << infolog << endl;
	}


	//FRAGMENT SHADER CREATED 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		cout << "ERROR: FRAG SAHDER COMILIE FAILURE\n" << infolog << endl;
	}



	//link shader
	GLuint shaderPRogram = glCreateProgram();
	glAttachShader(shaderPRogram, vertexShader);
	glAttachShader(shaderPRogram, fragmentShader);
	glLinkProgram(shaderPRogram);

	glGetProgramiv(shaderPRogram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shaderPRogram, 512, NULL, infolog);
		cout << "ERROR: SHADER PROGRAM FAILURE\n" << infolog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//VERTEx SHADER
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
		//-0.5f, -0.5f, 0.0f


	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//CREATE VISUAL OBJECT
		glUseProgram(shaderPRogram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

	}


	//Delete 
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return EXIT_SUCCESS;
}

