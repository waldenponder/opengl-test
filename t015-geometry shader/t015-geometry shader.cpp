#include "stdafx.h"
#include "../common/common.out.h"

GLuint createVAO()
{
	float v = .5f;

	float pts[] =
	{
		-v, -v,    1, .6, 0,
		v, -v,     .6, 1, 0,
		v, v,      0, .7, 1,
		-v, v,     .5, 0, 1,
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * FLOAT_SIZE, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * FLOAT_SIZE, (void*)(2 * FLOAT_SIZE));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

int _tmain(int argc, _TCHAR* argv[])
{
	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);
	g_Mat4 = glm::mat4(1.0);

	Shader shader("vert015.glsl", "frag015.glsl", "geom015.glsl");

	GLuint VAO = createVAO();

	shader.Use();
	glBindVertexArray(VAO);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(CLEAR_COLOR);
		glEnable(GL_PROGRAM_POINT_SIZE);

		glDrawArrays(GL_POINTS, 0, 4);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}