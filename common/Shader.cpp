#include "stdafx.h"
#include "Shader.h"
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

Shader::Shader(std::string vertPath, std::string fragPath)
{		
	const char* source_vert; string str_vert;
	{
		try
		{
			ifstream IF;
			stringstream  fstream;

			IF.open(vertPath);
			IF.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
			
			fstream << IF.rdbuf();
			str_vert = fstream.str();
			source_vert = str_vert.c_str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << " 读取shader " << vertPath << " 异常 " << e.what() << std::endl;
		}
	}

	const char* source_frag;  string str_frag;
	{
		try
		{
			ifstream IF;
			stringstream  fstream;

			IF.open(fragPath);
			IF.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);

			fstream << IF.rdbuf();
			str_frag = fstream.str();
			source_frag = str_frag.c_str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << " 读取shader " << fragPath << " 异常 " << e.what() << std::endl;
		}
	}

	GLint success;
	GLchar infoLog[512];

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	{
		glShaderSource(vertexShader, 1, &source_vert, NULL);
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
		glShaderSource(fragmentShader, 1, &source_frag, NULL);
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

void Shader::setUniformVec4f(char* name, TVec4 vec4)
{
	setUniformVec4f(name, vec4[0], vec4[1], vec4[2], vec4[3]);
}


void Shader::setUniformVec3f(char* name, float x, float y, float z)
{
	GLint loc = glGetUniformLocation(program, name);
	glUniform3f(loc, x, y, z);
}

void Shader::setUniformVec3f(char* name, TVec3 vec3)
{
	setUniformVec3f(name, vec3[0], vec3[1], vec3[2]);
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

	if (index != -1)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	GLuint loc = glGetUniformLocation(program, name);
	glUniform1i(loc, index);
}
