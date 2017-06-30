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

	void default_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		int flag = 1;
		if (mode == GLFW_MOD_SHIFT)
		{
			flag = -1;
		}

		if (key == GLFW_KEY_Q)
		{
			glm::vec3 axis(0, 0, flag);
			g_Mat4 = glm::rotate(g_Mat4, 3.0f, axis);
		}
		else if (key == GLFW_KEY_W)
		{
			glm::vec3 axis(0, flag, 0);
			g_Mat4 = glm::rotate(g_Mat4, 3.0f, axis);
		}
		else if (key == GLFW_KEY_E)
		{
			glm::vec3 axis(flag, 0, 0);
			g_Mat4 = glm::rotate(g_Mat4, 3.0f, axis);
		}
		else if (key == GLFW_KEY_A)
		{
			glm::vec3 axis(flag * .1, 0, 0);
			g_Mat4 = glm::translate(g_Mat4, axis);
		}
		else if (key == GLFW_KEY_S)
		{
			glm::vec3 axis(0, flag * .1, 0);
			g_Mat4 = glm::translate(g_Mat4, axis);
		}
		else if (key == GLFW_KEY_D)
		{
			glm::vec3 axis(0, 0, flag * .1);
			g_Mat4 = glm::translate(g_Mat4, axis);
		}
		else if (key == GLFW_KEY_SPACE)
		{
			g_Mat4 = glm::mat4(1.0);
		}
	}


}