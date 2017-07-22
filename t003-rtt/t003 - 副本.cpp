/*
 帧缓冲
*/
#include "stdafx.h"
#include "../common/com_include.h"

/*
VAO VBO EBO   纹理
*/
using namespace std;

float color1 = 0.1;
float color2 = 0.3;
float color3 = 0.4;

glm::mat4 g_mat;
bool g_b_line = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_1)
	{
		color1 = float(rand() % 255) / 255.0;
	}
	else if (key == GLFW_KEY_2)
	{
		color2 = float(rand() % 255) / 255.0;
	}
	else if (key == GLFW_KEY_3)
	{
		color3 = float(rand() % 255) / 255.0;
	}
	else if (key == GLFW_KEY_A)
	{
		glm::vec3 axis(0, 0, 1);
		g_mat = glm::rotate(g_mat, 3.0f, axis);
	}
	else if (key == GLFW_KEY_B)
	{
		glm::vec3 axis(0, 1, 0);
		g_mat = glm::rotate(g_mat, 3.0f, axis);
	}
	else if (key == GLFW_KEY_C)
	{
		glm::vec3 axis(1, 0, 0);
		g_mat = glm::rotate(g_mat, 3.0f, axis);
	}
	else if (key == GLFW_KEY_D)
	{
		glm::vec3 axis(1, 0, 0);
		g_mat = glm::translate(g_mat, axis);
	}
	else if (key == GLFW_KEY_E)
	{
		glm::vec3 axis(0, 1, 0);
		g_mat = glm::translate(g_mat, axis);
	}
	else if (key == GLFW_KEY_F)
	{
		glm::vec3 axis(0, 0, 1);
		g_mat = glm::translate(g_mat, axis);
	}
	else if (key == GLFW_KEY_W && action == 1)
	{
		g_b_line = !g_b_line;
	}
}

GLfloat quadVertices[] =
{
	// Positions   // TexCoords
	-1.0f, 1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 0.0f,

	-1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f
};

int main()
{
	GLfloat cubePts[180];
	tools::GetCubePts(cubePts);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(1200, 900, "learn opengl", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewInit();

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glfwSetKeyCallback(window, key_callback);

	GLuint VAO, VBO;
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubePts), cubePts, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * FLOAT_SIZE, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * FLOAT_SIZE, (void*) (3 * FLOAT_SIZE ));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	GLuint quadVAO, quadVBO;
	{
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	GLuint frambuffer, texColorBuffer;
	{
		glGenFramebuffers(1, &frambuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frambuffer);

		glGenTextures(1, &texColorBuffer);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1200, 900, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
		
		// 生成一个渲染缓存对象
		//GLuint RBO;
		//glGenRenderbuffers(1, &RBO);
		//glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1200, 900);
		//glBindRenderbuffer(GL_RENDERBUFFER, 0);
		//// 把渲染缓冲对象附加到深度模板附件上
		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			cout << "frame buffer uncompleted " << endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLuint texture = tools::CreateTexture("../common/src/container.jpg", GL_REPEAT, GL_LINEAR);
	
	Shader shader("vert003.v", "frag003.f");
	Shader shaderNew("vert003new.v", "frag003new.f");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		//1
		glBindFramebuffer(GL_FRAMEBUFFER, frambuffer);
		glClearColor(color1, color2, color3, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, g_b_line ? GL_LINE : GL_FILL);
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_ALWAYS);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		shader.setUniformMat4f("vert_mat", g_mat);
		shader.setUniformTexture2D("samp", texture, 0);

		shader.Use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//2
#if 1
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		//glDisable(GL_DEPTH_TEST);

		shaderNew.Use();
		shaderNew.setUniformMat4f("vert_mat", g_mat);
		shaderNew.setUniformTexture2D("sampNew", texColorBuffer, 0);
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
#endif

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}