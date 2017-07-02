
/*

*/

#include "stdafx.h"
#include "../common/common.out.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GLfloat cubePts[180];
	tools::GetCubePts(cubePts);

	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);
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

	GLuint texture = tools::CreateTexture("../common/src/container.jpg");
	Shader shader("vert005.v", "frag005.f");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	vector<glm::mat4> modelMats;

	TMat4 identy(1.0);
	for (int i = 0; i < 5; i++)
	{
		glm::vec3 v(0, i * 2, 0);
		auto TMP = glm::translate(identy, v);
		//TMP = glm::rotate(TMP, 5.0f, v);
		modelMats.push_back(TMP);
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(.2, .3, .6, 1);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		TMat4 view = Camera::Instance()->GetViewMatrix();
		TMat4 projection = Camera::Instance()->GetProjectionMatrix();

		for (auto Mat : modelMats)
		{
			glEnable(GL_DEPTH_TEST);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			shader.Use();
			shader.setUniformMat4f("model", Mat);
			shader.setUniformMat4f("view", view);
			shader.setUniformMat4f("projection", projection);
			shader.setUniformTexture2D("SAMP", texture, 0);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}