#ifndef SHADER_H
#define SHADER_H
#include<string>
#include<GL\glew.h>

using namespace std;
class Shader
{
public:
	Shader(const string &fileName);

	void Bind();

	//Shader();
	GLuint CreateShader(const string & text, GLenum shaderType);
	virtual ~Shader();
private:
	Shader(const Shader& other);
	void operator =(const Shader& other) {}

	static const unsigned int NUM_SHADERS = 2;

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];




};



#endif 
