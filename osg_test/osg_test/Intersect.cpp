#include "Intersect.h"

begin_name_scpae(intersect)

Result sphere(const Ray& ray, osg::Sphere* s)
{
	Result result;

	osg::Vec3 v = ray.start - s->getCenter();
	float a0 = v.length2() - s->getRadius() * s->getRadius();
	float DdotV = ray.dir * v;

	if (DdotV <= 0)
	{
		float discr = DdotV * DdotV - a0;

		if (discr >= 0)
		{
			result.shape = s;
			result.distance = -DdotV - sqrt(discr);
			result.position = ray.getPoint(result.distance);
			result.normal = (result.position - s->getCenter());
			result.normal.normalize();
			return result;
		}
	}
	return result;
}

Result plane(const Ray& ray, osg::InfinitePlane* p)
{
	Result ret;
	
	float a = ray.dir * p->getNormal();
	if (a >= 0) return ret;

	osg::Vec3 pos = p->getNormal() * p->asVec4()[3];

	float b = p->getNormal() * (ray.start - pos);

	ret.shape = p;
	ret.distance = -b / a;
	ret.normal = p->getNormal();
	ret.position = ray.getPoint(ret.distance);

	return ret;
}

end_name_space

