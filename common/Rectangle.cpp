#include "stdafx.h"
#include "Rectangle.h"
#include "Utility.h"

static float g_size;
		
Rectangle::Rectangle(char* img /*= ""*/, float sz /*= 1.0f*/)
	: _shader("../common/shader/Rectangle.v", "../common/shader/Rectangle.f")
{
	g_size = sz;

	Init();

	if (img != "")
	{
		GLuint tex = tools::CreateTexture(img);
		_shader.setUniformTexture2D("sampler", tex, 0);
	}
}

Rectangle::~Rectangle()
{
}

void Rectangle::Draw()
{
	_shader.Use();

	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Rectangle::SetTexture(GLuint tex)
{
	_shader.setUniformTexture2D("sampler", tex, 0);
}

void Rectangle::Init()
{
	GLuint VBO, EBO;

	static GLfloat pts[] =
	{
		g_size, g_size, 0.0f, 1, 0, 0, 1.0f, 1.0f,  // 右上角
		g_size, -g_size, 0.0f, 0, 1, 0, 1.0f, 0.0f,  // 右下角
		-g_size, -g_size, 0.0f, 0, 0, 1, 0.0f, 0.0f,  // 左下角
		-g_size, g_size, 0.0f, 1, 1, 0, 0.0f, 1.0f  // 左上角
	};

	static GLuint indices[] =
	{ // 注意索引从0开始!
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(_VAO);
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
