#include "stdafx.h"
#include "Utility.h"
#include "stdlib.h"
#include <string.h>

COMMON_API glm::mat4 g_Mat4;

namespace Utility
{
	GLuint CreateTexture(char* path, GLuint wrapModel, GLuint filterModel)
	{
		GLuint  ID;
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModel);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModel);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterModel);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterModel);
		
		FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(path);
		FIBITMAP* fib = FreeImage_Load(format, path);
		int width = FreeImage_GetWidth(fib);
		int height = FreeImage_GetHeight(fib);
		unsigned char* image = FreeImage_GetBits(fib);
	  		
		unsigned int bpp = FreeImage_GetBPP(fib);

		//	倒数第三个参数为 GL_RGB 则得不得到正确的结果
		glTexImage2D(GL_TEXTURE_2D, 0, bpp == 32 ? GL_RGBA : GL_RGB, width, height, 0,
			bpp == 32 ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, image);

		glGenerateMipmap(GL_TEXTURE_2D);
		
		FreeImage_Unload(fib);
		glBindTexture(GL_TEXTURE_2D, 0);

		return ID;
	}


	GLuint CreateCubemap(const vector<const char*> faceVec)
	{
		GLuint ID;
		glGenTextures(1, &ID);
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		for (int i = 0; i < faceVec.size(); i++)
		{
			auto face = faceVec[i];
			FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(face);
			FIBITMAP* fib = FreeImage_Load(format, face);
			int width = FreeImage_GetWidth(fib);
			int height = FreeImage_GetHeight(fib);
			unsigned char* image = FreeImage_GetBits(fib);

			unsigned int bpp = FreeImage_GetBPP(fib);

			//	倒数第三个参数为 GL_RGB 则得不得到正确的结果
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, bpp == 32 ? GL_RGBA : GL_RGB,
				width, height, 0, bpp == 32 ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, image);

			glGenerateMipmap(GL_TEXTURE_2D);

			FreeImage_Unload(fib);
		}

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return ID;
	}

	
	void CreateFBO(GLuint& frambuffer, GLuint& texColorBuffer,
		GLuint filterModel /*= GL_LINEAR*/, GLuint wrapModel /*= GL_CLAMP_TO_EDGE*/,
		GLuint width /*= WINDOW_WIDTH*/, GLuint height /*= WINDOW_HEIGHT*/)
	{
		glGenFramebuffers(1, &frambuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frambuffer);

		glGenTextures(1, &texColorBuffer);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "frame buffer uncompleted " << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GetCubePts_withTexture(GLfloat* arr)
	{
		/*
		顶点和纹理坐标
		*/
		GLfloat pts[] =
		{
			// 	上
			-0.5, 0.5, -0.5, 0, 1,
			-0.5, 0.5, 0.5, 0, 0,
			0.5, 0.5, -0.5, 1, 1,
			-0.5, 0.5, 0.5, 0, 0,
			0.5, 0.5, 0.5, 1, 0,
			0.5, 0.5, -0.5, 1, 1,

			//下
			-0.5, -0.5, -0.5, 0, 1,
			0.5, -0.5, -0.5, 1, 1,
			0.5, -0.5, 0.5, 1, 0,
			-0.5, -0.5, -0.5, 0, 1,
			0.5, -0.5, 0.5, 1, 0,
			-0.5, -0.5, 0.5, 0, 0,

			//右
			0.5, 0.5, 0.5, 0, 1,
			0.5, -0.5, 0.5, 0, 0,
			0.5, -0.5, -0.5, 1, 0,
			0.5, 0.5, 0.5, 0, 1,
			0.5, -0.5, -0.5, 1, 0,
			0.5, 0.5, -0.5, 1, 1,

			//左
			-0.5, 0.5, 0.5, 0, 1,
			-0.5, 0.5, -0.5, 1, 1,
			-0.5, -0.5, -0.5, 1, 0,
			-0.5, 0.5, 0.5, 0, 1,
			-0.5, -0.5, -0.5, 1, 0,
			-0.5, -0.5, 0.5, 0, 0,

			//前
			-0.5, 0.5, 0.5, 0, 1,
			0.5, -0.5, 0.5, 1, 0,
			0.5, 0.5, 0.5, 1, 1,
			-0.5, 0.5, 0.5, 0, 1,
			-0.5, -0.5, 0.5, 0, 0,
			0.5, -0.5, 0.5, 1, 0,

			//后
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

	void DefaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
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

	void GetCubePts_withTextureNormal(GLfloat* arr)
	{
		/*
		顶点和纹理坐标
		*/
		GLfloat pts[] =
		{
			// 	上
			-0.5, 0.5, -0.5, 0, 1,  0, 1, 0,
			-0.5, 0.5, 0.5, 0, 0,   0, 1, 0,
			0.5, 0.5, -0.5, 1, 1,   0, 1, 0,
			-0.5, 0.5, 0.5, 0, 0,   0, 1, 0,
			0.5, 0.5, 0.5, 1, 0,    0, 1, 0,
			0.5, 0.5, -0.5, 1, 1,   0, 1, 0,

			//下
			-0.5, -0.5, -0.5, 0, 1,   0, -1, 0,
			0.5, -0.5, -0.5, 1, 1,    0, -1, 0,
			0.5, -0.5, 0.5, 1, 0,     0, -1, 0,
			-0.5, -0.5, -0.5, 0, 1,   0, -1, 0,
			0.5, -0.5, 0.5, 1, 0,     0, -1, 0,
			-0.5, -0.5, 0.5, 0, 0,    0, -1, 0,

			//右
			0.5, 0.5, 0.5, 0, 1,	1, 0, 0, 
			0.5, -0.5, 0.5, 0, 0,   1, 0, 0,
			0.5, -0.5, -0.5, 1, 0,  1, 0, 0,
			0.5, 0.5, 0.5, 0, 1,    1, 0, 0,
			0.5, -0.5, -0.5, 1, 0,  1, 0, 0,
			0.5, 0.5, -0.5, 1, 1,   1, 0, 0,

			//左
			-0.5, 0.5, 0.5, 0, 1,    -1, 0, 0,
			-0.5, 0.5, -0.5, 1, 1,   -1, 0, 0,
			-0.5, -0.5, -0.5, 1, 0,  -1, 0, 0,
			-0.5, 0.5, 0.5, 0, 1,    -1, 0, 0,
			-0.5, -0.5, -0.5, 1, 0,  -1, 0, 0,
			-0.5, -0.5, 0.5, 0, 0,   -1, 0, 0,

			//前
			-0.5, 0.5, 0.5, 0, 1,    0, 0, 1,
			0.5, -0.5, 0.5, 1, 0,    0, 0, 1,
			0.5, 0.5, 0.5, 1, 1,     0, 0, 1,

			-0.5, 0.5, 0.5, 0, 1,    0, 0, 1,
			-0.5, -0.5, 0.5, 0, 0,   0, 0, 1,
			0.5, -0.5, 0.5, 1, 0,    0, 0, 1,

			//后
			-0.5, 0.5, -0.5, 0, 1,    0, 0, -1,
			0.5, 0.5, -0.5, 1, 1,     0, 0, -1,
			0.5, -0.5, -0.5, 1, 0,    0, 0, -1,
			-0.5, 0.5, -0.5, 0, 1,    0, 0, -1,
			0.5, -0.5, -0.5, 1, 0,    0, 0, -1,
			-0.5, -0.5, -0.5, 0, 0,	  0, 0, -1
		};

		for (int i = 0; i < 288; i++)
		{
			arr[i] = pts[i];
		}

	}

	void CreatePlaneVAO(OUT GLuint& VAO)
	{
		GLuint VBO;

		static GLfloat pts[] =
		{
			//pos 			 //texture  //normal
			-0.5, 0.5, 0,    0, 1,    0, 0, 1,
			0.5, -0.5, 0,    1, 0,	  0, 0, 1,
			0.5, 0.5, 0,     1, 1,    0, 0, 1,

			-0.5, 0.5, 0,    0, 1,    0, 0, 1,
			-0.5, -0.5, 0,   0, 0,    0, 0, 1,
			0.5, -0.5, 0,    1, 0,    0, 0, 1,
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(3 * FLOAT_SIZE));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(5 * FLOAT_SIZE));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void CreateCubeVAO(OUT GLuint& VAO)
	{
		GLfloat cubePts[288];
		GetCubePts_withTextureNormal(cubePts);

		GLuint VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubePts), cubePts, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(3 * FLOAT_SIZE));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(5 * FLOAT_SIZE));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void* MemoryMalloc(size_t size)
	{
		return malloc(size);
	}

	void MemoryFree(void* pointer)
	{
		free(pointer);
	}

	GLfloat MathRadToDegf(const GLfloat radians)
	{
		return radians * 360.0f / (2.0f * PI);
	}

	GLfloat MathDegToRadf(const GLfloat degrees)
	{
		return degrees * 2.0f * PI / 360.0f;
	}

	GLfloat MathClampf(const GLfloat value, const GLfloat min, const GLfloat max)
	{
		if (value < min)
		{
			return min;
		}
		if (value > max)
		{
			return max;
		}
		return value;
	}

}