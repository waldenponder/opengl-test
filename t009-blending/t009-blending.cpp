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

void createCube(OUT GLuint& VAO)
{
	GLuint VBO;
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

void createSquare(OUT GLuint& VAO)
{
	GLuint VBO, EBO;

	GLfloat x1,  y1; GLfloat x2, y2;

	x1 = y1 = 0;
	x2 = y2 = 1;
	static GLfloat pts[] =
	{
		x1, y1, 0.0f, 0, 0, 1, 0.0f, 0.0f,  // 左下角
		x2, y1, 0.0f, 0, 1, 0, 1.0f, 0.0f,  // 右下角
		x2, y2, 0.0f, 1, 0, 0, 1.0f, 1.0f,  // 右上角
		x1, y2, 0.0f, 1, 1, 0, 0.0f, 1.0f  // 左上角
	};

	static GLuint indices[] =
	{ // 注意索引从0开始!
		0, 1, 2, // 第一个三角形
		0, 2, 3  // 第二个三角形
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(3 * FLOAT_SIZE));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(6 * FLOAT_SIZE));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int _tmain(int argc, _TCHAR* argv[])
{

	tools::GetCubePts_withTextureNormal(cubePts);

	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);
	g_Mat4 = glm::mat4(1.0);

	GLuint cubeVAO, squareVAO;
	createCube(cubeVAO);
	createSquare(squareVAO);

	GLuint floor = tools::CreateTexture("../common/src/floor.jpg");
	GLuint grass = tools::CreateTexture("../common/src/grass.png");
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

		glBindVertexArray(squareVAO);
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