
/*
选中效果
*/

#include "stdafx.h"
#include "../common/com_include.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GLfloat cubePts[180];
	tools::GetCubePts(cubePts);

	tools::PrepareGlfw();


	return 0;
}