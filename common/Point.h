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
#include "common.inner.h"

#ifndef GLUS_POINT_H_
#define GLUS_POINT_H_

/**
 * Copies a 3D point, given as homogeneous coordinates.
 *
 * @param result The destination point.
 * @param point The source point.
 */
COMMON_API GLvoid  Point4Copyf(GLfloat result[4], const GLfloat point[4]);

/**
 * Copies a 2D point, given as homogeneous coordinates.
 *
 * @param result The destination point.
 * @param point The source point.
 */
COMMON_API GLvoid  Point3Copyf(GLfloat result[3], const GLfloat point[3]);

/**
 * Subtracts a 3D point, given as homogeneous coordinates, from another and calculates a 3D vector.
 *
 * @param result The resulting vector.
 * @param point0 The point subtracted by point1.
 * @param point1 The point subtracted from point0.
 */
COMMON_API GLvoid  Point4SubtractPoint4f(GLfloat result[3], const GLfloat point0[4], const GLfloat point1[4]);

/**
 * Subtracts a 2D point, given as homogeneous coordinates, from another and calculates a 2D vector.
 *
 * @param result The resulting vector.
 * @param point0 The point subtracted by point1.
 * @param point1 The point subtracted from point0.
 */
COMMON_API GLvoid  Point3SubtractPoint3f(GLfloat result[2], const GLfloat point0[3], const GLfloat point1[3]);

/**
 * Adds a vector to a 3D point, given as homogeneous coordinates. Result is the new point.
 *
 * @param result The resulting point.
 * @param point The point.
 * @param vector The vector, which is added to the point.
 */
COMMON_API GLvoid  Point4AddVector3f(GLfloat result[4], const GLfloat point[4], const GLfloat vector[3]);

/**
 * Adds a vector to a 2D point, given as homogeneous coordinates. Result is the new point.
 *
 * @param result The resulting point.
 * @param point The point.
 * @param vector The vector, which is added to the point.
 */
COMMON_API GLvoid  Point3AddVector2f(GLfloat result[3], const GLfloat point[3], const GLfloat vector[2]);

/**
 * Subtracts a vector from a 3D point, given as homogeneous coordinates. Result is the new point.
 *
 * @param result The resulting point.
 * @param point The point.
 * @param vector The vector, which is subtracted from the point.
 */
COMMON_API GLvoid  Point4SubtractVector3f(GLfloat result[4], const GLfloat point[4], const GLfloat vector[3]);

/**
 * Subtracts a vector from a 2D point, given as homogeneous coordinates. Result is the new point.
 *
 * @param result The resulting point.
 * @param point The point.
 * @param vector The vector, which is subtracted from the point.
 */
COMMON_API GLvoid  Point3SubtractVector2f(GLfloat result[3], const GLfloat point[3], const GLfloat vector[2]);

/**
 * Converts a 3D point, given as homogeneous coordinates, to a quaternion.
 *
 * @param result The resulting quaternion.
 * @param point The point, which is converted.
 */
COMMON_API GLvoid  Point4GetQuaternionf(GLfloat result[4], const GLfloat point[4]);

/**
 * Converts a 3D point, given as homogeneous coordinates, to a vector.
 *
 * @param result The resulting vector.
 * @param point The point, which is converted.
 */
COMMON_API GLvoid  Point4GetVector3f(GLfloat result[3], const GLfloat point[4]);

/**
 * Converts a 2D point, given as homogeneous coordinates, to a vector.
 *
 * @param result The resulting vector.
 * @param point The point, which is converted.
 */
COMMON_API GLvoid  Point3GetVector2f(GLfloat result[2], const GLfloat point[3]);

/**
 * Calculates the distance of two 3D points, given as homogeneous coordinates.
 *
 * @param point0 The first point.
 * @param point1 The second point.
 *
 * @return The distance of the two points.
 */
COMMON_API GLfloat  Point4Distancef(const GLfloat point0[4], const GLfloat point1[4]);

/**
 * Calculates the distance of two 2D points, given as homogeneous coordinates.
 *
 * @param point0 The first point.
 * @param point1 The second point.
 *
 * @return The distance of the two points.
 */
COMMON_API GLfloat  Point3Distancef(const GLfloat point0[3], const GLfloat point1[3]);

#endif /* GLUS_POINT_H_ */
