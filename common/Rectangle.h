#pragma once
#include "Shader.h"

class COMMON_API Rectangle
{
public:
	Rectangle(char* img = "", float sz = 1.0f);
	~Rectangle();
	void Draw();
	void SetTexture(GLuint tex);

private:
	void Init();

	Shader _shader;
	GLuint _VAO;
};