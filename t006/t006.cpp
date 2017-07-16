/*
»ù´¡ÒõÓ°
*/

#include "stdafx.h"
#include "../common/common.out.h"

GLfloat cubePts[288];

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

	TMP = glm::translate(identy, TVec3(9, 14, 24));
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WINDOW_WIDTH,
		WINDOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//GLuint depthMap;
	//glGenTextures(1, &depthMap);
	//glBindTexture(GL_TEXTURE_2D, depthMap);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	tools::GetCubePts_withTextureNormal(cubePts);
	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);
	g_Mat4 = glm::mat4(1.0);

	GLuint VAO, VBO;
	createVAO(VAO, VBO);

	GLuint depthTexture, depthFbo;
	createShadowMap(depthTexture, depthFbo);

	//GLuint tex = tools::CreateTexture("../common/src/floor.jpg");
	
	Shader shader("vert006.v", "frag006.f");
	Shader shaderDepth("vert006_2.v", "frag006_2.f");

	vector<glm::mat4> modelMats;
	setUpScene(modelMats);

	TVec3 lightPos(59, 30, 0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		float value = 30;
		TMat4 lightSpace;
		lightPos = TMat3(glm::rotate(glm::mat4(1.0), .4f, Y_AXIS)) * lightPos;
		TMat4 projection = glm::ortho(-value, value, -value, value, 0.1f, 1000.f);

		//1
		glBindFramebuffer(GL_FRAMEBUFFER, depthFbo);
		{
			glEnable(GL_DEPTH_TEST);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, depthTexture);

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
		}
		  
		//2
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 0, 1);

			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CCW);
			glCullFace(GL_BACK);

			TMat4 view = Camera::Instance()->GetViewMatrix();
			//TMat4 projection = Camera::Instance()->GetProjectionMatrix();

			//glEnable(GL_DEPTH_TEST);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			shader.Use();

			shader.setUniformMat4f("uView", view);
			shader.setUniformMat4f("uProjection", projection);

			//shader.setUniformTexture2D("uSAMP", tex, 0);
			shader.setUniformTexture2D("uDepthTexture", depthTexture, 0);

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