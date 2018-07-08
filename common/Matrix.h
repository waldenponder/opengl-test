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

#ifndef GLUS_MATRIX_H_
#define GLUS_MATRIX_H_
#include "common.inner.h"
#include "Utility.h"

/**
 * Sets the given 4x4 matrix to an identity matrix.
 *
 * @param matrix The matrix, which is set to the identity matrix.
 */
COMMON_API GLvoid  Matrix4x4Identityf(GLfloat matrix[16]);

/**
 * Sets the given 3x3 matrix to an identity matrix.
 *
 * @param matrix The matrix, which is set to the identity matrix.
 */
COMMON_API GLvoid  Matrix3x3Identityf(GLfloat matrix[9]);

/**
 * Sets the given 2x2 matrix to an identity matrix.
 *
 * @param matrix The matrix, which is set to the identity matrix.
 */
COMMON_API GLvoid  Matrix2x2Identityf(GLfloat matrix[4]);

/**
 * Initializes the given 4x4 matrix with the provided column vectors.
 *
 * @param matrix The matrix, which is initalized with the given column vectors.
 * @param column0 The first column of the matrix.
 * @param column1 The second column of the matrix.
 * @param column2 The third column of the matrix.
 * @param column3 The fourth column of the matrix.
 */
COMMON_API GLvoid  Matrix4x4Initf(GLfloat matrix[16], const GLfloat column0[4], const GLfloat column1[4], const GLfloat column2[4], const GLfloat column3[4]);

/**
 * Initializes the given 3x3 matrix with the provided column vectors.
 *
 * @param matrix The matrix, which is initalized with the given column vectors.
 * @param column0 The first column of the matrix.
 * @param column1 The second column of the matrix.
 * @param column2 The third column of the matrix.
 */

COMMON_API GLvoid  Matrix3x3Initf(GLfloat matrix[9], const GLfloat column0[3], const GLfloat column1[3], const GLfloat column2[3]);

/**
 * Initializes the given 2x2 matrix with the provided column vectors.
 *
 * @param matrix The matrix, which is initalized with the given column vectors.
 * @param column0 The first column of the matrix.
 * @param column1 The second column of the matrix.
 */
COMMON_API GLvoid  Matrix2x2Initf(GLfloat matrix[4], const GLfloat column0[2], const GLfloat column1[2]);

/**
 * Copies a 4x4 matrix.
 *
 * @param matrix The destination matrix.
 * @param source The source matrix.
 * @param rotationOnly If GL_TRUE, only the 3x3 Matrix is copied into an identity 4x4 matrix.
 */
COMMON_API GLvoid  Matrix4x4Copyf(GLfloat matrix[16], const GLfloat source[16], const GLboolean rotationOnly);

/**
 * Copies a 3x3 matrix.
 *
 * @param matrix The destination matrix.
 * @param source The source matrix.
 * @param rotationOnly If GL_TRUE, only the 2x2 Matrix is copied into an identity 3x3 matrix.
 */
COMMON_API GLvoid  Matrix3x3Copyf(GLfloat matrix[9], const GLfloat source[9], const GLboolean rotationOnly);

/**
 * Copies a 3x3 matrix.
 *
 * @param matrix The destination matrix.
 * @param source The source matrix.
 */
COMMON_API GLvoid  Matrix2x2Copyf(GLfloat matrix[4], const GLfloat source[4]);

/**
 * Extracts a 3x3 matrix out of a 4x4 matrix.
 *
 * @param matrix The destination matrix.
 * @param source The source matrix.
 */
COMMON_API GLvoid  Matrix4x4ExtractMatrix3x3f(GLfloat matrix[9], const GLfloat source[16]);

/**
 * Extracts a 2x2 matrix out of a 4x4 matrix.
 *
 * @param matrix The destination matrix.
 * @param source The source matrix.
 */
COMMON_API GLvoid  Matrix4x4ExtractMatrix2x2f(GLfloat matrix[4], const GLfloat source[16]);

/**
 * Extracts a 2x2 matrix out of a 3x3 matrix.
 *
 * @param matrix The destination matrix.
 * @param source The source matrix.
 */
