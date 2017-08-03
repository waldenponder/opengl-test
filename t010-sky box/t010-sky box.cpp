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

int _tmain(int argc, _TCHAR* argv[])
{
	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);
	g_Mat4 = glm::mat4(1.0);

	GLuint cubeVAO, planeVAO;
	Utility::CreateCubeVAO(cubeVAO);
	Utility::CreatePlaneVAO(planeVAO);
     
	GLuint floor = Utility::CreateTexture("../common/src/floor.jpg");

	Shader shader("vert010.v", "frag010.f");
	Shader shader2("vert010_2.v", "frag010_2.f");

	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_CULL_FACE);
	}

	vector<const GLchar*> faces;
	faces.push_back("../common/src/skybox/right.jpg");
	faces.push_back("../common/src/skybox/left.jpg");

	faces.push_back("../common/src/skybox/top.jpg");
	faces.push_back("../common/src/skybox/bottom.jpg");

	faces.push_back("../common/src/skybox/front.jpg");
	faces.push_back("../common/src/skybox/back.jpg");

	GLuint cubemapTexture = Utility::CreateCubemap(faces);


	vector<TMat4> modelMats;
	setUpScene(modelMats);

	//Camera::Instance()->ConfigViewMatrix(TVec3(0, 0, -1), TVec3(), Y_AXIS);
	Camera::Instance()->ConfigViewMatrix(TVec3(0, 10, 50), TVec3(), Y_AXIS);

	TVec3 lightPos(50, 30, 0);
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(CLEAR_COLOR);

		TMat4 view = Camera::Instance()->GetViewMatrix();
		TMat4 projection = Camera::Instance()->GetProjectionMatrix();

		if (Camera::Instance()->_bNeedRotation)
			lightPos = TMat3(glm::rotate(glm::mat4(1.0), 0.05f, Y_AXIS)) * lightPos;
		
		glBindVertexArray(cubeVAO);

		//1
		shader.Use();
		shader.setUniformMat4f("uView", glm::mat4(glm::mat3(view)));
		shader.setUniformMat4f("uProjection", projection);
				   
		glDepthMask(GL_FALSE);

		shader.setUniformTextureCube("cubemap", cubemapTexture, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDepthMask(GL_TRUE);

		//2 
		shader2.Use();
		shader2.setUniformMat4f("uView", view);
		shader.setUniformMat4f("uProjection", projection);

		shader2.setUniformTexture2D("uSAMP", floor, 0);
		shader2.setUniformVec3f("uLightColor", 1, 1, 1);
		shader2.setUniformVec3f("uLightPos", lightPos);
		shader2.setUniformVec3f("uViewPos", CameraPos);

		for (auto Mat : modelMats)
		{
			shader2.setUniformMat4f("uModel", Mat);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}