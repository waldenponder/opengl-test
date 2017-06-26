
/*
选中效果
*/

#include "stdafx.h"
#include "../common/com_include.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GLfloat cubePts[180];
	tools::GetCubePts(cubePts);

	GLFWwindow* window; 
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);

	GLuint VAO, VBO;
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubePts), cubePts, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * FLOAT_SIZE, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * FLOAT_SIZE, (void*)(3 * FLOAT_SIZE));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLuint texture = tools::CreateTexture("../common/src/container.jpg");
	Shader shader("vert004.v", "frag004.f");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(.5, .3, .6, 1);

		shader.Use();
		shader.setUniformTexture2D("SAMP", texture, 0);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	
	glfwSwapBuffers(window);

	return 0;
}