COMMON_API GLvoid  Matrix3x3ExtractMatrix2x2f(GLfloat matrix[4], const GLfloat source[9]);

/**
 * Creates a 4x4 matrix out of a 3x3 matrix.
 *
 * @param matrix The destination matrix.
 * @param source The source matrix.
 */
COMMON_API GLvoid  Matrix3x3CreateMatrix4x4f(GLfloat matrix[16], const GLfloat source[9]);

/**
 * Creates a 4x4 matrix out of a 2x2 matrix.
 *
 * @param matrix The destination matrix.
 * @param source The source matrix.
 */
COMMON_API GLvoid  Matrix2x2CreateMatrix4x4f(GLfloat matrix[16], const GLfloat source[4]);

/**
 * Creates a 3x3 matrix out of a 2x2 matrix.
 *
 * @param matrix The destination matrix.
 * @param source The source matrix.
 */
COMMON_API GLvoid  Matrix2x2CreateMatrix3x3f(GLfloat matrix[9], const GLfloat source[4]);

/**
 * Multiplies two 4x4 matrices: matrix0 * matrix1.
 *
 * @param matrix The resulting matrix.
 * @param matrix0 The first matrix.
 * @param matrix1 The second matrix.
 */
COMMON_API GLvoid  Matrix4x4Multiplyf(GLfloat matrix[16], const GLfloat matrix0[16], const GLfloat matrix1[16]);


/**
 * Multiplies two 3x3 matrices: matrix0 * matrix1.
 *
 * @param matrix The resulting matrix.
 * @param matrix0 The first matrix.
 * @param matrix1 The second matrix.
 */
COMMON_API GLvoid  Matrix3x3Multiplyf(GLfloat matrix[9], const GLfloat matrix0[9], const GLfloat matrix1[9]);


/**
 * Multiplies two 2x2 matrices: matrix0 * matrix1.
 *
 * @param matrix The resulting matrix.
 * @param matrix0 The first matrix.
 * @param matrix1 The second matrix.
 */
 COMMON_API GLvoid  Matrix2x2Multiplyf(GLfloat matrix[4], const GLfloat matrix0[4], const GLfloat matrix1[4]);


/**
 * Adds two 4x4 matrices: matrix0 + matrix1.
 *
 * @param matrix The resulting matrix.
 * @param matrix0 The first matrix.
 * @param matrix1 The second matrix.
 */
COMMON_API GLvoid  Matrix4x4Addf(GLfloat matrix[16], const GLfloat matrix0[16], const GLfloat matrix1[16]);

/**
 * Adds two 3x3 matrices: matrix0 + matrix1.
 *
 * @param matrix The resulting matrix.
 * @param matrix0 The first matrix.
 * @param matrix1 The second matrix.
 */
COMMON_API GLvoid  Matrix3x3Addf(GLfloat matrix[9], const GLfloat matrix0[9], const GLfloat matrix1[9]);

/**
 * Adds two 2x2 matrices: matrix0 + matrix1.
 *
 * @param matrix The resulting matrix.
 * @param matrix0 The first matrix.
 * @param matrix1 The second matrix.
 */
COMMON_API GLvoid  Matrix2x2Addf(GLfloat matrix[4], const GLfloat matrix0[4], const GLfloat matrix1[4]);

/**
 * Subtracts two 4x4 matrices: matrix0 - matrix1.
 *
 * @param matrix The resulting matrix.
 * @param matrix0 The first matrix.
 * @param matrix1 The second matrix.
 */
COMMON_API GLvoid  Matrix4x4Subtractf(GLfloat matrix[16], const GLfloat matrix0[16], const GLfloat matrix1[16]);

/**
 * Subtracts two 3x3 matrices: matrix0 - matrix1.
 *
 * @param matrix The resulting matrix.
 * @param matrix0 The first matrix.
 * @param matrix1 The second matrix.
 */
COMMON_API GLvoid  Matrix3x3Subtractf(GLfloat matrix[9], const GLfloat matrix0[9], const GLfloat matrix1[9]);

