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

GLuint createPBOandTextures(GLuint* textures)
{
	glGenTextures(6, textures);

	int size = WINDOW_WIDTH * WINDOW_HEIGHT * 4;
	void* data = malloc(size);
	memset(data, 0, size);

	for (int i = 0; i < 6; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	GLuint PBO;
	glGenBuffers(1, &PBO);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, PBO);
	glBufferData(GL_PIXEL_PACK_BUFFER, size, data, GL_DYNAMIC_COPY);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	return PBO;
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

	Shader shader("vert_a002.glsl", "frag_a002.glsl");
	Shader shader2("vert_a002_2.glsl", "frag_a002_2.glsl");

	vector<const GLchar*> faces;
	faces.push_back("../common/src/skybox/right.jpg");	//x+
	faces.push_back("../common/src/skybox/left.jpg");

	faces.push_back("../common/src/skybox/top.jpg");  //y+
	faces.push_back("../common/src/skybox/bottom.jpg");

	faces.push_back("../common/src/skybox/front.jpg"); //Z+
	faces.push_back("../common/src/skybox/back.jpg");

	GLuint cubemapTexture = Utility::CreateCubemap(faces);


	vector<TMat4> modelMats;
	setUpScene(modelMats);

	Camera::Instance()->ConfigViewMatrix(TVec3(35, 10, -36), TQuat(0, 0, 0, 1), Y_AXIS);

	TVec3 lightPos(50, 30, 0);

	glEnable(GL_DEPTH_TEST);

	GLuint textures[6];
	GLuint PBO = createPBOandTextures(textures);

	while (!glfwWindowShouldClose(window))
	{
		FRAME_RATE_BEGIN;

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
		shader2.setUniformMat4f("uProjection", projection);

		shader2.setUniformTexture2D("uSAMP", floor, 0);
		shader2.setUniformVec3f("uLightColor", 1, 1, 1);
		shader2.setUniformVec3f("uLightPos", lightPos);
		shader2.setUniformVec3f("uViewPos", CameraPos);

		for (auto Mat : modelMats)
		{
			shader2.setUniformMat4f("uModel", Mat);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		if (Camera::Instance()->_bTrigger)
		{
			Camera::Instance()->_bTrigger = false;
		}

		glfwSwapBuffers(window);

		FRAME_RATE_END;
	}

	glfwTerminate();

	return 0;
}