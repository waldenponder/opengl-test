// common.cpp : 定义控制台应用程序的入口点。
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

#pragma comment(lib, "common.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "FreeImaged.lib")

