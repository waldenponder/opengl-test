#pragma once
#include "Shader.h"

class COMMON_API Rectangle2D
{
public:
	Rectangle2D(char* img = "", GLfloat x1 = -1, GLfloat y1 = -1, GLfloat x2 = 1, GLfloat y2 = 1);
	~Rectangle2D();

	void Draw();
	void SetTexture(GLuint tex);

private:
	void Init(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

	GLuint _textureID;
	Shader _shader;
	GLuint _VAO;
};