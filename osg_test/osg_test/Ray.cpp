#include "Ray.h"

osg::Vec4 g_initColor(57, 131, 255, 255);

Ray::Ray()
{
}


Ray::Ray(const osg::Vec3& s, const osg::Vec3& d)
	:start(s), dir(d)
{

}

Ray::~Ray()
{
}

osg::Vec3 Ray::getPoint(float dis) const
{
	return start + dir * dis;
}
