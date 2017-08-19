#include "stdafx.h"
#include "../common/common.out.h"

GLuint createVAO()
{
	float v = .5f;

#if 0
	float pts[] =
	{
		-v, -v,    1, .6, 0,
		v, -v,     .6, 1, 0,
		v, v,      0, .7, 1,
		-v, v,     .5, 0, 1,
	};
#else
	float pts[] =
	{
		-.5, -.5,   1, .6, 0,
		0, -.6,     .6, 1, 0,
		.3, -.3,      0, .7, 1,
		.5, .2,     .5, 0, 1,
	};
#endif

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

	Shader shader("vert015.glsl", "frag015.glsl" , "geom015.glsl");
	Shader shader2("vert015.glsl", "frag015.glsl");

	GLuint VAO = createVAO();

	glBindVertexArray(VAO);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(CLEAR_COLOR);
		glEnable(GL_PROGRAM_POINT_SIZE);

		shader.Use();
		glDrawArrays(GL_LINES_ADJACENCY, 0, 4);

		shader2.Use();
		glDrawArrays(GL_POINTS, 0, 4);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}