/**
 * Subtracts two 2x2 matrices: matrix0 - matrix1.
 *
 * @param matrix The resulting matrix.
 * @param matrix0 The first matrix.
 * @param matrix1 The second matrix.
 */
COMMON_API GLvoid  Matrix2x2Subtractf(GLfloat matrix[4], const GLfloat matrix0[4], const GLfloat matrix1[4]);

/**
 * Calculates the determinant of a 4x4 matrix.
 *
 * @param matrix The used matrix.
 *
 * @return The calculated determinant.
 */
COMMON_API GLfloat  Matrix4x4Determinantf(const GLfloat matrix[16]);

/**
 * Calculates the determinant of a 3x3 matrix.
 *
 * @param matrix The used matrix.
 *
 * @return The calculated determinant.
 */
COMMON_API GLfloat  Matrix3x3Determinantf(const GLfloat matrix[9]);

/**
 * Calculates the determinant of a 2x2 matrix.
 *
 * @param matrix The used matrix.
 *
 * @return The calculated determinant.
 */
COMMON_API GLfloat  Matrix2x2Determinantf(const GLfloat matrix[4]);

/**
 * Calculates the inverse of a 4x4 matrix using Gaussian Elimination.
 *
 * @param matrix The matrix to be inverted.
 *
 * @return GL_TRUE, if creation succeeded.
 */
COMMON_API GLboolean  Matrix4x4Inversef(GLfloat matrix[16]);

/**
 * Calculates the inverse of a 3x3 matrix using the determinant and adjunct of a matrix.
 *
 * @param matrix The matrix to be inverted.
 *
 * @return GL_TRUE, if creation succeeded.
 */
COMMON_API GLboolean  Matrix3x3Inversef(GLfloat matrix[9]);

/**
 * Calculates the inverse of a 2x2 matrix using the determinant and adjunct of a matrix.
 *
 * @param matrix The matrix to be inverted.
 *
 * @return GL_TRUE, if creation succeeded.
 */
COMMON_API GLboolean  Matrix2x2Inversef(GLfloat matrix[4]);

/**
 * Calculates the inverse of a 4x4 matrix by assuming it is a rigid body matrix.
 *
 * @param matrix The matrix to be inverted.
 */
COMMON_API GLvoid  Matrix4x4InverseRigidBodyf(GLfloat matrix[16]);

/**
 * Calculates the inverse of a 3x3 matrix by assuming it is a rigid body matrix.
 *
 * @param matrix The matrix to be inverted.
 * @param is2D Set to GL_TRUE, if this matrix should be treated as a 2D matrix.
 */
COMMON_API GLvoid  Matrix3x3InverseRigidBodyf(GLfloat matrix[9], const GLboolean is2D);

/**
 * Calculates the inverse of a 2x2 matrix by assuming it is a rigid body matrix.
 *
 * @param matrix The matrix to be inverted.
 */
COMMON_API GLvoid  Matrix2x2InverseRigidBodyf(GLfloat matrix[4]);

/**
 * Transposes a 4x4 matrix.
 *
 * @param matrix The matrix to be transposed.
 */
COMMON_API GLvoid  Matrix4x4Transposef(GLfloat matrix[16]);

/**
 * Transposes a 3x3 matrix.
 *
 * @param matrix The matrix to be transposed.
 */
COMMON_API GLvoid  Matrix3x3Transposef(GLfloat matrix[9]);

/**
 * Transposes a 2x2 matrix.
 *
 * @param matrix The matrix to be transposed.
 */
COMMON_API GLvoid  Matrix2x2Transposef(GLfloat matrix[4]);

/**
 * Creates a 4x4 translation matrix and multiplies it with the provided one: matrix = matrix * translateMatrix
 *
 * @param matrix The final matrix.
 * @param x Amount to translate in x direction.
 * @param y Amount to translate in y direction.
 * @param z Amount to translate in z direction.
 */
COMMON_API GLvoid  Matrix4x4Translatef(GLfloat matrix[16], const GLfloat x, const GLfloat y, const GLfloat z);

/**
 * Creates a 3x3 translation matrix and multiplies it with the provided one: matrix = matrix * translateMatrix
 *
 * @param matrix The final matrix.
 * @param x Amount to translate in x direction.
 * @param y Amount to translate in y direction.
 */
