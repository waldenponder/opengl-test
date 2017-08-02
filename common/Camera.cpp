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

	auto mat = GetWorldSpaceMatrix();
	_up = ToVec3(mat * ToVec4(Y_AXIS));
	_lookAt = ToVec3(mat * TVec4(0, 0, 0, 0));

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

TMat4 Camera::GetCameraSpaceMatrix()
{
	TMat4 rot(1);
	rot = glm::rotate(rot, _rotation[0], X_AXIS);
	rot = glm::rotate(rot, _rotation[1], Y_AXIS);
	rot = glm::rotate(rot, _rotation[2], Z_AXIS);
			
	auto x = ToVec3(rot  * ToVec4(X_AXIS));
	auto y = ToVec3(rot  * ToVec4(Y_AXIS));
	auto z = ToVec3(rot  * ToVec4(Z_AXIS));

	TMat4 mat(ToVec4(x), ToVec4(y), ToVec4(z), TVec4(_pos.x, _pos.y, _pos.z, 1));

	return mat;
}

TMat4 Camera::GetWorldSpaceMatrix()
{
	return glm::inverse(GetCameraSpaceMatrix());
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

	auto mat = camera->GetWorldSpaceMatrix();

	if (key == GLFW_KEY_UP)
	{
		glm::vec3 v(0, 0, -delta);
		v = ToVec3(mat * ToVec4(v));

		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_DOWN)
	{
		glm::vec3 v(0, 0, delta);
		v = ToVec3(mat * ToVec4(v));

		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_LEFT)
	{
		glm::vec3 v(delta, 0, 0);
		v = ToVec3(mat * ToVec4(v));

		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_RIGHT)
	{
		glm::vec3 v(-delta, 0, 0);
		v = ToVec3(mat * ToVec4(v));

		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_U)
	{
		glm::vec3 v(0, -delta, 0);
		v = ToVec3(mat * ToVec4(v));

		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_D)
	{
		glm::vec3 v(0, delta, 0);
		v = ToVec3(mat * ToVec4(v));

		*camera->_pMoveVale += v;
	}

	else if (key == GLFW_KEY_X)
	{
		camera->_rotation += ToVec3(mat * ToVec4(X_AXIS));
	}

	else if (key == GLFW_KEY_Y)
	{
		camera->_rotation += ToVec3(mat * ToVec4(Y_AXIS));
	}

	else if (key == GLFW_KEY_Z)
	{
		camera->_rotation += ToVec3(mat * ToVec4(Z_AXIS));
	}

	else if (key == GLFW_KEY_R)
	{
		camera->_bNeedRotation = !camera->_bNeedRotation;
	}

	else if (key == GLFW_KEY_SPACE)
	{
		camera->_pos = g_defaultPos;
		camera->_rotation = TVec3();
	}

	if (key == GLFW_KEY_X || key == GLFW_KEY_Y || key == GLFW_KEY_Z)
	{
		TMat4 rot(1);
		rot = glm::rotate(rot, camera->_rotation[0], X_AXIS);
		rot = glm::rotate(rot, camera->_rotation[1], Y_AXIS);
		rot = glm::rotate(rot, camera->_rotation[2], Z_AXIS);

		auto pos = rot * ToVec4(camera->_pos);
		camera->_pos = ToVec3(pos);

		auto up = rot * ToVec4(camera->_up);
		camera->_up = ToVec3(up);

		auto lookAt = rot * ToVec4(camera->_lookAt);
		camera->_lookAt = ToVec3(lookAt);
	}
}
