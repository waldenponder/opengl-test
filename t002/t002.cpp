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

	Shader shader("vert002.v", "frag002.f");

	GLuint VBO, VAO, EBO;
	{
		GLfloat pts[] =
		{
			0.5f, 0.5f, 0.0f, 1, 0, 0,     1.0f, 1.0f,  // 右上角
			0.5f, -0.5f, 0.0f, 0, 1, 0,    1.0f, 0.0f,  // 右下角
			-0.5f, -0.5f, 0.0f, 0, 0, 1,   0.0f, 0.0f,  // 左下角
			-0.5f, 0.5f, 0.0f, 1, 1, 0,    0.0f, 1.0f  // 左上角
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

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(3 * FLOAT_SIZE));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * FLOAT_SIZE, (void*)(6 * FLOAT_SIZE));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	GLuint texture = tools::CreateTexture("../common/src/tt.jpg");
	GLuint texture2 = tools::CreateTexture("../common/src/container.jpg");
	 
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(color1, color2, color3, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat time = glfwGetTime();
		GLfloat color_g = sin(time) / 2.0 + 0.5;
		GLfloat color_b = sin(time) / 2.0 + 0.4;
	
		shader.setUniformVec4f("myColor", 0.0f, color_g, color_b, 1.0f);
		shader.setUniformTexture2D("sampler", texture, 0);
		shader.setUniformTexture2D("sampler2", texture2, 1);
		shader.Use();

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}