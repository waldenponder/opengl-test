#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	Camera::Instance()->ConfigViewMatrix(TVec3(), TQuat(0, 0, 0, 1), Y_AXIS);
}


Object::~Object()
{
}

void Object::initShader()
{
	
}

void Object::initVAO()
{

}

void Object::render()
{

}

TMat4 Object::projectMat()
{
	return Camera::Instance()->GetProjectionMatrix();
}

TMat4 Object::viewMat()
{
	return Camera::Instance()->GetViewMatrix();
}
