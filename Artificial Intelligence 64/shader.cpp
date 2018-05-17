#include "shader.h"
#include <iostream>
#include <fstream>

using namespace std;

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
static string LoadShader(const std::string& filename);
//static GLuint CreateShader(const string& text, GLenum shaderType);

Shader::Shader(const string & fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "\nERROR: program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "\nERROR: program validation failed: ");


}

void Shader::Bind()
{

	glUseProgram(m_program);

}
Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

static string LoadShader(const string& fileName)
{
	ifstream file;
	file.open((fileName).c_str());

	string output;
	string line;

	if (file.is_open())
	{
		cout << "\nFILE " << fileName << " is open" << endl;
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
			cout << "\n " << line << " \n";
		}
	}
	else
	{
		cerr << "\nUNABLE TO LAOD SHADER" << fileName << endl;
	}

	return output;
}

GLuint Shader::CreateShader(const string & text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		cerr << "\nERROR: SHADER CREATION FAILED\n";
	}

	const GLchar* shaderSourceString[1];
	shaderSourceString[0] = text.c_str();
	GLint shaderSourceStringLengths[1];
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "\nERROR: Shader Compilation failed: ");


	return shader;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}


	//
	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		cerr << errorMessage << ": [ " << error << " ]" << endl;
	}

}