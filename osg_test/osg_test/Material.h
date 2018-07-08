#pragma once
#include "Ray.h"


extern float g_checkerScale;

begin_name_scpae(material)

//∆Â≈Ã
osg::Vec4 Checker(const Ray& ray, const osg::Vec3& pos, const osg::Vec3& norm);

osg::Vec4 Phong(const Ray& ray, const osg::Vec3& pos, const osg::Vec3& norm, const osg::Material* mat);

end_name_space