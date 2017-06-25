// common.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdlib.h>  
#include<stdio.h>  
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "macro.h"

#if 1
#define use_glfw3

#include "include/gl/glew.h"
#ifndef use_glfw3
#include "include/gl/glfw.h"
#else
#include "include/glfw/glfw3.h"
#endif
#include "include/glut/glut.h"
#endif

#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "FreeImaged.lib")
#ifndef use_glfw3
#pragma comment(lib, "GLFW.lib")
#else
#pragma comment(lib, "glfw3.lib")
#endif

#include "../common/include/glm/glm.hpp"
#include "../common/include/glm/gtc/matrix_transform.hpp"
#include "../common/include/glm/gtc/type_ptr.hpp"