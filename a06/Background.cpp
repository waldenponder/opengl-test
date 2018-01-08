#include "stdafx.h"
#include "Background.h"


Background::Background()
{
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

}

void Background::render()
{
	glBindVertexArray(_vao);
	_shader.Use();
	_shader.setUniformMat4f("u_projectionMatrix", projectMat());
	_shader.setUniformMat4f("u_modelViewMatrix", viewMat());
	_shader.setUniformMat4f("u_modelViewMatrix", _modelMat);


}
