#include "stdafx.h"
#include "../common/common.out.h"

/*

fragment两种纹理混合

VAO VBO EBO   纹理
*/
using namespace std;

float color1 = 0.1;
float color2 = 0.1;
float color3 = 0.1;

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
}

GLuint createVao()
{
	GLuint VBO, VAO, EBO;
	float val = 0.95f;
	GLfloat pts[] =
	{
		val, val, 0.0f, 1, 0, 0, 1.0f, 1.0f,  // 右上角
		val, -val, 0.0f, 0, 1, 0, 1.0f, 0.0f,  // 右下角
		-val, -val, 0.0f, 0, 0, 1, 0.0f, 0.0f,  // 左下角
		-val, val, 0.0f, 1, 1, 0, 0.0f, 1.0f  // 左上角
	};

	GLuint indices[] =
	{ // 注意索引从0开始!
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
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
	
	return VAO;
}

GLuint createFBO(int w, int  h)
{
	GLuint fbo, renderBuffer[2];

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	glGenRenderbuffers(2, renderBuffer);
	{
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer[0]);  //color
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, w, h);

		glBindFramebuffer(GL_RENDERBUFFER, renderBuffer[1]); //depth
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);
	}
	
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer[0]);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer[1]);

	glEnable(GL_DEPTH_TEST);

	return fbo;
}

int main()
{
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
	srand((unsigned)time(nullptr));

	Shader shader("verta003.glsl", "fraga003.glsl");

	GLuint VAO = createVao();
	GLuint FBO = createFBO(w, h);

	GLuint tex = Utility::CreateTexture("../common/src/tt.jpg");
	GLuint tex2 = Utility::CreateTexture("../common/src/container.jpg");


	while (!glfwWindowShouldClose(window))
	{

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);

		glfwPollEvents();

		glClearColor(CLEAR_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat time = glfwGetTime();
		GLfloat color_g = sin(time) / 2.0 + 0.5;
		GLfloat color_b = sin(time) / 2.0 + 0.4;

		shader.setUniformVec4f("myColor", 0.0f, color_g, color_b, 1.0f);
		shader.setUniformTexture2D("sampler", tex, 0);
		shader.setUniformTexture2D("sampler2", tex2, 1);
		shader.Use();

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		///////////////////////////////
		glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		glClearColor(CLEAR_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBlitFramebuffer(0, 0, w, h, 0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
																				   
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}