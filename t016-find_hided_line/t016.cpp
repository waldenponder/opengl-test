/*
 帧缓冲,  渲染到纹理
*/
#include "stdafx.h"
#include "../common/common.out.h"

using namespace std;
#define WINDOW_WIDTH 4096
#define WINDOW_HEIGHT 4096

int g_size = WINDOW_WIDTH * WINDOW_HEIGHT * 4;

GLfloat cubePts[180];
GLuint VAO, VBO;
void setUp() {
	Utility::GetCubePts_withTexture(cubePts);

	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubePts), cubePts, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * FLOAT_SIZE, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * FLOAT_SIZE, (void*)(3 * FLOAT_SIZE));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

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
			bits[3] = mpixels[(y * WINDOW_WIDTH + x) * 4 + 3];
			int t1 = bits[0];
			int t2 = bits[1];
			int t3 = bits[2];
			int t4 = bits[3];

			if (t1)
			{
				//cout << "\n";
			}
			bits[3] = 255;
			bits += 4;
		}
	}
	bool bSuccess = FreeImage_Save(FIF_PNG, bitmap, "E:\\aabbcc3.png", PNG_DEFAULT);
	FreeImage_Unload(bitmap);
}
//http://cn.voidcc.com/question/p-xqbbkaxn-ev.html

union ColorID
{
	explicit ColorID(unsigned int id_) : id(id_) {}
	ColorID(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_)
		: r(r_), g(g_), b(b_), a(a_)
	{
	}

	struct {
		unsigned char r, g, b, a;
	};
	unsigned int id;
};

void main()
{
	ColorID color(1230000);
	int r = color.r;
	int g = color.g;
	int b = color.b;
	int a = color.a;

	ColorID c2(r, g, b, a);
	unsigned int dd = c2.id;

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
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	{
		setUp();
		g_Mat4 = glm::mat4(1.0);
		Shader shader("vert_line_hided.glsl", "frag_line_hided.glsl");
		glBindVertexArray(VAO);

		glm::mat4 Mat1 = g_Mat4;

		shader.Use();
		shader.setUniformMat4f("vert_mat", Mat1);
		shader.setUniformVec4f("u_color", 230.0 / 255., 2. / 255., 150. / 255., 180. / 255.);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//glfwSwapBuffers(window);
	screenCapture();
	getchar();
}