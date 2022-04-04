// common.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <stdlib.h>  
#include<stdio.h>  
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <list>

using std::vector;
using std::map;
using std::list;
using std::cout;
using std::cin;
using std::endl;

#include "../common/Shader.h"
#include "../common/include/FreeImage/FreeImage.h"

#include "../common/include/gl/glew.h"
#include "../common/include/glfw/glfw3.h"


#include "../common/include/glm/glm.hpp"
#include "../common/include/glm/gtc/matrix_transform.hpp"
#include "../common/include/glm/gtc/type_ptr.hpp"
#include "../common/Utility.h"
#include "../common/Camera.h"
#include "../common/Rectangle2D.h"
#include "../common/Shape.h"
#include "../common/Vector.h"
#include "../common/Point.h"

#include <iomanip>

#ifdef _DEBUG
#pragma comment(lib, "common.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "FreeImaged.lib")
#else
#pragma comment(lib, "common.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "FreeImage.lib")
#endif
