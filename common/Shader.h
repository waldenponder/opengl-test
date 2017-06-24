#pragma once
#include <iostream>
#include "common.h"

class COMMON_API Shader
{
public:
	Shader(std::string vertPath, std::string fragPath);
	~Shader();

	void Use();
	void setUniformVec4f(char* name, float x, float y, float z, float w);
	void setUniformMat4f(char* name, glm::mat4 mat4);
	void setUniformTexture2D(char* name, GLuint texture, int index);

private:
	GLuint program;
};