COMMON_API GLvoid  Matrix3x3Translatef(GLfloat matrix[9], const GLfloat x, const GLfloat y);

/**
 * Creates a 4x4 matrix for rotation around a given axis and multiplies it with the given one: matrix = matrix * rotateMatrix
 *
 * @param matrix The final matrix.
 * @param angle The rotation angle in degree.
 * @param x X coordinate of axis.
 * @param y Y coordinate of axis.
 * @param z Z coordinate of axis.
 */
COMMON_API GLvoid  Matrix4x4Rotatef(GLfloat matrix[16], const GLfloat angle, const GLfloat x, const GLfloat y, const GLfloat z);

/**
 * Creates a 3x3 matrix for rotation around a given axis and multiplies it with the given one: matrix = matrix * rotateMatrix
 *
 * @param matrix The final matrix.
 * @param angle The rotation angle in degree.
 * @param x X coordinate of axis.
 * @param y Y coordinate of axis.
 * @param z Z coordinate of axis.
 */
COMMON_API GLvoid  Matrix3x3Rotatef(GLfloat matrix[9], const GLfloat angle, const GLfloat x, const GLfloat y, const GLfloat z);

/**
 * Creates a 2x2 matrix for a rotation around in 2D and multiplies it with the given one: matrix = matrix * rotateMatrix
 *
 * @param matrix The final matrix.
 * @param angle The rotation angle in degree.
 */
COMMON_API GLvoid  Matrix2x2Rotatef(GLfloat matrix[4], const GLfloat angle);

/**
 * Creates a 4x4 matrix for rotation around the x axis and multiplies it with the given one: matrix = matrix * rotateMatrix
 *
 * @param matrix The final matrix.
 * @param angle The rotation angle in degree.
 */
COMMON_API GLvoid  Matrix4x4RotateRxf(GLfloat matrix[16], const GLfloat angle);

/**
 * Creates a 3x3 matrix for rotation around the x axis and multiplies it with the given one: matrix = matrix * rotateMatrix
 *
 * @param matrix The final matrix.
 * @param angle The rotation angle in degree.
 */
COMMON_API GLvoid  Matrix3x3RotateRxf(GLfloat matrix[9], const GLfloat angle);

/**
 * Creates a 4x4 matrix for rotation around the y axis and multiplies it with the given one: matrix = matrix * rotateMatrix
 *
 * @param matrix The final matrix.
 * @param angle The rotation angle in degree.
 */
COMMON_API GLvoid  Matrix4x4RotateRyf(GLfloat matrix[16], const GLfloat angle);

/**
 * Creates a 3x3 matrix for rotation around the y axis and multiplies it with the given one: matrix = matrix * rotateMatrix
 *
 * @param matrix The final matrix.
 * @param angle The rotation angle in degree.
 */
COMMON_API GLvoid  Matrix3x3RotateRyf(GLfloat matrix[9], const GLfloat angle);

/**
 * Creates a 4x4 matrix for rotation around the z axis and multiplies it with the given one: matrix = matrix * rotateMatrix
 *
 * @param matrix The final matrix.
 * @param angle The rotation angle in degree.
 */
COMMON_API GLvoid  Matrix4x4RotateRzf(GLfloat matrix[16], const GLfloat angle);

/**
 * Creates a 3x3 matrix for rotation around the z axis and multiplies it with the given one: matrix = matrix * rotateMatrix
 *
 * @param matrix The final matrix.
 * @param angle The rotation angle in degree.
 */
COMMON_API GLvoid  Matrix3x3RotateRzf(GLfloat matrix[9], const GLfloat angle);

/**
 * Creates a 4x4 matrix for rotation using Euler angles and multiplies it with the given one: matrix = matrix * Rz * Rx * Ry
 *
 * @param matrix The final matrix.
 * @param anglez The rotation angle for the z axis in degree.
 * @param anglex The rotation angle for the x axis in degree.
 * @param angley The rotation angle for the y axis in degree.
 */
COMMON_API GLvoid  Matrix4x4RotateRzRxRyf(GLfloat matrix[16], const GLfloat anglez, const GLfloat anglex, const GLfloat angley);

