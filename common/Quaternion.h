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

#ifndef GLUS_QUATERNION_H_
#define GLUS_QUATERNION_H_
#include "common.inner.h"
/**
 * Creates the identity Quaternion.
 *
 * @param quaternion The resulting identity Quaternion.
 */
COMMON_API GLvoid  QuaternionIdentityf(GLfloat quaternion[4]);

/**
 * Copies a Quaternion.
 *
 * @param result The destination Quaternion.
 * @param quaternion The source Quaternion.
 */
COMMON_API GLvoid  QuaternionCopyf(GLfloat result[4], const GLfloat quaternion[4]);

/**
 * Calculates the norm of a Quaternion.
 *
 * @param quaternion The Quaternion to calculate the norm from.
 *
 * @return The norm of the Quaternion.
 */
COMMON_API GLfloat  QuaternionNormf(const GLfloat quaternion[4]);

/**
 * Normalized a Quaternion.
 *
 * @param quaternion The Quaternion to normalize.
 *
 * @return GL_TRUE, if normalization succeeded.
 */
COMMON_API GLboolean  QuaternionNormalizef(GLfloat quaternion[4]);

/**
 * Adds two Quaternions.
 *
 * @param result The sum of both Quaternions.
 * @param quaternion0 The first Quaternion.
 * @param quaternion1 The second Quaternion.
 */
COMMON_API GLvoid  QuaternionAddQuaternionf(GLfloat result[4], const GLfloat quaternion0[4], const GLfloat quaternion1[4]);

/**
 * Subtracts two Quaternions: quaternion0 - quaternion1
 *
 * @param result The difference of both Quaternions.
 * @param quaternion0 The first Quaternion.
 * @param quaternion1 The second Quaternion.
 */
COMMON_API GLvoid  QuaternionSubQuaternionf(GLfloat result[4], const GLfloat quaternion0[4], const GLfloat quaternion1[4]);

/**
 * Multiplies two Quaternions: quaternion0 * quaternion1
 *
 * @param result The multiplied Quaternion.
 * @param quaternion0 The first Quaternion.
 * @param quaternion1 The second Quaternion.
 */
COMMON_API GLvoid  QuaternionMultiplyQuaternionf(GLfloat result[4], const GLfloat quaternion0[4], const GLfloat quaternion1[4]);

/**
 * Calculates the conjugate of a Quaternion.
 *
 * @param quaternion The Quaternion to conjugate.
 */
COMMON_API GLvoid  QuaternionConjugatef(GLfloat quaternion[4]);

/**
 * Calculates the inverse of a Quaternion.
 *
 * @param quaternion The Quaternion to invert.
 *
 * @return GL_TRUE, if the inverse could be calculated.
 */
COMMON_API GLboolean  QuaternionInversef(GLfloat quaternion[4]);

/**
 * Calculates the inverse of a unit Quaternion.
 *
 * @param quaternion The Quaternion to invert.
 */
COMMON_API GLvoid  QuaternionInverseUnitf(GLfloat quaternion[4]);

/**
 * Creates a rotation Quaternion around a given axis.
 *
 * @param quaternion The final quaternion.
 * @param angle The rotation angle in degree.
 * @param x The x coordinate of the axis.
 * @param y The y coordinate of the axis.
 * @param z The z coordinate of the axis.
 */
COMMON_API GLvoid  QuaternionRotatef(GLfloat quaternion[4], const GLfloat angle, const GLfloat x, const GLfloat y, const GLfloat z);

/**
 * Creates a rotation Quaternion around a the x axis.
 *
 * @param quaternion The final quaternion.
 * @param angle The rotation angle in degree.
 */
COMMON_API GLvoid  QuaternionRotateRxf(GLfloat quaternion[4], const GLfloat angle);

/**
 * Creates a rotation Quaternion around a the y axis.
 *
 * @param quaternion The final quaternion.
 * @param angle The rotation angle in degree.
 */
COMMON_API GLvoid  QuaternionRotateRyf(GLfloat quaternion[4], const GLfloat angle);

