#include "stdafx.h"
#include "Camera.h"


static Camera* g_sCamera = nullptr;

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
	_farClip = 10000;
	_up = Y_AXIS;
	_lookAt = Z_AXIS;
	_rotation = TVec3();
	_dirtyRotation = true;
	_moveFactor = 0.1;

	_pos = TVec3(0, 0, 10);
	_pMoveVale = &_pos;
}


Camera::~Camera()
{
}

TMat4 Camera::GetViewMatrix()
{
	//if (_dirtyRotation && 0)
	{
		_dirtyRotation = false;
		
		TMat4 rot(1);
		rot = glm::rotate(rot, _rotation[0], X_AXIS);
		rot = glm::rotate(rot, _rotation[1], Y_AXIS);
		rot = glm::rotate(rot, _rotation[2], Z_AXIS);
		
		//TVec3 aim = ToVec3(rot * ToVec4(_lookAt));
		//TVec3 up = ToVec3(rot * ToVec4(Y_AXIS));
		//TVec3 x = glm::cross(aim, up);
		
		TMat4 tran(1);
		tran = glm::translate(tran, _pos);
		_up = ToVec3(rot * ToVec4(Y_AXIS));
		_lookAt = ToVec3(tran * rot * ToVec4(-Z_AXIS));
		
	//	_up = ToVec3(rot * ToVec4(Y_AXIS));
	//	_lookAt = ToVec3(-tran * rot  * ToVec4(Z_AXIS));

	}

	return glm::lookAt(_pos, _lookAt, _up);
}

TMat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(_fovy, _aspect, _nearClip, _farClip);
}

void Camera::ConfigViewMatrix(TVec3 pos, TVec3 rotation, TVec3 up)
{
	_pos = pos;
	_rotation = rotation;
	_up = up;
}

void  Camera::ConfigProjectionMatrix(float fovy, float aspect, float near, float far)
{
	_fovy = fovy; _aspect = aspect; 
	_nearClip = near; _farClip = far;
}

void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Camera* camera = g_sCamera;

	float delta = (mode == GLFW_MOD_SHIFT) ? -camera->_moveFactor : camera->_moveFactor;

	if (key == GLFW_KEY_UP)
	{
		glm::vec3 v(0, -delta, 0);
		*camera->_pMoveVale += v;
	}
	else if (key == GLFW_KEY_DOWN)
	{
		glm::vec3 v(0, delta, 0);
		*camera->_pMoveVale += v;
	}
	else if (key == GLFW_KEY_LEFT)
	{
		glm::vec3 v(delta, 0, 0);
		*camera->_pMoveVale += v;
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		glm::vec3 v(-delta, 0, 0);
		*camera->_pMoveVale += v;
	}
	else if (key == GLFW_KEY_N)
	{
		glm::vec3 v(0, 0, -delta);
		*camera->_pMoveVale += v;
	}
	else if (key == GLFW_KEY_F)
	{
		glm::vec3 v(0, 0, delta);
		*camera->_pMoveVale += v;
	}
	else if (key == GLFW_KEY_SPACE)
	{
		camera->_pos = TVec3(0, 0, 10);
		camera->_rotation = TVec3();
	}
	else if (key == GLFW_KEY_X)
	{
		camera->_rotation += 30 * delta * X_AXIS;
	}
	else if (key == GLFW_KEY_Y)
	{
		camera->_rotation += 30 * delta * Y_AXIS;
	}
	else if (key == GLFW_KEY_Z)
	{
		camera->_rotation += 30 * delta * Z_AXIS;
	}
}
