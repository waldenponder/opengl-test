#pragma once
#include <iostream>
#include "common.inner.h"

class COMMON_API Shader
{
public:
	Shader(std::string vertPath, std::string fragPath);
	~Shader();

	void Use();
	void setUniformVec4f(char* name, float x, float y, float z, float w);
	void setUniformVec3f(char* name, float x, float y, float z);

	void setUniformVec3f(char* name, TVec3 vec3);
	void setUniformVec4f(char* name, TVec4 vec4);

	void setUniformMat4f(char* name, glm::mat4 mat4);
	void setUniformTexture2D(char* name, GLuint texture, int index);
	void setUniformTextureCube(char* name, GLuint texture, int index);

private:
	GLuint program;
};