#pragma once
#include "osg/Vec3"
#include "Ray.h"
#include "Image.h"
#include "Intersect.h"

#define REFLECTION "REFLECTION"

class Camera
{
public:
	Camera(const osg::Vec3& eye, const osg::Vec3& _front, const osg::Vec3& _up, float fovy);
	~Camera();
	
	Ray generateRay(float x, float y);
	
	void render();
	void initShape();

	bool getColor(osg::Vec4& color, const Ray& ray, int maxReflect);

	intersect::Result intersetion(const Ray& ray);

public:
	osg::Vec3 _eye;
	osg::Vec3 _front;
	osg::Vec3 _up;
	float _fov;

	float _fovScale;
	osg::Vec3 _right;

	std::vector<osg::Shape*> _shapes;
};

extern Camera* g_camera;
