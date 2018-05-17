#ifndef DISPLAY_H
#define DISPLAY_H
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include <SDL2\SDL.h>
#include <string>

using namespace std;

class Display
{
public:
	Display(int width, int height, const std::string& title);
	virtual ~Display();

	void SDLDisplay(int width, int height, const std::string& title);
	void SwapBuffers();
	void Update();

	bool IsClosed();


private:
	Display(const Display& other) {}
	Display & operator=(const Display& other) {}

	GLFWwindow* window;
	//SDL_GLContext glContext;

	bool bIsClosed;


};

#endif //DISPLAY_H