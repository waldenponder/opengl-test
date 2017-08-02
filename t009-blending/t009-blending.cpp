#include "stdafx.h"
#include "../common/common.out.h"



void setUpScene(OUT vector<glm::mat4>& modelMats)
{
	TMat4 identy(1.0);

	TVec3 v(50, 1, 50);
	auto TMP = glm::scale(identy, v);
	TMP = glm::rotate(TMP, 60.0f, X_AXIS);
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(20, 2, 0));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(5, 3, 1));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(6, 4, -1));
	modelMats.push_back(TMP);

	TMP = glm::translate(TMP, TVec3(-8, 0, -18));
	TMP = glm::scale(TMP, TVec3(10, 10, 10));
	modelMats.push_back(TMP);
}


void setUpScene2(OUT vector<glm::mat4>& modelMats)
{
	TMat4 identy(1.0);

	auto TMP = glm::translate(identy, TVec3(20, 2, -10));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(15, 3, -1));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(6, 4, 8));
	modelMats.push_back(TMP);

	TMP = glm::translate(identy, TVec3(-8, 0, 18));
	TMP = glm::scale(TMP, TVec3(10, 10, 10));
	modelMats.push_back(TMP);
}


int _tmain(int argc, _TCHAR* argv[])
{
	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);
	g_Mat4 = glm::mat4(1.0);

	GLuint cubeVAO, planeVAO;
	Utility::CreateCubeVAO(cubeVAO);
	Utility::CreatePlaneVAO(planeVAO);

	GLuint floor = Utility::CreateTexture("../common/src/floor.jpg");
	GLuint grass = Utility::CreateTexture("../common/src/grass.png");
	Shader shader("vert009.v", "frag009.f");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			  
	vector<TMat4> modelMats;
	setUpScene(modelMats);

	vector<TMat4> modelMats2;
	setUpScene2(modelMats2);

	TVec3 lightPos(50, 30, 0);
	
	Camera::Instance()->ConfigViewMatrix(TVec3(0, 10, 50), TVec3(), Y_AXIS);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);

		glDisable(GL_CULL_FACE);

		TMat4 view = Camera::Instance()->GetViewMatrix();
		TMat4 projection = Camera::Instance()->GetProjectionMatrix();

		if (Camera::Instance()->_bNeedRotation)
			lightPos = TMat3(glm::rotate(glm::mat4(1.0), 0.05f, Y_AXIS)) * lightPos;
		
		glBindVertexArray(cubeVAO);
		shader.Use();

		for (auto Mat : modelMats)
		{
			shader.setUniformMat4f("uModel", Mat);
			shader.setUniformMat4f("uView", view);
			shader.setUniformMat4f("uProjection", projection);

			shader.setUniformTexture2D("uSAMP", floor, 0);
			shader.setUniformVec3f("uLightColor", 1, 1, 1);
			shader.setUniformVec3f("uLightPos", lightPos);
			shader.setUniformVec3f("uViewPos", CameraPos);
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(planeVAO);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (auto Mat : modelMats2)
		{
			shader.setUniformMat4f("uModel", Mat);
			shader.setUniformMat4f("uView", view);
			shader.setUniformMat4f("uProjection", projection);

			shader.setUniformTexture2D("uSAMP", grass, 1);
			shader.setUniformVec3f("uLightColor", 1, 1, 1);
			shader.setUniformVec3f("uLightPos", lightPos);
			shader.setUniformVec3f("uViewPos", CameraPos);
				
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}


		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}