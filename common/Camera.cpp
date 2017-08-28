#include "stdafx.h"
#include "Camera.h"
#include <math.h>

static Camera* g_sCamera = nullptr;

static TVec3 g_defaultPos = TVec3(40, 50, 50);

Camera* Camera::Instance()
{
	if (g_sCamera == nullptr)
	{
		g_sCamera = new Camera();
	}

	return g_sCamera;
}

Camera::Camera()
{
	_fovy = 45;
	_aspect = float(WINDOW_WIDTH) / float(WINDOW_HEIGHT);
	_nearClip = 0.1;
	_farClip = 100000;
	_up = Y_AXIS;
	_center = TVec3();
	_rotation = TQuat(0, 0, 0, 1);
	_dirtyRotation = true;
	_moveFactor = 1;

	_eye = g_defaultPos;
	_pMoveVale = &_eye;
	_bNeedRotation = true;
}


Camera::~Camera()
{
}

TMat4 Camera::GetViewMatrix()
{
	_dirtyRotation = false;
	TVec3 v_ = RotationFrom(Z_AXIS);
	return glm::lookAt(_eye, v_ + _eye, _up);
}

TMat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(_fovy, _aspect, _nearClip, _farClip);
}

void Camera::ConfigViewMatrix(TVec3 pos, TQuat rotation, TVec3 up)
{
	g_defaultPos = _eye = pos;
	_rotation = rotation;
	_up = up;
}

void  Camera::ConfigProjectionMatrix(float fovy, float aspect, float near, float far)
{
	_fovy = fovy; _aspect = aspect; 
	_nearClip = near; _farClip = far;
}

#if 0
//世界空间到相机空间
TMat4 Camera::GetCameraSpaceMatrix()
{
	TMat4 rot(1);
	rot = glm::rotate(rot, _rotation[0], X_AXIS);
	rot = glm::rotate(rot, _rotation[1], Y_AXIS);
	rot = glm::rotate(rot, _rotation[2], Z_AXIS);
			
#if 1
	auto x = ToVec3(rot  * ToVec4(X_AXIS));
	auto y = ToVec3(rot  * ToVec4(Y_AXIS));
	auto z = ToVec3(rot  * ToVec4(Z_AXIS));
#else
	//auto x = ToVec3(rot  * ToVec4(X_AXIS));
	auto y = ToVec3(rot  * ToVec4(Y_AXIS));
	auto z = ToVec3(rot  * glm::normalize(TVec4(0, 10, 50, 0)));
	auto x = glm::cross(y, z);	  
	y = glm::cross(z, x);
#endif

	TMat4 mat(ToVec4(x), ToVec4(y), ToVec4(z), TVec4(_eye.x, _eye.y, _eye.z, 1));

	return mat;
}

//相机空间到世界空间
TMat4 Camera::GetWorldSpaceMatrix()
{
	return glm::inverse(GetCameraSpaceMatrix());
}
#endif

void Camera::MakeRotation(TVec3 axis, float angle)
{
	float s = sin(angle / 360.f * PI);
	float c = cos(angle / 360.f * PI);
	TQuat deltaQuat(axis[0] * s, axis[1] * s, axis[2] * s, c);

	TQuat quat = _rotation;

	//std::swap(quat, deltaQuat);

	TVec3 tempVec3 = c * ToVec3(quat) + quat[3] * ToVec3(deltaQuat)
		+ glm::cross(ToVec3(quat), ToVec3(deltaQuat));

	float tempFloat = c * quat[3] - glm::dot(ToVec3(quat), ToVec3(deltaQuat));

	_rotation = TQuat(tempVec3[0], tempVec3[1], tempVec3[2], tempFloat);
}

TVec3 Camera::RotationFrom(const TVec3& v)
{
	TVec3 q = ToVec3(_rotation);
	TVec3 temp = (glm::cross(q, v) + _rotation[3] * v);
	TVec3 v_ = v + 2.f * glm::cross(q, temp);

	return v_;
}
			  
/*
按键回调函数接受一个GLFWwindow指针作为它的第一个参数；
第二个整形参数用来表示按下的按键；
action参数表示这个按键是被按下还是释放；	  1	为按下, 0为释放
最后一个整形参数表示是否有Ctrl、Shift、Alt、Super等按钮的操作
*/

void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Camera* camera = g_sCamera;

	float delta = (mode == GLFW_MOD_SHIFT) ? -camera->_moveFactor : camera->_moveFactor;

	if (action == 0) return;

#pragma region move
	if (key == GLFW_KEY_UP || key == GLFW_KEY_W)
	{
		glm::vec3 v(0, 0, delta);
		v = camera->RotationFrom(v);
		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S)
	{
		glm::vec3 v(0, 0, -delta);
		v = camera->RotationFrom(v);
		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A)
	{
		glm::vec3 v(-delta, 0, 0);
		v = camera->RotationFrom(v);
		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D)
	{
		glm::vec3 v(delta, 0, 0);
		v = camera->RotationFrom(v);
		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_U)
	{
		glm::vec3 v(0, -delta, 0);
		v = camera->RotationFrom(v);
		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_D)
	{
		glm::vec3 v(0, delta, 0);
		v = camera->RotationFrom(v);
		*camera->_pMoveVale += v;
	}
#pragma endregion

	else if (key == GLFW_KEY_X)
	{
		camera->MakeRotation(X_AXIS, 5);
	}

	else if (key == GLFW_KEY_Y)
	{
		camera->MakeRotation(Y_AXIS, 5);
	}

	else if (key == GLFW_KEY_Z)
	{
		camera->MakeRotation(Z_AXIS, 5);
	}

	else if (key == GLFW_KEY_R)
	{
		camera->_bNeedRotation = !camera->_bNeedRotation;
	}

	else if (key == GLFW_KEY_SPACE)
	{
		camera->_eye = g_defaultPos;
		camera->_rotation = TQuat(0, 0, 0, 1);
	}
}
