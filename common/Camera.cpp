#include "stdafx.h"
#include "Camera.h"


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
	_farClip = 10000;
	_up = Y_AXIS;
	_lookAt = TVec3();
	_rotation = TVec3();
	_dirtyRotation = true;
	_moveFactor = 1;

	_pos = g_defaultPos;
	_pMoveVale = &_pos;
	_bNeedRotation = true;
}


Camera::~Camera()
{
}

TMat4 Camera::GetViewMatrix()
{
	_dirtyRotation = false;
		
	TMat4 rot(1);
	rot = glm::rotate(rot, _rotation[0], X_AXIS);
	rot = glm::rotate(rot, _rotation[1], Y_AXIS);
	rot = glm::rotate(rot, _rotation[2], Z_AXIS);
	
	_pos = ToVec3(rot * ToVec4(_pos));

	TMat4 tran(1);
	tran = glm::translate(tran, _pos);

	//auto x = rot * tran * ToVec4(X_AXIS);
	//auto y = rot * tran * ToVec4(Y_AXIS);
	//auto z = rot * tran * ToVec4(Z_AXIS);

	auto x = rot  * ToVec4(X_AXIS);
	auto y = rot  * ToVec4(Y_AXIS);
	auto z = rot  * ToVec4(Z_AXIS);

	_up = ToVec3(y);
									 
	TMat4 mat(x, y, z, TVec4(_pos.x, _pos.y, _pos.z, 1));
	_lookAt = ToVec3(glm::inverse(mat) *  TVec4() );

	return glm::lookAt(_pos, _lookAt, _up);
}

TMat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(_fovy, _aspect, _nearClip, _farClip);
}

void Camera::ConfigViewMatrix(TVec3 pos, TVec3 rotation, TVec3 up)
{
	g_defaultPos = _pos = pos;
	_rotation = rotation;
	_up = up;
}

void  Camera::ConfigProjectionMatrix(float fovy, float aspect, float near, float far)
{
	_fovy = fovy; _aspect = aspect; 
	_nearClip = near; _farClip = far;
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

	if (key == GLFW_KEY_UP)
	{
		glm::vec3 v(0, -delta, 0);
		*camera->_pMoveVale += v;
		camera->_lookAt += v;
	}
	else if (key == GLFW_KEY_DOWN)
	{
		glm::vec3 v(0, delta, 0);
		*camera->_pMoveVale += v;
		camera->_lookAt += v;
	}
	else if (key == GLFW_KEY_LEFT)
	{
		glm::vec3 v(delta, 0, 0);
		*camera->_pMoveVale += v;
		camera->_lookAt += v;
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		glm::vec3 v(-delta, 0, 0);
		*camera->_pMoveVale += v;
		camera->_lookAt += v;
	}
	else if (key == GLFW_KEY_N)
	{
		glm::vec3 v(0, 0, -delta);
		*camera->_pMoveVale += v;
		camera->_lookAt += v;
	}
	else if (key == GLFW_KEY_F)
	{
		glm::vec3 v(0, 0, delta);
		*camera->_pMoveVale += v;
		camera->_lookAt += v;
	}
	else if (key == GLFW_KEY_SPACE)
	{
		camera->_pos = g_defaultPos;
		camera->_rotation = TVec3();
	}
	else if (key == GLFW_KEY_X)
	{
		camera->_rotation += .3f * X_AXIS;
	}
	else if (key == GLFW_KEY_Y)
	{
		camera->_rotation += .3f  * Y_AXIS;
	}
	else if (key == GLFW_KEY_Z)
	{
		camera->_rotation += .3f  * Z_AXIS;
	}
	else if (key == GLFW_KEY_R)
	{
		camera->_bNeedRotation = !camera->_bNeedRotation;
	}
}