/**
 * Creates a rotation Quaternion around a the z axis.
 *
 * @param quaternion The final quaternion.
 * @param angle The rotation angle in degree.
 */
COMMON_API GLvoid  QuaternionRotateRzf(GLfloat quaternion[4], const GLfloat angle);

/**
 * Creates a rotation Quaternion out of Euler angels: Rz * Rx * Ry
 *
 * @param quaternion The final quaternion.
 * @param anglez The rotation z angle in degree.
 * @param anglex The rotation x angle in degree.
 * @param angley The rotation y angle in degree.
 */
COMMON_API GLvoid  QuaternionRotateRzRxRyf(GLfloat quaternion[4], const GLfloat anglez, const GLfloat anglex, const GLfloat angley);

/**
 * Creates a rotation Quaternion out of Euler angels: Rz * Ry * Rx
 *
 * @param quaternion The final quaternion.
 * @param anglez The rotation z angle in degree.
 * @param angley The rotation y angle in degree.
 * @param anglex The rotation x angle in degree.
 */
COMMON_API GLvoid  QuaternionRotateRzRyRxf(GLfloat quaternion[4], const GLfloat anglez, const GLfloat angley, const GLfloat anglex);

/**
 * Creates a 4x4 matrix out of a Quaternion.
 *
 * @param matrix The resulting matrix.
 * @param quaternion The final quaternion.
 */
COMMON_API GLvoid  QuaternionGetMatrix4x4f(GLfloat matrix[16], const GLfloat quaternion[4]);

/**
 * Creates a 3x3 matrix out of a Quaternion.
 *
 * @param matrix The resulting matrix.
 * @param quaternion The final Quaternion.
 */
COMMON_API GLvoid  QuaternionGetMatrix3x3f(GLfloat matrix[9], const GLfloat quaternion[4]);

/**
 * Creates a 3D Point, given as homogeneous coordinates, out of a Quaternion.
 *
 * @param point The resulting point.
 * @param quaternion The used Quaternion.
 *
 * @return GL_TRUE, if a point could be created.
 */
COMMON_API GLboolean  QuaternionGetPoint4f(GLfloat point[4], const GLfloat quaternion[4]);

/**
 * Creates a 3D Vector, out of a Quaternion.
 *
 * @param vector The resulting vecotor.
 * @param quaternion The used Quaternion.
 *
 * @return GL_TRUE, if a vector could be created.
 */
COMMON_API GLboolean  QuaternionGetVector3f(GLfloat vector[3], const GLfloat quaternion[4]);

/**
 * Extracts the Euler angles from a Quaternion, created by Rz * Rx * Ry.
 *
 * @param angles Resulting anglex (Pitch), angley (Yaw) and anglez (Roll) in degrees.
 * @param quaternion The used Quaternion.
 *
 * @return GL_TRUE, if a extraction could be done.
 */
COMMON_API GLboolean  QuaternionGetEulerRzRxRyf(GLfloat angles[3], const GLfloat quaternion[4]);

/**
 * Extracts the Euler angles from a Quaternion, created by Rz * Ry * Rx.
 *
 * @param angles Resulting anglex (Pitch), angley (Yaw) and anglez (Roll) in degrees.
 * @param quaternion The used Quaternion.
 *
 * @return GL_TRUE, if a extraction could be done.
 */
COMMON_API GLboolean  QuaternionGetEulerRzRyRxf(GLfloat angles[3], const GLfloat quaternion[4]);

/**
 * Spherical interpolation of two Quaternions.
 *
 * @param result The interpolated Quaternion.
 * @param quaternion0 The first Quaternion.
 * @param quaternion1 The second Quaternion.
 * @param t The fraction of both Quaternions.
 *
 * @return GL_TRUE, if a slerp could be done.
 */
COMMON_API GLboolean  QuaternionSlerpf(GLfloat result[4], const GLfloat quaternion0[4], const GLfloat quaternion1[4], const GLfloat t);

#endif /* GLUS_QUATERNION_H_ */
