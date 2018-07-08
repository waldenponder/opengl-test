#pragma once
#include "common.inner.h"
#include "include/FreeImage/FreeImage.h"

COMMON_API extern glm::mat4 g_Mat4;

struct COMMON_API Complex
{
	GLfloat real;
	GLfloat imaginary;
};

namespace Utility
{
	COMMON_API GLuint  CreateTexture(char* path, GLuint wrapModel = GL_REPEAT, GLuint filterModel = GL_LINEAR);

	COMMON_API GLuint  CreateCubemap(const vector<const char*> faces);

	COMMON_API void CreateFBO(GLuint& frambuffer, GLuint& texColorBuffer,
		GLuint filterModel = GL_LINEAR, GLuint wrapModel = GL_CLAMP_TO_EDGE, 
		GLuint width = WINDOW_WIDTH, GLuint height = WINDOW_HEIGHT);

	//获得180个浮点型的数组, 顶点加纹理
	COMMON_API void  GetCubePts_withTexture(GLfloat* arr);
	
	//获得288个浮点型的数组, 顶点/纹理/法线
	COMMON_API void  GetCubePts_withTextureNormal(GLfloat* arr);

	COMMON_API void  DefaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);


	COMMON_API void CreatePlaneVAO(OUT GLuint& VAO);

	COMMON_API void CreateCubeVAO(OUT GLuint& VAO);

	COMMON_API void* MemoryMalloc(size_t size);

	COMMON_API void MemoryFree(void* pointer);

	COMMON_API GLfloat MathRadToDegf(const GLfloat radians);

	COMMON_API GLfloat MathDegToRadf(const GLfloat degrees);

	COMMON_API GLfloat MathClampf(const GLfloat value, const GLfloat min, const GLfloat max);
}