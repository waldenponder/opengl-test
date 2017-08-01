#pragma once
#include "Shader.h"

class COMMON_API Rectangle2D
{
public:
	Rectangle2D(char* img = "", float sz = 1.0f);
	~Rectangle2D();

	void Draw();
	void SetTexture(GLuint tex);

private:
	void Init();

	GLuint _textureID;
	Shader _shader;
	GLuint _VAO;
};