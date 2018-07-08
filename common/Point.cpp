/*
 * GLUS - Modern OpenGL, OpenGL ES and OpenVG Utilities. Copyright (C) since 2010 Norbert Nopper
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"
#include "Point.h"
#include "Vector.h"

GLvoid  Point4Copyf(GLfloat result[4], const GLfloat point[4])
{
    result[0] = point[0];
    result[1] = point[1];
    result[2] = point[2];
    result[3] = point[3];
}

GLvoid  Point3Copyf(GLfloat result[3], const GLfloat point[3])
{
    result[0] = point[0];
    result[1] = point[1];
    result[2] = point[2];
}

GLvoid  Point4SubtractPoint4f(GLfloat result[3], const GLfloat point0[4], const GLfloat point1[4])
{
    result[0] = point0[0] - point1[0];
    result[1] = point0[1] - point1[1];
    result[2] = point0[2] - point1[2];
}

GLvoid  Point3SubtractPoint3f(GLfloat result[2], const GLfloat point0[3], const GLfloat point1[3])
{
    result[0] = point0[0] - point1[0];
    result[1] = point0[1] - point1[1];
}

GLvoid  Point4AddVector3f(GLfloat result[4], const GLfloat point[4], const GLfloat vector[3])
{
    result[0] = point[0] + vector[0];
    result[1] = point[1] + vector[1];
    result[2] = point[2] + vector[2];
    result[3] = point[3];
}

GLvoid  Point3AddVector2f(GLfloat result[3], const GLfloat point[3], const GLfloat vector[2])
{
    result[0] = point[0] + vector[0];
    result[1] = point[1] + vector[1];
    result[2] = point[2];
}

GLvoid  Point4SubtractVector3f(GLfloat result[4], const GLfloat point[4], const GLfloat vector[3])
{
    result[0] = point[0] - vector[0];
    result[1] = point[1] - vector[1];
    result[2] = point[2] - vector[2];
    result[3] = point[3];
}

GLvoid  Point3SubtractVector2f(GLfloat result[3], const GLfloat point[3], const GLfloat vector[2])
{
    result[0] = point[0] - vector[0];
    result[1] = point[1] - vector[1];
    result[2] = point[2];
}

GLvoid  Point4GetQuaternionf(GLfloat result[4], const GLfloat point[4])
{
    result[0] = point[0];
    result[1] = point[1];
    result[2] = point[2];
    result[3] = 0.0f;
}

GLvoid  Point4GetVector3f(GLfloat result[3], const GLfloat point[4])
{
    result[0] = point[0];
    result[1] = point[1];
    result[2] = point[2];
}

GLvoid  Point3GetVector2f(GLfloat result[2], const GLfloat point[3])
{
    result[0] = point[0];
    result[1] = point[1];
}

GLfloat  Point4Distancef(const GLfloat point0[4], const GLfloat point1[4])
{
	GLfloat vector[3];

	Point4SubtractPoint4f(vector, point0, point1);

	return Vector3Lengthf(vector);
}

GLfloat  Point3Distancef(const GLfloat point0[3], const GLfloat point1[3])
{
	GLfloat vector[2];

	Point3SubtractPoint3f(vector, point0, point1);

	return Vector2Lengthf(vector);
}
