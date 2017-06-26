#pragma once
#include "common.h"
#include "include/FreeImage/FreeImage.h"

#ifndef FLOAT_SIZE
#define FLOAT_SIZE (sizeof(GLfloat))
#endif // !FLOAT_SIZE

#ifndef PREPARE_GLFW_WINDOW
#define PREPARE_GLFW_WINDOW(nW, nH, strName)\
	glfwInit();\
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);\
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);\
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);\
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);\
	window = glfwCreateWindow(nW, nH, strName, nullptr, nullptr); \
	glfwMakeContextCurrent(window); \
	glewInit(); \
	int w, h; \
	glfwGetFramebufferSize(window, &w, &h); \
	glViewport(0, 0, w, h);
#endif

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1200
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 1200
#endif

#ifndef WINDOW_NAME
#define WINDOW_NAME "learn gl"
#endif

namespace tools
{
	GLuint COMMON_API CreateTexture(char* path, GLuint param1 = GL_REPEAT, GLuint param2 = GL_LINEAR);

	//获得180个浮点型的数组, 顶点加纹理
	void COMMON_API GetCubePts(GLfloat* arr);

	//返回GLFWwindow指针
	COMMON_API GLFWwindow*  PrepareGlfwWindow(int w = 1200, int h = 900, const char* title = "learn opengl", GLFWkeyfun cbfun = nullptr);
}