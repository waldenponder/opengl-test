#pragma once
#include "osg/Vec3"
#include "osg/Shape"
#include "Ray.h"

begin_name_scpae(intersect)

struct Result
{
	float distance = 0;
	osg::Shape* shape = nullptr;

	osg::Vec3 normal;
	osg::Vec3 position;
};


Result sphere(const Ray& ray, osg::Sphere* s);

Result plane(const Ray& ray, osg::InfinitePlane* p);

end_name_space