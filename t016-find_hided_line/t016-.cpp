/*
 帧缓冲,  渲染到纹理
*/
#include "stdafx.h"
#include "../common/common.out.h"

/*
VAO VBO EBO   纹理
*/
using namespace std;

#if 0
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

GLuint PROGRAM;
GLuint VBO, VA0, EOB;

void init_render()
{
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

		PROGRAM = glCreateProgram();
		glAttachShader(PROGRAM, vertShader);
		glAttachShader(PROGRAM, fragShader);
		glLinkProgram(PROGRAM);

		glGetProgramiv(PROGRAM, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(PROGRAM, 512, NULL, info);
			cout << "link err " << endl << info << endl;
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

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
}

#endif

int g_size = WINDOW_WIDTH * WINDOW_WIDTH * 4;

void screenCapture()
{
	GLuint g_PBO;
	glGenBuffers(1, &g_PBO);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, g_PBO);
	glBufferData(GL_PIXEL_PACK_BUFFER, g_size, NULL, GL_STREAM_READ);

	unsigned char *mpixels = new unsigned char[g_size];
#if 0
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, mpixels);
	glReadBuffer(GL_BACK);
#else
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	//glReadBuffer(GL_BACK);

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
	bool bSuccess = FreeImage_Save(FIF_PNG, bitmap, "E:\\aabbcc3.png", PNG_DEFAULT);
	FreeImage_Unload(bitmap);
}
//http://cn.voidcc.com/question/p-xqbbkaxn-ev.html
void main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();

	//-------------------------------------------------创建framebuffer
	GLuint renderbuffer, framebuffer;
	glGenRenderbuffers(1, &renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT);
	// 生成&绑定FrameBuffer
	glGenFramebuffers(1, &framebuffer);
	//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, renderbuffer);
	// Renderbuffer关联到FrameBuffer
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer);
	//-------------------------------------------------
	
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	// 渲染到Framebuffer
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glfwSwapBuffers(window);
	screenCapture();
	getchar();
}