/*
»ù´¡ÒõÓ°
*/

#include "stdafx.h"
#include "../common/common.out.h"

GLfloat cubePts[288];
const GLuint SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

void setUpScene(OUT vector<glm::mat4>& modelMats)
{
	TMat4 identy(1.0);

	TVec3 v(50, 1, 50);
	auto TMP = glm::scale(identy, v);
	TMP = glm::rotate(TMP, 60.0f, X_AXIS);
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(20, 20, 0));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(5, 3, 1));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(6, 4, 8));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(9, 4, 24));
	TMP = glm::scale(TMP, TVec3(10, 10, 10));
	modelMats.push_back(TMP);
}

void createVAO(OUT GLuint& VAO, OUT GLuint& VBO)
{
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

void createShadowMap(OUT GLuint& tex, OUT GLuint& fbo)
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH,
		SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			  
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("FB error, status: 0x%x\n", Status);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Utility::GetCubePts_withTextureNormal(cubePts);
	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);
	g_Mat4 = glm::mat4(1.0);

	GLuint VAO, VBO;
	createVAO(VAO, VBO);

	GLuint depthTexture, depthFbo;
	createShadowMap(depthTexture, depthFbo);

	GLuint floorTex = Utility::CreateTexture("../common/src/floor.jpg");
	
	Shader shader("vert006.glsl", "frag006.glsl");
	Shader shaderDepth("vert006_2.glsl", "frag006_2.glsl");

	vector<glm::mat4> modelMats;
	setUpScene(modelMats);

	TVec3 lightPos(30, 30, 11);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		float value = 20;
		TMat4 lightSpace;
		TMat4 projection = glm::ortho(-value, value, -value, value, 0.1f, 600.glsl);
								 
		if (Camera::Instance()->_bNeedRotation)
			lightPos = TMat3(glm::rotate(glm::mat4(1.0), .4f, Y_AXIS)) * lightPos;

		//1
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthFbo);
		{
			glClear(GL_DEPTH_BUFFER_BIT);
			glCullFace(GL_FRONT);
			lightSpace = projection * glm::lookAt(lightPos, glm::vec3(0), Y_AXIS);

			shaderDepth.Use();
			shaderDepth.setUniformMat4f("uLightSpace", lightSpace);

			for (auto Mat : modelMats)
			{
				shaderDepth.setUniformMat4f("uModel", Mat);

				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);
			}
			glCullFace(GL_BACK);
		}
		  
		//2
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 0, 1);

			TMat4 view = Camera::Instance()->GetViewMatrix();
			TMat4 projection = Camera::Instance()->GetProjectionMatrix();

			shader.Use();

			shader.setUniformMat4f("uView", view);
			shader.setUniformMat4f("uProjection", projection);

			shader.setUniformTexture2D("uDepthTexture", depthTexture, 0);
			shader.setUniformTexture2D("uSAMP", floorTex, 1);
			shader.setUniformVec3f("uLightColor", 1, 1, 1);
			shader.setUniformVec3f("uLightPos", lightPos);
			shader.setUniformVec3f("uViewPos", CameraPos);
			shader.setUniformMat4f("uLightSpace", lightSpace);

			for (auto Mat : modelMats)
			{
				shader.setUniformMat4f("uModel", Mat);

				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);
			}
		}

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	  
	return 0;
}