/**
 * Creates a 4x4 matrix for rotation using Euler angles and multiplies it with the given one: matrix = matrix * Rz * Ry * Rx
 *
 * @param matrix The final matrix.
 * @param anglez The rotation angle for the z axis in degree.
 * @param angley The rotation angle for the y axis in degree.
 * @param anglex The rotation angle for the x axis in degree.
 */
COMMON_API GLvoid  Matrix4x4RotateRzRyRxf(GLfloat matrix[16], const GLfloat anglez, const GLfloat angley, const GLfloat anglex);

/**
 * Creates a 3x3 matrix for rotation using Euler angles and multiplies it with the given one: matrix = matrix * Rz * Rx * Ry
 *
 * @param matrix The final matrix.
 * @param anglez The rotation angle for the z axis in degree.
 * @param anglex The rotation angle for the x axis in degree.
 * @param angley The rotation angle for the y axis in degree.
 */
COMMON_API GLvoid  Matrix3x3RotateRzRxRyf(GLfloat matrix[9], const GLfloat anglez, const GLfloat anglex, const GLfloat angley);

/**
 * Creates a 3x3 matrix for rotation using Euler angles and multiplies it with the given one: matrix = matrix * Rz * Ry * Rx
 *
 * @param matrix The final matrix.
 * @param anglez The rotation angle for the z axis in degree.
 * @param angley The rotation angle for the y axis in degree.
 * @param anglex The rotation angle for the x axis in degree.
 */
COMMON_API GLvoid  Matrix3x3RotateRzRyRxf(GLfloat matrix[9], const GLfloat anglez, const GLfloat angley, const GLfloat anglex);

/**
 * Creates a 4x4 matrix for scaling and multiplies it with the given one: matrix = matrix * scaleMatrix
 *
 * @param matrix The final matrix.
 * @param x The value to scale in the x axis.
 * @param y The value to scale in the y axis.
 * @param z The value to scale in the z axis.
 */
COMMON_API GLvoid  Matrix4x4Scalef(GLfloat matrix[16], const GLfloat x, const GLfloat y, const GLfloat z);

/**
 * Creates a 3x3 matrix for scaling and multiplies it with the given one: matrix = matrix * scaleMatrix
 *
 * @param matrix The final matrix.
 * @param x The value to scale in the x axis.
 * @param y The value to scale in the y axis.
 * @param z The value to scale in the z axis.
 */
COMMON_API GLvoid  Matrix3x3Scalef(GLfloat matrix[9], const GLfloat x, const GLfloat y, const GLfloat z);

/**
 * Creates a 2x2 matrix for scaling and multiplies it with the given one: matrix = matrix * scaleMatrix
 *
 * @param matrix The final matrix.
 * @param x The value to scale in the x axis.
 * @param y The value to scale in the y axis.
 */
COMMON_API GLvoid  Matrix2x2Scalef(GLfloat matrix[4], const GLfloat x, const GLfloat y);

/**
 * Creates a 4x4 matrix for shearing and multiplies it with the given one: matrix = matrix * shearMatrix
 *
 * @param matrix The final matrix.
 * @param shxy Value for shearing x in y direction.
 * @param shxz Value for shearing x in z direction.
 * @param shyx Value for shearing y in x direction.
 * @param shyz Value for shearing y in z direction.
 * @param shzx Value for shearing z in x direction.
 * @param shzy Value for shearing z in y direction.
 */
COMMON_API GLvoid  Matrix4x4Shearf(GLfloat matrix[16], const GLfloat shxy, const GLfloat shxz, const GLfloat shyx, const GLfloat shyz, const GLfloat shzx, const GLfloat shzy);

/**
 * Creates a 3x3 matrix for shearing and multiplies it with the given one: matrix = matrix * shearMatrix
 *
 * @param matrix The final matrix.
 * @param shxy Value for shearing x in y direction.
 * @param shxz Value for shearing x in z direction.
 * @param shyx Value for shearing y in x direction.
 * @param shyz Value for shearing y in z direction.
 * @param shzx Value for shearing z in x direction.
 * @param shzy Value for shearing z in y direction.
 */
