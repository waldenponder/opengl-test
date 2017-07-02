#pragma once
#include "common.inner.h"
#include "include/FreeImage/FreeImage.h"

COMMON_API glm::mat4 g_Mat4;

namespace tools
{
	COMMON_API GLuint  CreateTexture(char* path, GLuint param1 = GL_REPEAT, GLuint param2 = GL_LINEAR);

	//获得180个浮点型的数组, 顶点加纹理
	COMMON_API void  GetCubePts(GLfloat* arr);
			
	COMMON_API void  default_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
}