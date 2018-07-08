#include "Image.h"
#include "osg/Texture2D"
#include "osg/Image"
#include "osg/Camera"
#include "osg/Geometry"
#include "osg/Geode"
#include "osg/Depth"

unsigned char *g_data;
osg::Image* g_osg_image;
int g_width = 2048, g_height = 2048;

osg::Node* createHUDBg(osg::Vec4 color)
{
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;

	osg::ref_ptr<osg::Image> image = new osg::Image;
	g_osg_image = image.get();
	g_data = new  unsigned char[g_width* g_height * 4];

	int index = 0;
	for (int i = 0; i < g_width; i++)
	{
		for (int j = 0; j < g_height; j++)
		{
			g_data[index++] = color[0];
			g_data[index++] = color[1];
			g_data[index++] = color[2];
			g_data[index++] = color[3];
		}
	}
	image->setImage(g_width, g_height, 24, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, g_data, osg::Image::USE_NEW_DELETE);
	texture->setImage(image.get());

	osg::ref_ptr<osg::Drawable> quad = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(1.0f, 0.0f, 0.0f), osg::Vec3(0.0f, 1.0f, 0.0f));
	quad->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(quad.get());

	osg::Camera* camera = new osg::Camera;
	camera->setClearMask(0);
	camera->setCullingActive(false);
	camera->setAllowEventFocus(false);
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setRenderOrder(osg::Camera::NESTED_RENDER);
	camera->setProjectionMatrix(osg::Matrix::ortho2D(0.0, 1.0, 1.0, .0));
	camera->addChild(geode.get());

	osg::StateSet* ss = camera->getOrCreateStateSet();
	ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	ss->setAttributeAndModes(new osg::Depth(osg::Depth::LEQUAL, 1.0, 1.0));

	return camera;
}