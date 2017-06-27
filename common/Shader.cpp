#include "stdafx.h"
#include "Shader.h"
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

Shader::Shader(std::string vertPath, std::string fragPath)
{
	const char* sourceVert, *sourceFrag;
	string streamVert, streamFrag;

	try
	{
		{
			ifstream vertIF, fragIF;
			vertIF.open(vertPath);
			fragIF.open(fragPath);
				
			char buffer[256];
			while (!vertIF.eof())
			{
				vertIF.getline(buffer, 256, '\n');
				streamVert += buffer; streamVert += '\n';
			}
			streamVert += '\0';
	
			while (!fragIF.eof())
			{
				fragIF.getline(buffer, 256, '\n');
				streamFrag += buffer; streamFrag += '\n';
			}
			streamFrag += '\0';
	
			sourceVert = streamVert.c_str();
			sourceFrag = streamFrag.c_str();
		}
	}
	catch (const char* msg)
	{
		std::cout << " 读取shader 异常 "  << msg << std::endl;
	}

	GLint success;
	GLchar infoLog[512];

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	{
		glShaderSource(vertexShader, 1, &sourceVert, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	{
		glShaderSource(fragmentShader, 1, &sourceFrag, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
	
	program = glCreateProgram();
	{
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		// Check for linking errors
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}



Shader::~Shader()
{
}

void Shader::Use()
{
	glUseProgram(program);
}

void Shader::setUniformVec4f(char* name, float x, float y, float z, float w)
{
	GLint loc = glGetUniformLocation(program, name);
	glUniform4f(loc, x, y, z, w);
}


void Shader::setUniformMat4f(char* name, glm::mat4 mat4)
{
	GLint loc = glGetUniformLocation(program, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::setUniformTexture2D(char* name, GLuint texture, int index)
{
#if 0
	GLuint arr[] =
	{ 
		GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2,
		GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5
	};

	if (index >= sizeof(arr) / sizeof(arr[0]))
		std::cout << "Shader::setUniform(char* name, GLuint texture, int index)  index 越界 " << std::endl;
#endif

	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, texture);

	GLuint loc = glGetUniformLocation(program, name);
	glUniform1i(loc, index);
}
