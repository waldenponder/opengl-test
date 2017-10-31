#include "stdafx.h"
#include "../common/common.out.h"

int ptCount = 0;
GLuint createVAO()
{
	GLuint VBO, VA0, EOB;
	{
		GLfloat pts[] =
		{
			0.5f, .9, 0.0f,
			0.5f, 0.5f, 0.0f,   // 右上角
			0.5f, -0.5f, 0.0f,  // 右下角
			-0.5f, -0.5f, 0.0f, // 左下角
			-0.5f, 0.5f, 0.0f   // 左上角
		};

		float xStart = .0, yStart = .0;
		float delta = .1;

		GLuint indices[] =
		{ // 注意索引从0开始!
			0, 1, 2, 3, // 第一个三角形
			//1, 2, 3  // 第二个三角形
		};

		glGenVertexArrays(1, &VA0);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EOB);

		glBindVertexArray(VA0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EOB);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	return VA0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);
	g_Mat4 = glm::mat4(1.0);

	GLuint VAO = createVAO();

	Shader shader("vert_a002.glsl", "frag_a002.glsl");
	Camera::Instance()->ConfigViewMatrix(TVec3(), TQuat(0, 0, 0, 1), Y_AXIS);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(CLEAR_COLOR);

		TMat4 view = Camera::Instance()->GetViewMatrix();
		TMat4 projection = Camera::Instance()->GetProjectionMatrix();

		shader.Use();
		shader.setUniformMat4f("uView", glm::mat4(glm::mat3(view)));
		shader.setUniformMat4f("uProjection", projection);

		glBindVertexArray(VAO);

		//	glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, 0);
		//	glDrawArrays(GL_LINE, 0, ptCount);

		glDrawArrays(GL_LINE_STRIP, 0, 5);

		if (Camera::Instance()->_bTrigger)
		{
			Camera::Instance()->_bTrigger = false;
		}

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}