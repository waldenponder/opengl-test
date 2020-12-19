#include "stdafx.h"
#include "Shader.h"
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

Shader::Shader()
{

}

Shader::Shader(std::string vertPath, std::string fragPath, std::string geomPath)
{		
	setSource(vertPath, fragPath, geomPath);
}


void Shader::setSource(std::string vertPath, std::string fragPath, std::string geomPath /*= ""*/)
{
	string str = getSource(vertPath);
	GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
	compile(str.c_str(), vertID);

	str = getSource(fragPath);
	GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
	compile(str.c_str(), fragID);

	GLuint geomID = INT_MAX;
	if (!geomPath.empty())
	{
		str = getSource(geomPath);
		geomID = glCreateShader(GL_GEOMETRY_SHADER);
		compile(str.c_str(), geomID);
	}

	_program = glCreateProgram();
	{
		glAttachShader(_program, vertID);
		glAttachShader(_program, fragID);

		if (geomID != INT_MAX)
			glAttachShader(_program, geomID);

		glLinkProgram(_program);

		GLint success;
		GLchar infoLog[512];

		glGetProgramiv(_program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(_program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}

	glDeleteShader(vertID);
	glDeleteShader(fragID);
	glDeleteShader(geomID);
}


Shader::~Shader()
{
}

std::string Shader::getSource(const string& path)
{
	string str;
	try
	{
		ifstream IF;
		stringstream  fstream;

		IF.open(path);
		IF.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);

		fstream << IF.rdbuf();
		str = fstream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << " ¶ÁÈ¡shader " << path << " Òì³£ " << e.what() << std::endl;
	}

	return str;
}

void Shader::compile(const char* src, GLuint ID)
{
	GLint success;
	GLchar infoLog[512];

	glShaderSource(ID, 1, &src, NULL);
	glCompileShader(ID);
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		std::cout << src << infoLog << std::endl;
	}
}

void Shader::Use()
{
	glUseProgram(_program);
}

void Shader::setUniform1i(char* name, int i)
{
	GLint loc = glGetUniformLocation(_program, name);
	glUniform1i(loc, i);
}

void Shader::setUniform1f(char* name, int f)
{
	GLint loc = glGetUniformLocation(_program, name);
	glUniform1f(loc, f);
}

void Shader::setUniformVec4f(char* name, float x, float y, float z, float w)
{
	GLint loc = glGetUniformLocation(_program, name);
	glUniform4f(loc, x, y, z, w); 
}

void Shader::setUniformVec4f(char* name, TVec4 vec4)
{
	setUniformVec4f(name, vec4[0], vec4[1], vec4[2], vec4[3]);
}


void Shader::setUniformVec3f(char* name, float x, float y, float z)
{
	GLint loc = glGetUniformLocation(_program, name);
	glUniform3f(loc, x, y, z);
}

void Shader::setUniformVec3f(char* name, TVec3 vec3)
{
	setUniformVec3f(name, vec3[0], vec3[1], vec3[2]);
}

void Shader::setUniformMat4f(char* name, glm::mat4 mat4)
{
	GLint loc = glGetUniformLocation(_program, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::setUniformTexture2D(char* name, GLuint texture, int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, texture);

	GLuint loc = glGetUniformLocation(_program, name);
	glUniform1i(loc, index);
}

void Shader::setUniformTextureCube(char* name, GLuint texture, int index)
{

	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	GLuint loc = glGetUniformLocation(_program, name);
	glUniform1i(loc, index);
}
