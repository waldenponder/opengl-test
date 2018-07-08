#include "Light.h"
#include "common.h"


std::vector<osg::Light*> g_lights;

void initLight()
{
	osg::Light* lt = new osg::Light;
	osg::Vec3 dir = osg::Vec3(1, 1, 1);
	dir.normalize();
	lt->setDirection(dir);
	lt->setDiffuse(Color::White);
	g_lights.push_back(lt);
}
