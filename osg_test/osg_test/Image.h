#pragma once
#include "osg/Node"
#include "osg/Image"

extern unsigned char *g_data;
extern osg::Image* g_osg_image;

extern int g_width;
extern int g_height;

osg::Node* createHUDBg(osg::Vec4 color);
