#include "stdafx.h"
#include <fstream>
#include <osg/NodeVisitor>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include "Image.h"
#include "Camera.h"
#include "ChangeWindowSize.h"
#include "Material.h"

void init()
{
	g_camera = new Camera(osg::Vec3(0, 10, 10), osg::Vec3(0, 0, -1), osg::Vec3(0, 1, 0), 90.f);
	g_camera->render();
}

int _tmain(int argc, _TCHAR* argv[])
{
	initLight();

	srand((int)time(0));

	osgViewer::Viewer viewer;

	osg::Group* root = new osg::Group;
	//root->addChild(osgDB::readNodeFile("cow.osg"));
	root->addChild(createHUDBg(g_initColor));
	viewer.setSceneData(root);

	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	viewer.addEventHandler(new osgViewer::StatsHandler());
	viewer.addEventHandler(new ChangeWindow);

	init();

	viewer.run();

	return 0;
}