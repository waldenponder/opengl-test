#include "stdafx.h"
#include "Utility.h"
#include <string.h>

namespace tools
{
	GLuint CreateTexture(char* path, GLuint param1, GLuint param2)
	{
		GLuint  texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param2);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param2);
		
		FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(path);
		FIBITMAP* fib = FreeImage_Load(format, path);
		int width = FreeImage_GetWidth(fib);
		int height = FreeImage_GetWidth(fib);
		unsigned char* image = FreeImage_GetBits(fib);
	  		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		FreeImage_Unload(fib);
		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}
	
	void GetCubePts(GLfloat* arr)
	{
		/*
		定点和纹理坐标
		*/
		GLfloat pts[] =
		{
			// 涓?
			-0.5, 0.5, -0.5, 0, 1,
			-0.5, 0.5, 0.5, 0, 0,
			0.5, 0.5, -0.5, 1, 1,
			-0.5, 0.5, 0.5, 0, 0,
			0.5, 0.5, 0.5, 1, 0,
			0.5, 0.5, -0.5, 1, 1,

			//涓?
			-0.5, -0.5, -0.5, 0, 1,
			0.5, -0.5, -0.5, 1, 1,
			0.5, -0.5, 0.5, 1, 0,
			-0.5, -0.5, -0.5, 0, 1,
			0.5, -0.5, 0.5, 1, 0,
			-0.5, -0.5, 0.5, 0, 0,

			//宸?
			0.5, 0.5, 0.5, 0, 1,
			0.5, -0.5, 0.5, 0, 0,
			0.5, -0.5, -0.5, 1, 0,
			0.5, 0.5, 0.5, 0, 1,
			0.5, -0.5, -0.5, 1, 0,
			0.5, 0.5, -0.5, 1, 1,

			//鍙?
			-0.5, 0.5, 0.5, 0, 1,
			-0.5, 0.5, -0.5, 1, 1,
			-0.5, -0.5, -0.5, 1, 0,
			-0.5, 0.5, 0.5, 0, 1,
			-0.5, -0.5, -0.5, 1, 0,
			-0.5, -0.5, 0.5, 0, 0,

			//鍓?
			-0.5, 0.5, 0.5, 0, 1,
			0.5, -0.5, 0.5, 1, 0,
			0.5, 0.5, 0.5, 1, 1,
			-0.5, 0.5, 0.5, 0, 1,
			-0.5, -0.5, 0.5, 0, 0,
			0.5, -0.5, 0.5, 1, 0,

			//鍚?
			-0.5, 0.5, -0.5, 0, 1,
			0.5, 0.5, -0.5, 1, 1,
			0.5, -0.5, -0.5, 1, 0,
			-0.5, 0.5, -0.5, 0, 1,
			0.5, -0.5, -0.5, 1, 0,
			-0.5, -0.5, -0.5, 0, 0
		};

		for (int i = 0; i < 180; i++)
		{
			arr[i] = pts[i];
		}
	}

	GLFWwindow* PrepareGlfwWindow(int w /*= 1200*/, int h /*= 900*/,
		const char* title /*= "learn opengl"*/, GLFWkeyfun cbfun /*= nullptr*/)
	{
#if 0
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		GLFWwindow* window = glfwCreateWindow(w, h, title, nullptr, nullptr);
		glfwMakeContextCurrent(window);
		
		glewInit();

		int nW, nH;
		glfwGetFramebufferSize(window, &nW, &nH);
		glViewport(0, 0, nW, nH);
#else
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWwindow*window = glfwCreateWindow(1200, 900, "learn opengl", nullptr, nullptr);
		glfwMakeContextCurrent(window);

		glewInit();

		int nw, nh;
		glfwGetFramebufferSize(window, &nw, &nh);
		glViewport(0, 0, nw, nh);
#endif

		if (cbfun)
		   glfwSetKeyCallback(window, cbfun);

		return window;
	}
}