COMMON_API GLvoid  Matrix3x3Shearf(GLfloat matrix[9], const GLfloat shxy, const GLfloat shxz, const GLfloat shyx, const GLfloat shyz, const GLfloat shzx, const GLfloat shzy);

/**
 * Creates a 2x2 matrix for shearing and multiplies it with the given one: matrix = matrix * shearMatrix
 *
 * @param matrix The final matrix.
 * @param shx Value for shearing in x direction.
 * @param shy Value for shearing in y direction.
 */
COMMON_API GLvoid  Matrix2x2Shearf(GLfloat matrix[4], const GLfloat shx, const GLfloat shy);

/**
 * Multiplies a 4x4 matrix with a 3D Vector.
 *
 * @param result The transformed vector.
 * @param matrix The matrix used for the transformation.
 * @param vector The used vector for the transformation.
 */
COMMON_API GLvoid  Matrix4x4MultiplyVector3f(GLfloat result[3], const GLfloat matrix[16], const GLfloat vector[3]);

/**
 * Multiplies a 4x4 matrix with a 2D Vector.
 *
 * @param result The transformed vector.
 * @param matrix The matrix used for the transformation.
 * @param vector The used vector for the transformation.
 */
COMMON_API GLvoid  Matrix4x4MultiplyVector2f(GLfloat result[2], const GLfloat matrix[16], const GLfloat vector[2]);

/**
 * Multiplies a 3x3 matrix with a 3D Vector.
 *
 * @param result The transformed vector.
 * @param matrix The matrix used for the transformation.
 * @param vector The used vector for the transformation.
 */
COMMON_API GLvoid  Matrix3x3MultiplyVector3f(GLfloat result[3], const GLfloat matrix[9], const GLfloat vector[3]);

/**
 * Multiplies a 3x3 matrix with a 2D Vector.
 *
 * @param result The transformed vector.
 * @param matrix The matrix used for the transformation.
 * @param vector The used vector for the transformation.
 */
COMMON_API GLvoid  Matrix3x3MultiplyVector2f(GLfloat result[2], const GLfloat matrix[9], const GLfloat vector[2]);

/**
 * Multiplies a 2x2 matrix with a 2D Vector.
 *
 * @param result The transformed vector.
 * @param matrix The matrix used for the transformation.
 * @param vector The used vector for the transformation.
 */
COMMON_API GLvoid  Matrix2x2MultiplyVector2f(GLfloat result[2], const GLfloat matrix[4], const GLfloat vector[2]);

/**
 * Multiplies a 4x4 matrix with a 3D Point, given as homogeneous coordinates.
 *
 * @param result The transformed point.
 * @param matrix The matrix used for the transformation.
 * @param point The used point for the transformation.
 */
COMMON_API GLvoid  Matrix4x4MultiplyPoint4f(GLfloat result[4], const GLfloat matrix[16], const GLfloat point[4]);

/**
 * Multiplies a 3x3 matrix with a 2D Point, given as homogeneous coordinates.
 *
 * @param result The transformed point.
 * @param matrix The matrix used for the transformation.
 * @param point The used point for the transformation.
 */
COMMON_API GLvoid  Matrix3x3MultiplyPoint3f(GLfloat result[3], const GLfloat matrix[9], const GLfloat point[3]);

/**
 * Multiplies a 4x4 matrix with a plane.
 *
 * @param result The transformed plaen.
 * @param matrix The matrix used for the transformation.
 * @param plane The used plane for the transformation.
 */
COMMON_API GLvoid  Matrix4x4MultiplyPlanef(GLfloat result[4], const GLfloat matrix[16], const GLfloat plane[4]);

/**
 * Extracts the Euler angles from a 4x4 matrix, which was created by a Rz * Rx * Ry transformation.
 *
 * @param angles Resulting anglex (Pitch), angley (Yaw) and anglez (Roll) in degrees.
 * @param matrix The used matrix.
 *
 * @return GL_TRUE, if a extraction could be done.
 */
COMMON_API GLboolean  Matrix4x4GetEulerRzRxRyf(GLfloat angles[3], const GLfloat matrix[16]);

