#include <iostream>
#include "display.h"
#include<GL\glew.h>
#include<GLFW\glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;
Display::Display(int width, int height, const std::string& title)
{
	int type;
	enum DisplayTypes { SDL = 1, GLFW = 2 };


	SDLDisplay(width, height, title);


}
Display::~Display()
{
	//SDL_GL_DeleteContext(glContext);
	//SDL_GL_DeleteContext(window);
	//SDL_Quit();
}
void Display::SDLDisplay(int width, int height, const std::string& title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);


	window = glfwCreateWindow(WIDTH, HEIGHT, "VACCUM", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	if (nullptr == window)
	{
		std::cout << "WINDOW CREATE FAILED\n";
		glfwTerminate();
		//return EXIT_FAILURE;
	}
	else
	{
		cout << "\WINDOW CREATED";


		glfwMakeContextCurrent(window);

		GLenum status = glewInit();

		if (status != GLEW_OK)
		{
			std::cerr << "\nGLEW FAILED" << std::endl;
		}

		bIsClosed = false;


	}
}

void Display::Update()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);//WARNING
		glBindVertexArray(0);//WARNING

		glfwSwapBuffers(window);
	}
}
void Display::SwapBuffers()
{
	glfwSwapBuffers(window);

}
bool Display::IsClosed()
{
	return bIsClosed;
}