#pragma once
#include <iostream>
#include "common.inner.h"

class COMMON_API Shader
{
public:
	Shader();
	Shader(std::string vertPath, std::string fragPath, std::string geomPath = "");
	~Shader();

	void setSource(std::string vertPath, std::string fragPath, std::string geomPath = "");
		 
	void Use();
	void setUniform1i(char* name, int i);
	void setUniform1f(char* name, int f);

	void setUniformVec4f(char* name, float x, float y, float z, float w);
	void setUniformVec3f(char* name, float x, float y, float z);

	void setUniformVec3f(char* name, TVec3 vec3);
	void setUniformVec4f(char* name, TVec4 vec4);

	void setUniformMat4f(char* name, glm::mat4 mat4);
	void setUniformTexture2D(char* name, GLuint texture, int index);
	void setUniformTextureCube(char* name, GLuint texture, int index);

private:
	std::string getSource(const std::string& path);
	void compile(const char* src, GLuint ID);

private:

	GLuint program;
};