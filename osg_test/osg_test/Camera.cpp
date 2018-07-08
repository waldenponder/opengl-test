#include "Camera.h"
#include "osg/Shape"
#include "Intersect.h"
#include <algorithm>
#include "osgDB/WriteFile"
#include "osg/Material"
#include "Material.h"

Camera* g_camera;

Camera::Camera(const osg::Vec3& eye, const osg::Vec3& front, const osg::Vec3& up, float fovy)
	:_eye(eye), _front(front), _up(up), _fov(fovy)
{
	_right = front^up;
	_up = _right ^ _front;
	_fovScale = tan(_fov * .5f * osg::PI / 180.0f) * 2;

	initShape();
}

Camera::~Camera()
{
}

Ray Camera::generateRay(float x, float y)
{
	osg::Vec3 r = _right * (x - .5f) * _fovScale;
	osg::Vec3 u = _up * (y - .5f) * _fovScale;

	Ray ray;
	ray.start = _eye;
	ray.dir = _front + r + u;
	ray.dir.normalize();

	return ray;
}

void Camera::render()
{
	long t1 = clock();

	float maxDepth = 1000.f;

	int i = 0;
	for (float y = 0; y < g_height; y++ )
	{
		float sy = 1 - y / g_height;
		for (float x = 0; x < g_width; x++)
		{
			float sx = x / g_width;
			Ray ray = generateRay(sx, sy);

			osg::Vec4 color;
			if (getColor(color, ray, 5))
			{
				for (size_t v = 0; v < 4; v++)
				{
					if (color[v] > 255) color[v] = 255;
				}

				g_data[i] = color[0];
				g_data[i + 1] = color[1];
				g_data[i + 2] = color[2];
				g_data[i + 3] = color[3];
			}
			
			i += 4;
		}
	}

	cout << "time use " << (clock() - t1) << endl;

	//osgDB::writeImageFile(*g_osg_image, "abc.bmp");
}

void Camera::initShape()
{
	vector<osg::Vec3> posVec{ osg::Vec3(-22, 14, -15), osg::Vec3(3, 3, -10), osg::Vec3(2, 20, -5)};
	vector<osg::Vec4> colorVec{Color::Blue, Color::Red, Color::Green};

	for (size_t i = 0; i< 10; i++)
	{
		float x = rand() % 13;
		float y = rand() % 5; 
		float z = rand() % 15 - 5;

		auto v = posVec[i % 3] + osg::Vec3(x, y, z);
		posVec.push_back(v);
	}

	for (size_t i = 0; i < posVec.size(); i++)
	{
		auto var = posVec[i];
		auto color = colorVec[i % colorVec.size()];
		osg::Sphere* sphere = new osg::Sphere(var, 2);
		osg::Material* ma = new osg::Material;
		ma->setDiffuse(F_B, color);
		ma->setSpecular(F_B, Color::White);
		ma->setShininess(F_B, 128);
		sphere->setUserValue(REFLECTION, .1f);
		sphere->setUserData(ma);
		_shapes.push_back(sphere);
	}
	
	osg::InfinitePlane* plane = new osg::InfinitePlane;
	plane->setUserValue(REFLECTION, .3f);
	plane->set(osg::Vec4(0,1,0,0));
	_shapes.push_back(plane);
}

bool Camera::getColor(osg::Vec4& color, const Ray& ray, int maxReflect)
{
	//光线的方向和阴影颜色
	osg::Vec3 lightDir = g_lights[0]->getDirection();
	osg::Vec4 shadowColor(10.f, 10.f, 10.f, 255.f);

	for (osg::Shape* shape : _shapes)
	{
		intersect::Result result;

		if (osg::Sphere* var1 = dynamic_cast<osg::Sphere*>(shape))
		{
			result = intersect::sphere(ray, var1);

			if (result.shape)
			{
				Ray shadowRay(result.position, lightDir);
				intersect::Result resultS = intersetion(shadowRay);
				if (resultS.shape)
				{
					color = shadowColor; return true;
				}
					
				osg::Material* ma = dynamic_cast<osg::Material*>(result.shape->getUserData());
				color = material::Phong(ray, result.position, result.normal, ma);
			}
		}
		else if (osg::InfinitePlane* var2 = dynamic_cast<osg::InfinitePlane*>(shape))
		{
			result = intersect::plane(ray, var2);

			if (result.shape)
			{
				Ray shadowRay(result.position, lightDir);
				intersect::Result resultS = intersetion(shadowRay);
				if (resultS.shape)
				{
					color = shadowColor; return true;
				}

				color = material::Checker(ray, result.position, result.normal);
			}
		}

		if (result.shape)
		{
			float reflect;
			result.shape->getUserValue<float>(REFLECTION, reflect);
			color *= (1 - reflect);

			if (reflect > 0 && maxReflect > 0)
			{
				osg::Vec3 r = result.normal * (result.normal * ray.dir* -2.f) + ray.dir;

				Ray rayNew(result.position, r);
				osg::Vec4 reflectedColor;
				bool falg = getColor(reflectedColor, rayNew, maxReflect - 1);
				if (falg) color += reflectedColor * reflect;
			}
			return true;
		}
		else
		{
			color = Color::White;
		}
	}
	
	return false;
}

intersect::Result Camera::intersetion(const Ray& ray)
{
	for (osg::Shape* shape : _shapes)
	{
		intersect::Result result;

		if (osg::Sphere* var1 = dynamic_cast<osg::Sphere*>(shape))
		{
			result = intersect::sphere(ray, var1);

			if (result.shape)
			{
				return result;
			}
		}
		else if (osg::InfinitePlane* var2 = dynamic_cast<osg::InfinitePlane*>(shape))
		{
			result = intersect::plane(ray, var2);

			if (result.shape)
			{
				return result;
			}
		}
	}

	return intersect::Result();
}
