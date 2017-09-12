#include "stdafx.h"
#include "../common/common.out.h"

unsigned g_PBO;
int g_size = WINDOW_WIDTH * WINDOW_HEIGHT * 4;

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

void screenCapture()
{
	unsigned char *mpixels = new unsigned char[g_size];
#if 0
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, mpixels);
	glReadBuffer(GL_BACK);
#else
	glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	unsigned char* PTR = (unsigned char*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
	memcpy(mpixels, PTR, g_size);
	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
#endif

	for (int i = 0; i < g_size; i += 4)
	{
		mpixels[i] ^= mpixels[i + 2] ^= mpixels[i] ^= mpixels[i + 2];
	}
	FIBITMAP* bitmap = FreeImage_Allocate(WINDOW_WIDTH, WINDOW_HEIGHT, 32, 8, 8, 8);

	for (int y = 0; y < FreeImage_GetHeight(bitmap); y++)
	{
		BYTE *bits = FreeImage_GetScanLine(bitmap, y);
		for (int x = 0; x < FreeImage_GetWidth(bitmap); x++)
		{
			bits[0] = mpixels[(y * WINDOW_WIDTH + x) * 4 + 0];
			bits[1] = mpixels[(y * WINDOW_WIDTH + x) * 4 + 1];
			bits[2] = mpixels[(y * WINDOW_WIDTH + x) * 4 + 2];
			bits[3] = 255;
			bits += 4;

		}
	}
	bool bSuccess = FreeImage_Save(FIF_PNG, bitmap, "123321.png", PNG_DEFAULT);
	FreeImage_Unload(bitmap);
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

	glGenBuffers(1, &g_PBO);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, g_PBO);
	glBufferData(GL_PIXEL_PACK_BUFFER, g_size, NULL, GL_STREAM_READ);

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
			screenCapture();
		}

		glfwSwapBuffers(window);

		FRAME_RATE_END;
	}

	glfwTerminate();

	return 0;
}