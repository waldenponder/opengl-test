#pragma once
#include "common.h"

class Ray
{
public:
	Ray();
	Ray(const osg::Vec3& s, const osg::Vec3& d);
	~Ray();

	osg::Vec3 getPoint(float dis) const;

	osg::Vec3 start;
	osg::Vec3 dir;
};

extern osg::Vec4 g_initColor;