#include "stdafx.h"
#include "../common/common.out.h"

#define WINDOW_WIDTH  800  
#define WINDOW_HEIGHT 600  

void initScene(int w, int h)
{
	// 启用阴影平滑  
	glShadeModel(GL_SMOOTH);
	// 黑色背景  
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// 设置深度缓存  
	glClearDepth(1.0);
	// 启用深度测试  
	glEnable(GL_DEPTH_TEST);
	// 所作深度测试的类型  
	glDepthFunc(GL_LEQUAL);
	// 告诉系统对透视进行修正  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//这里进行所有的绘图工作  
void  drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                   // Reset The View  
	glTranslatef(0.0f, 0.0f, -5.0f);
	//绘制一个正方形  
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	// 交换缓冲区  
	glfwSwapBuffers();
}
//重置窗口大小后的回调函数  
void GLFWCALL resizeGL(int width, int height)
{
	// 防止窗口大小变为0  
	if (height == 0)
	{
		height = 1;
	}
	// 重置当前的视口  
	glViewport(0, 0, (GLint)width, (GLint)height);
	// 选择投影矩阵  
	glMatrixMode(GL_PROJECTION);
	// 重置投影矩阵  
	glLoadIdentity();
	// 设置视口的大小  
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	// 选择模型观察矩阵  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(void)
{
	//记录程序运行状态  
	int running = GL_TRUE;
	//初始化 GLFW  
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	// 创建一个OpenGL 窗口  
	if (!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 6, 6, 6, 0, 32, 0, GLFW_WINDOW))
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//初始化OpenGL窗口  
	initScene(WINDOW_WIDTH, WINDOW_HEIGHT);
	//设置窗口大小发生变化时的回调函数  
	glfwSetWindowSizeCallback(resizeGL);
	//主循环  
	while (running)
	{
		// OpenGL rendering goes here...  
		glClear(GL_COLOR_BUFFER_BIT);
		// 当按下ESC键的时候触发  
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
		drawScene();
		//延时0.05秒  
		glfwSleep(0.05);
	}
	glfwTerminate();
	//退出程序  
	exit(EXIT_SUCCESS);
}