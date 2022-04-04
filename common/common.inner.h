// common.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <stdlib.h>  
#include<stdio.h>  
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "macro.h"
	
#include <vector>
#include <map>
#include <list>

#include "include/GL/glew.h"
#include "include/glut/glut.h"
#include "include/glfw/glfw3.h"

#ifdef _DEBUG
#pragma comment(lib, "glew32d.lib")
#pragma comment(lib, "FreeImaged.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "freeglutd.lib")
#else
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "FreeImage.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "freeglut.lib")
#endif

#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

#include "Matrix.h"
#include "Utility.h"

using std::vector;
using std::map;
using std::list;
using std::cout;
using std::cin;
using std::endl;
using std::string;