#include "stdafx.h"
#include "../common/common.out.h"
/*

*/
void RenderScene(Shader& shader, Shader& shader2, GLuint texture);
void CreateVAO(GLuint& VAO, GLuint& VBO);
void CreateFBO(GLuint& hdrFBO);

GLfloat cubePts[180];
GLuint g_colorBuffers[2];

int _tmain(int argc, _TCHAR* argv[])
{
	tools::GetCubePts_withTexture(cubePts);

	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, tools::DefaultKeyCallback);
	g_Mat4 = glm::mat4(1.0);

	GLuint VAO, VBO;
	CreateVAO(VAO, VBO);

	GLuint sperateFBO;
	CreateFBO(sperateFBO);

	GLuint combineFBO, combineTex, rbo;
	tools::CreateFBO(combineFBO, combineTex);

	GLuint containerTex = tools::CreateTexture("../common/src/container.jpg");
	Shader shader("vert007.v", "frag007.f");
	Shader shader2("vert007_2.v", "frag007_2.f");
		   	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glBindVertexArray(VAO);
		
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
												 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(.2, .3, .6, 1);
		glClearStencil(0);

		glBindFramebuffer(GL_FRAMEBUFFER, combineFBO);
						   
		RenderScene(shader, shader2, containerTex);
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		Rectangle rect;
		//rect.SetShader(shader);
		rect.SetTexture(combineTex);
		rect.Draw();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

void RenderScene(Shader& shader, Shader& shader2, GLuint text)
{
	//2	 渲染边框
	float s = 1.02f;
	glm::mat4 Mat2 = glm::scale(g_Mat4, glm::vec3(s, s, s));
	//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	////禁止模板缓存
	//glStencilMask(0x00);
	shader2.Use();
	shader2.setUniformMat4f("vert_mat", Mat2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glStencilMask(0xFF);

	//1	 正常渲染
	glm::mat4 Mat1 = g_Mat4;
	////调用后模板缓存区值为1
	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
	////允许写入模板缓存
	//glStencilMask(0xFF);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	shader.Use();
	shader.setUniformMat4f("vert_mat", Mat1);
	shader.setUniformTexture2D("SAMP", text, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CreateVAO(GLuint& VAO, GLuint& VBO)
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

void CreateFBO(GLuint& hdrFBO)
{
	glGenFramebuffers(1, &hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	glGenTextures(2, g_colorBuffers);
	for (GLuint i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, g_colorBuffers[i]);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGB16F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL
			);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// attach texture to framebuffer
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, g_colorBuffers[i], 0
			);
	}
}

