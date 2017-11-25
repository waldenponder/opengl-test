
/*
选中效果
*/

#include "stdafx.h"
#include "../common/common.out.h"
Shader* g_shader = nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_SPACE)
	{
		if (g_shader) delete g_shader;

		g_shader = new Shader("woodVert.glsl", "woodFrag.glsl");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	GLfloat cubePts[180];
	Utility::GetCubePts_withTexture(cubePts);

	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, Utility::DefaultKeyCallback);
	//glfwSetKeyCallback(window, key_callback);

	g_Mat4 = glm::mat4(1.0);
	
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

	GLuint texture = Utility::CreateTexture("../common/src/container.jpg");
	//Shader shader("brickVert.glsl", "brickFrag.glsl");
	//Shader shader("stripeVert.glsl", "stripeFrag.glsl");
	//Shader shader("woodVert.glsl", "woodFrag.glsl");

	glEnable(GL_DEPTH_TEST);
	glBindVertexArray(VAO);


	while (!glfwWindowShouldClose(window))
	{
		g_shader = new Shader("woodVert.glsl", "woodFrag.glsl");

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(.2, .3, .6, 1);

		glm::mat4 Mat1 = g_Mat4;
		g_shader->Use();
		g_shader->setUniformMat4f("vert_mat", Mat1);
		g_shader->setUniformTexture2D("SAMP", texture, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
	}

	glfwSwapBuffers(window);

	return 0;
}