#include "Material.h"

begin_name_scpae(material)

float g_scale = .1f;

osg::Vec4 Checker(const Ray& ray, const osg::Vec3& pos, const osg::Vec3& norm)
{
	return abs((int)(floor(pos.x() * .1) + floor(pos.z() * g_scale)) % 2) < 1 ? Color::Black : Color::White;
}

osg::Vec4 Phong(const Ray& ray, const osg::Vec3& pos, const osg::Vec3& norm, const osg::Material* mat)
{
	osg::Vec4 diffuse = mat->getDiffuse(F_B) / 255.f;
	osg::Vec4 specular = mat->getSpecular(F_B) / 255.f;
	float shiness = mat->getShininess(F_B);

	//osg::Vec4 ambient(3, 3, 3, 255);
	osg::Vec4 lightColor = g_lights[0]->getDiffuse();
	osg::Vec3 lightDir = g_lights[0]->getDirection();
	float NdotL = norm * lightDir;
	osg::Vec3 H = lightDir - ray.dir;
	H.normalize();

	float NdotH = norm * H;

	osg::Vec4 diffuseItem = diffuse * std::max(NdotL, 0.f);
	osg::Vec4 specularItem = specular * std::pow(std::max(NdotH, 0.f), shiness) * .6;

	osg::Vec4 ret = osg::componentMultiply(lightColor / 255.f, (diffuseItem + specularItem)) * 255.f;
	
	return ret;
}

end_name_space