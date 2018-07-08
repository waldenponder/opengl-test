#include "stdafx.h"
#include "Background.h"
#include "../common/common.out.h"

#define WATER_PLANE_LENGTH 128

static GLuint g_vaoBackground;

static GLuint g_verticesBackgroundVBO;

static GLuint g_normalsBackgroundVBO;

static GLuint g_indicesBackgroundVBO;

static GLuint g_numberIndicesBackground;

static GLuint g_cubeMape;

Background::Background()
{
	initShader();
	initVAO();
										 
#if 0
	vector<const char*> faces;
	faces.push_back("../common/src/skybox/right.jpg");	//x+
	faces.push_back("../common/src/skybox/left.jpg");

	faces.push_back("../common/src/skybox/top.jpg");  //y+
	faces.push_back("../common/src/skybox/bottom.jpg");

	faces.push_back("../common/src/skybox/front.jpg"); //Z+
	faces.push_back("../common/src/skybox/back.jpg");

	g_cubeMape = Utility::CreateCubemap(faces);
#else
	vector<const char*> faceVec;
	faceVec.push_back("img/water_pos_x.tga"); faceVec.push_back("img/water_neg_x.tga");
	faceVec.push_back("img/water_pos_y.tga"); faceVec.push_back("img/water_neg_y.tga");
	faceVec.push_back("img/water_pos_z.tga"); faceVec.push_back("img/water_neg_z.tga");
	g_cubeMape = Utility::CreateCubemap(faceVec);
#endif

	//Utility::CreateCubeVAO(g_vaoBackground);
}


Background::~Background()
{
}

void Background::initShader()
{
	_shader.setSource("shader/Background.vert.glsl", "shader/Background.frag.glsl");
}

void Background::initVAO()
{
#if 1
	Shape background;
	ShapeCreateSpheref(&background, (GLfloat)(GLfloat)WATER_PLANE_LENGTH / 2.0f + 0.5f, 32);
	g_numberIndicesBackground = background.numberIndices;

	glGenBuffers(1, &g_verticesBackgroundVBO);
	glBindBuffer(GL_ARRAY_BUFFER, g_verticesBackgroundVBO);
	glBufferData(GL_ARRAY_BUFFER, background.numberVertices * 4 * sizeof(GLfloat), (GLfloat*)background.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &g_normalsBackgroundVBO);
	glBindBuffer(GL_ARRAY_BUFFER, g_normalsBackgroundVBO);
	glBufferData(GL_ARRAY_BUFFER, background.numberVertices * 3 * sizeof(GLfloat), (GLfloat*)background.normals, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &g_indicesBackgroundVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_indicesBackgroundVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, background.numberIndices * sizeof(GLuint), (GLuint*)background.indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	ShapeDestroyf(&background);

	///////////////////////////////////////////////////////////////

	glGenVertexArrays(1, &g_vaoBackground);
	glBindVertexArray(g_vaoBackground);

	glBindBuffer(GL_ARRAY_BUFFER, g_verticesBackgroundVBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, g_normalsBackgroundVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_indicesBackgroundVBO);
#endif
}

void Background::render()
{
	glDepthMask(GL_FALSE);

	glBindVertexArray(g_vaoBackground);
	//glFrontFace(GL_CW);
	_shader.Use();
	_shader.setUniformMat4f("u_projectionMatrix", projectMat());
	_shader.setUniformMat4f("u_modelViewMatrix", viewMat());
	//_shader.setUniformMat4f("u_modelViewMatrix", _modelMat);

	_shader.setUniformTextureCube("u_cubemap", g_cubeMape, 0);

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, g_numberIndicesBackground, GL_UNSIGNED_INT, 0);

	glDepthMask(GL_TRUE);
}
