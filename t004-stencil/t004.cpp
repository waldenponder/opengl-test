
/*
选中效果
*/

#include "stdafx.h"
#include "../common/common.out.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GLfloat cubePts[180];
	Utility::GetCubePts_withTexture(cubePts);

	GLFWwindow* window; 
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, Utility::DefaultKeyCallback);
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
	Shader shader("vert004.glsl", "frag004.glsl");
	Shader shader2("vert004_2.glsl", "frag004_2.glsl");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//不调用结果奇怪
	glEnable(GL_CULL_FACE);
	glBindVertexArray(VAO);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(.2, .3, .6, 1);
		glClearStencil(123);
				  
		//1	 正常渲染
		glm::mat4 Mat1 = g_Mat4;
		//调用后模板缓存区值为1
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//允许写入模板缓存
		glStencilMask(0xFF);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		shader.Use();
		shader.setUniformMat4f("vert_mat", Mat1);
		shader.setUniformTexture2D("SAMP", texture, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//2	 渲染边框
		float s = 1.02f;
		glm::mat4 Mat2 = glm::scale(g_Mat4, glm::vec3(s, s, s));
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//禁止模板缓存
		glStencilMask(0x00);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glLineWidth(3);
		shader2.Use();
		shader2.setUniformMat4f("vert_mat", Mat2);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glStencilMask(0xFF);

		glfwSwapBuffers(window);
	}
	
	glfwSwapBuffers(window);

	return 0;
}