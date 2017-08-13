#include "stdafx.h"
#include "../common/common.out.h"

#define  instance 50

#define  count 8

void setUpScene(OUT vector<glm::mat4>& modelMats)
{
	TMat4 identy(1.0);

	TVec3 v(5000, 1, 5000);
	auto TMP = glm::scale(identy, v);
	TMP = glm::rotate(TMP, 60.0f, X_AXIS);
	modelMats.push_back(TMP);
}


void setUpScene2(OUT vector<glm::mat4>& modelMats)
{
	TMat4 identy(1.0);

	auto TMP = glm::translate(identy, TVec3(2, 5, -10));
	TMP = glm::scale(TMP, TVec3(10, 10, 10));
	modelMats.push_back(TMP);
}

void createOffsetVBO(IN const GLuint& VAO)
{
#define  item_size 	 (sizeof(TVec3) * instance * instance * 4)

	srand((unsigned)time(0));
		  
	GLuint offsetVBO;
	glGenBuffers(1, &offsetVBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, offsetVBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * item_size * count, nullptr, GL_STATIC_DRAW);
										 
	for (int i = 0; i < count; i++) 
	{
		TVec3 translations[4 * instance * instance];
		{
			int index = 0;
			GLfloat offset = 1.0f;
		
			for (GLint y = -instance; y < instance; y += 3)
			{
				for (GLint x = -instance; x < instance; x += 3)
				{
					TVec3 translation;
					translation.x = (i + 1) * ((GLfloat)x / 3.5f + offset);
					translation.z = (i + 1)* ((GLfloat)y / 3.5f + offset);
					translation.y = 0;
					translations[index++] = translation;
				}
			}
		}

		glBufferSubData(GL_ARRAY_BUFFER, i * item_size, item_size, translations);
	}


	//并通知OpenGL解析这个VBO数据的方式：

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1); // 注意这里 指定1表示每个实例更新一次数据
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	GLFWwindow* window;
	PREPARE_GLFW_WINDOW(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, OnKeyDown);
	g_Mat4 = glm::mat4(1.0);

	GLuint cubeVAO, planeVAO;
	Utility::CreateCubeVAO(cubeVAO);
	Utility::CreatePlaneVAO(planeVAO);

	createOffsetVBO(planeVAO);

	GLuint brick = Utility::CreateTexture("../common/src/brick.png");
	GLuint grass = Utility::CreateTexture("../common/src/grass.png");
	Shader shader("vert011.v", "frag011.f");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);

	vector<TMat4> modelMats, modelMats2;
	setUpScene(modelMats);
	setUpScene2(modelMats2);

	TVec3 lightPos(50, 30, 0);

	Camera::Instance()->ConfigViewMatrix(TVec3(0, 60, 50), TVec3(), Y_AXIS);
	Camera::Instance()->_moveFactor = 100;

	shader.Use();
	shader.setUniformVec3f("uLightColor", 1, 1, 1);
		  
	while (!glfwWindowShouldClose(window))
	{			 
		long t = clock();

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(CLEAR_COLOR);

		TMat4 view = Camera::Instance()->GetViewMatrix();
		TMat4 projection = Camera::Instance()->GetProjectionMatrix();

		if (Camera::Instance()->_bNeedRotation)
			lightPos = TMat3(glm::rotate(glm::mat4(1.0), 0.5f, Y_AXIS)) * lightPos;
				  
		shader.setUniformVec3f("uLightPos", lightPos);
		shader.setUniformVec3f("uViewPos", CameraPos);
		shader.setUniformMat4f("uView", view);
		shader.setUniformMat4f("uProjection", projection);
				  
		//地板
		if (1)
		{
			glBindVertexArray(cubeVAO);
			shader.setUniformTexture2D("uSAMP", brick, 0);
			shader.setUniform1f("uTexCoordScale", 1000);
			shader.setUniformMat4f("uModel", modelMats[0]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
			  
		 //草
		if (1)
		{
			glBindVertexArray(planeVAO);
			shader.setUniformTexture2D("uSAMP", grass, 1);
			shader.setUniform1f("uTexCoordScale", 1);
			shader.setUniformMat4f("uModel", modelMats2[0]);
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 4 * instance * instance * count);
		}


		glfwSwapBuffers(window);

		cout << "elipse : " << (clock() - t) << "        count:  " << (4 * instance * instance * count) << endl;
	}

	glfwTerminate();

	return 0;
}