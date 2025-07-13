#include "Main.h"
#include "../glad4.6/include/glad/glad.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

void Init_Shader_GL(const char* vertex, const char* fragment)
{
	std::string vsscode;
	std::ifstream vssshaderfile;
	std::stringstream vssshaderstream;
	
	vssshaderfile.open(vertex);
	vssshaderstream << vssshaderfile.rdbuf();
	vssshaderfile.close();
	vsscode = vssshaderstream.str();
	
	std::string fsscode;
	std::ifstream fssshaderfile;
	std::stringstream fssshaderstream;
	
	fssshaderfile.open(fragment);
	fssshaderstream << fssshaderfile.rdbuf();
	fssshaderfile.close();
	fsscode = fssshaderstream.str();
	
	const char* vertexShaderSource = vsscode.c_str();
	const char* fragmentShaderSource = fsscode.c_str();
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

}

void Link_Shader_GL()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
}

void Clean_Shader_GL()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}
