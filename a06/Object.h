#pragma once
#include "../common/common.out.h"

class Object
{
public:
	Object();
	~Object();

protected:
	virtual void    initShader();
	virtual void    initVAO();

	TMat4 			projectMat();
	TMat4 			viewMat();

public:
	virtual void    render();
	
protected:
	GLuint   	    _vao;
	Shader          _shader;

	TMat4           _modelMat;	
};

