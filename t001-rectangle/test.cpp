#include "stdafx.h"
#include "../common/common.out.h"

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
		color3 = float(rand() % 255) /255.0;
	}
}

const GLchar* vert = "#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z,1.0);\n"
"}\0";

const GLchar* frag = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 myColor;\n"
"void main()\n"
"{\n"
"color = /*vec4(1.0f, 0.5f, 0.5f, 1.0f)*/myColor;\n"
"}\n\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "learn opengl", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewInit();

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glfwSetKeyCallback(window, key_callback);
	srand((unsigned)time(nullptr));

	GLuint program;
	{
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vert, NULL);
		glCompileShader(vertShader);
		GLint success;
		char info[512];

		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertShader, 512, NULL, info);
			cout << "定点着色器发生错误  " << info << endl;
		}

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &frag, NULL);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragShader, 512, NULL, info);
			cout << "片段着色器发生错误  " << info << endl;
		}
		
		program = glCreateProgram();
		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 512, NULL, info);
			cout << "link err " << endl << info << endl;
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	GLuint VBO, VA0, EOB;
	{
		GLfloat pts[] =
		{
			0.5f, 0.5f, 0.0f,   // 右上角
			0.5f, -0.5f, 0.0f,  // 右下角
			-0.5f, -0.5f, 0.0f, // 左下角
			-0.5f, 0.5f, 0.0f   // 左上角
		};

		GLuint indices[] =
		{ // 注意索引从0开始!
			0, 1, 3, // 第一个三角形
	   		1, 2, 3  // 第二个三角形
	     };

		glGenVertexArrays(1, &VA0);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EOB);

		glBindVertexArray(VA0);		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pts), pts, GL_STATIC_DRAW);		

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EOB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;


	while (!glfwWindowShouldClose(window))
	{
		GLfloat time = glfwGetTime();
		GLfloat color_g = sin(time) / 2.0 + 0.5;
		GLfloat color_b = sin(time) / 2.0 + 0.4;
		GLint loc = glGetUniformLocation(program, "myColor");
		glUniform4f(loc, 0.0f, color_g, color_b, 1.0f);

		glfwPollEvents();

		glClearColor(color1, color2, color3, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VA0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	
	return 0;
}