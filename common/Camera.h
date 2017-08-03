#pragma once
#include "common.inner.h"

#define CameraPos   (Camera::Instance()->_pos)

void  COMMON_API OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mode);

//TODO: 变换还是有问题
class COMMON_API Camera
{
public:
	static Camera* Instance();

private:
	Camera();
	~Camera();

public:
	TMat4  GetViewMatrix();
	TMat4  GetProjectionMatrix();

	void   ConfigViewMatrix(TVec3 pos, TVec3 rotation, TVec3 up);
	void   ConfigProjectionMatrix(float fovy, float aspect, float near, float far);

	void   DirtyRotation() { _dirtyRotation = true; }

	TMat4  GetCameraSpaceMatrix();
	TMat4  GetWorldSpaceMatrix();

public:

	TVec3* _pMoveVale;
	float  _moveFactor;

	/*
	glm::lookAt的参数
	*/
	TVec3  _pos;
	//世界坐标系
	TVec3  _rotation;
	TVec3  _up;
	TVec3  _lookAt;

	bool   _dirtyRotation;

	/*
	glm::perspective的参数
	*/
	float  _nearClip;
	float  _farClip;
	float  _fovy;
	float  _aspect;

public:
	bool _bNeedRotation;
};