/**
 * Extracts the Euler angles from a 4x4 matrix, which was created by a Rz * Ry * Rz transformation.
 *
 * @param angles Resulting anglex (Pitch), angley (Yaw) and anglez (Roll) in degrees.
 * @param matrix The used matrix.
 *
 * @return GL_TRUE, if a extraction could be done.
 */
COMMON_API GLboolean  Matrix4x4GetEulerRzRyRxf(GLfloat angles[3], const GLfloat matrix[16]);

/**
 * Extracts the Euler angles from a 3x3 matrix, which was created by a Rz * Rx * Ry transformation.
 *
 * @param angles Resulting anglex (Pitch), angley (Yaw) and anglez (Roll) in degrees.
 * @param matrix The used matrix.
 *
 * @return GL_TRUE, if a extraction could be done.
 */
COMMON_API GLboolean  Matrix3x3GetEulerRzRxRyf(GLfloat angles[3], const GLfloat matrix[9]);

/**
 * Extracts the Euler angles from a 3x3 matrix, which was created by a Rz * Ry * Rx transformation.
 *
 * @param angles Resulting anglex (Pitch), angley (Yaw) and anglez (Roll) in degrees.
 * @param matrix The used matrix.
  *
 * @return GL_TRUE, if a extraction could be done.
 */
COMMON_API GLboolean  Matrix3x3GetEulerRzRyRxf(GLfloat angles[3], const GLfloat matrix[9]);

/**
 * Extracts the angle from a 3x3 matrix, which is used in 2D.
 *
 * @param angle Resulting angle in degrees.
 * @param matrix The used matrix.
 *
 * @return GL_TRUE, if a extraction could be done.
 */
COMMON_API GLboolean  Matrix3x3GetAnglef(GLfloat* angle, const GLfloat matrix[9]);

/**
 * Extracts the angle from a 2x2 matrix.
 *
 * @param angle Resulting angle in degrees.
 * @param matrix The used matrix.
 *
 * @return GL_TRUE, if a extraction could be done.
 */
COMMON_API GLboolean  Matrix2x2GetAnglef(GLfloat* angle, const GLfloat matrix[4]);

/**
 * Extracts the scales from a 4x4 matrix.
 *
 * @param scales Resulting sx, sy, sz.
 * @param matrix The used matrix.
 */
COMMON_API GLvoid  Matrix4x4GetScalef(GLfloat scales[3], const GLfloat matrix[16]);

/**
 * Extracts the scales from a 3x3 matrix.
 *
 * @param scales Resulting sx, sy, sz.
 * @param matrix The used matrix.
 */
COMMON_API GLvoid  Matrix3x3GetScalef(GLfloat scales[3], const GLfloat matrix[9]);

/**
 * Extracts the scales from a 2x2 matrix.
 *
 * @param scales Resulting sx, sy.
 * @param matrix The used matrix.
 */
COMMON_API GLvoid  Matrix2x2GetScalef(GLfloat scales[2], const GLfloat matrix[4]);

/**
 * Extracts the translates from a 4x4 matrix.
 *
 * @param translates Resulting x, y and z.
 * @param matrix The used matrix.
 */
COMMON_API GLvoid  Matrix4x4GetTranslatef(GLfloat translates[3], const GLfloat matrix[16]);

/**
 * Extracts the translates from a 3x3 matrix, which is used for 2D.
 *
 * @param translates Resulting x and y.
 * @param matrix The used matrix.
 */
COMMON_API GLvoid  Matrix3x3GetTranslatef(GLfloat translates[2], const GLfloat matrix[9]);

/**
 * Multiplies a NxN matrix with a Vector with N elements.
 *
 * @param result The transformed vector.
 * @param matrix The matrix used for the transformation.
 * @param vector The used vector for the transformation.
 * @param n 	 The number of elements.
 *
 * @return GL_TRUE, if succeeded.
 */
//COMMON_API GLboolean  MatrixNxNMultiplyVectorNc(Complex* result, const Complex* matrix, const Complex* vector, const GLint n);

#endif /* GLUS_MATRIX_H_ */
