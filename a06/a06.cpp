#include "stdafx.h"
#include "../common/common.out.h"
#include "Background.h"

#if 0

/**
* The number of waves. Also has to be changed in the shader.
*/
#define NUMBERWAVES 4

/**
* Length (width and height) of the water surface,
*/
#define WATER_PLANE_LENGTH 128

/**
* Size of the normal map texture.
*/
#define TEXTURE_SIZE 1024

GLuint g_verticesVBO;
GLuint g_indicesVBO;
GLuint g_cubeMape;

void init()
{
	GLfloat* points = (GLfloat*)malloc(WATER_PLANE_LENGTH * WATER_PLANE_LENGTH * 4 * sizeof(GLfloat));
	GLuint* indices = (GLuint*)malloc(WATER_PLANE_LENGTH * (WATER_PLANE_LENGTH - 1) * 2 * sizeof(GLuint));

	GLuint x, z, i, k;

	GLuint waterTexture;

	for (z = 0; z < WATER_PLANE_LENGTH; z++)
	{
		for (x = 0; x < WATER_PLANE_LENGTH; x++)
		{
			points[(x + z * (WATER_PLANE_LENGTH)) * 4 + 0] = -(GLfloat)WATER_PLANE_LENGTH / 2 + 0.5f + (GLfloat)x;
			points[(x + z * (WATER_PLANE_LENGTH)) * 4 + 1] = 0.0f;
			points[(x + z * (WATER_PLANE_LENGTH)) * 4 + 2] = +(GLfloat)WATER_PLANE_LENGTH / 2 - 0.5f - (GLfloat)z;
			points[(x + z * (WATER_PLANE_LENGTH)) * 4 + 3] = 1.0f;
		}
	}

	for (k = 0; k < WATER_PLANE_LENGTH - 1; k++)
	{
		for (i = 0; i < WATER_PLANE_LENGTH; i++)
		{
			if (k % 2 == 0)
			{
				indices[(i + k * (WATER_PLANE_LENGTH)) * 2 + 0] = i + (k + 1) * WATER_PLANE_LENGTH;
				indices[(i + k * (WATER_PLANE_LENGTH)) * 2 + 1] = i + k * WATER_PLANE_LENGTH;
			}
			else
			{
				indices[(i + k * (WATER_PLANE_LENGTH)) * 2 + 0] = WATER_PLANE_LENGTH - 1 - i + k * WATER_PLANE_LENGTH;
				indices[(i + k * (WATER_PLANE_LENGTH)) * 2 + 1] = WATER_PLANE_LENGTH - 1 - i + (k + 1) * WATER_PLANE_LENGTH;
			}
		}
	}

	glGenBuffers(1, &g_verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, g_verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, WATER_PLANE_LENGTH * WATER_PLANE_LENGTH * 4 * sizeof(GLfloat), (GLfloat*)points, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, WATER_PLANE_LENGTH * (WATER_PLANE_LENGTH - 1) * 2 * sizeof(GLuint), (GLuint*)indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//

	free(points);
	free(indices);
}

void initTexture()
{
	vector<const char*> faceVec;
	faceVec.push_back("img/water_pos_x.tga"); faceVec.push_back("img/water_neg_x.tga");
	faceVec.push_back("img/water_pos_y.tga"); faceVec.push_back("img/water_neg_y.tga");
	faceVec.push_back("img/water_pos_z.tga"); faceVec.push_back("img/water_neg_z.tga");
	g_cubeMape = Utility::CreateCubemap(faceVec);
}

void setWaterShader(Shader& waterShader)
{
	waterShader.Use();
	waterShader.setUniform1f("u_waterPlaneLength", WATER_PLANE_LENGTH);
			   
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_cubeMape);
	waterShader.setUniform1i("u_cubemap", 0);
}

void setBackgroundShader(Shader& bgShader)
{
	bgShader.Use();
	


}

#endif

int _tmain(int argc, _TCHAR* argv[])
{
	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);

	glEnable(GL_DEPTH_TEST);

	Background backGround;
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(CLEAR_COLOR);
					
		backGround.render();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}