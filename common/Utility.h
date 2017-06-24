#pragma once
#include "common.h"

#ifndef FLOAT_SIZE
#define FLOAT_SIZE (sizeof(GLfloat))
#endif // !FLOAT_SIZE

namespace tools
{
	GLuint COMMON_API CreateTexture(char* path, GLuint param1 = GL_REPEAT, GLuint param2 = GL_LINEAR);

	//获得180个浮点型的数组, 顶点加纹理
	void COMMON_API GetCubePts(GLfloat* arr);
}