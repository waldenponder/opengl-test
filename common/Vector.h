#pragma once
#include "common.inner.h"
#include "Utility.h"

/**
 * Copies a 3D Vector.
 *
 * @param result The destination vector.
 * @param vector The source vector.
 */
COMMON_API GLvoid  Vector3Copyf(GLfloat result[3], const GLfloat vector[3]);

/**
 * Copies a 2D Vector.
 *
 * @param result The destination vector.
 * @param vector The source vector.
 */
COMMON_API GLvoid  Vector2Copyf(GLfloat result[2], const GLfloat vector[2]);

/**
 * Adds a 3D Vector to another.
 *
 * @param result The final vector.
 * @param vector0 The first vector.
 * @param vector1 The second vector.
 */
COMMON_API GLvoid  Vector3AddVector3f(GLfloat result[3], const GLfloat vector0[3], const GLfloat vector1[3]);

/**
 * Adds a 2D Vector to another.
 *
 * @param result The final vector.
 * @param vector0 The first vector.
 * @param vector1 The second vector.
 */
COMMON_API GLvoid  Vector2AddVector2f(GLfloat result[2], const GLfloat vector0[2], const GLfloat vector1[2]);

/**
 * Subtracts a 3D Vector from another.
 *
 * @param result The final vector.
 * @param vector0 The vector subtracted by vector1.
 * @param vector1 The vector subtracted from vector0.
 */
COMMON_API GLvoid  Vector3SubtractVector3f(GLfloat result[3], const GLfloat vector0[3], const GLfloat vector1[3]);

/**
 * Subtracts a 2D Vector from another.
 *
 * @param result The final vector.
 * @param vector0 The vector subtracted by vector1.
 * @param vector1 The vector subtracted from vector0.
 */
COMMON_API GLvoid  Vector2SubtractVector2f(GLfloat result[2], const GLfloat vector0[2], const GLfloat vector1[2]);

/**
 * Multiplies a 3D Vector by a scalar.
 *
 * @param result The final vector.
 * @param vector The used vector for multiplication.
 * @param scalar The scalar.
 */
COMMON_API GLvoid  Vector3MultiplyScalarf(GLfloat result[3], const GLfloat vector[3], const GLfloat scalar);

/**
 * Multiplies a 2D Vector by a scalar.
 *
 * @param result The final vector.
 * @param vector The used vector for multiplication.
 * @param scalar The scalar.
 */
COMMON_API GLvoid  Vector2MultiplyScalarf(GLfloat result[2], const GLfloat vector[2], const GLfloat scalar);

/**
 * Calculates the length of a 3D Vector.
 *
 * @param vector The used vector.
 *
 * @return The length of the vector.
 */				 
COMMON_API GLfloat  Vector3Lengthf(const GLfloat vector[3]);

/**
 * Calculates the length of a 2D Vector.
 *
 * @param vector The used vector.
 *
 * @return The length of the vector.
 */
COMMON_API GLfloat  Vector2Lengthf(const GLfloat vector[2]);

/**
 * Normalizes the given 3D Vector.
 *
 * @param vector The vector to normalize.
 *
 * @return GL_TRUE, if normalization succeeded.
 */					  
COMMON_API GLboolean  Vector3Normalizef(GLfloat vector[3]);

/**
 * Normalizes the given 2D Vector.
 *
 * @param vector The vector to normalize.
 *
 * @return GL_TRUE, if normalization succeeded.
 */
COMMON_API GLboolean  Vector2Normalizef(GLfloat vector[2]);

/**
 * Calculates the dot product of two 3D vectors.
 *
 * @param vector0 The first vector.
 * @param vector1 The second vector.
 *
 * @return The dot product.
 */
COMMON_API GLfloat  Vector3Dotf(const GLfloat vector0[3], const GLfloat vector1[3]);

/**
 * Calculates the dot product of two 2D vectors.
 *
 * @param vector0 The first vector.
 * @param vector1 The second vector.
 *
 * @return The dot product.
 */
COMMON_API GLfloat  Vector2Dotf(const GLfloat vector0[2], const GLfloat vector1[2]);

/**
 * Calculates the cross product of two 3D vectors: vector0 x vector1.
 *
 * @param result The resulting vector from the cross product.
 * @param vector0 The first vector.
 * @param vector1 The second vector.
 */
COMMON_API GLvoid  Vector3Crossf(GLfloat result[3], const GLfloat vector0[3], const GLfloat vector1[3]);

/**
 * Creates a quaternion out of a 3D vector.
 *
 * @param result The resulting quaternion.
 * @param vector The used vector.
 */
COMMON_API GLvoid  Vector3GetQuaternionf(GLfloat result[4], const GLfloat vector[3]);

/**
 * Creates a 3D point, given as homogeneous coordinates, out of a 3D vector.
 *
 * @param result The resulting point.
 * @param vector The used vector.
 */
COMMON_API GLvoid  Vector3GetPoint4f(GLfloat result[4], const GLfloat vector[3]);

/**
 * Creates a 2D point, given as homogeneous coordinates, out of a 2D vector.
 *
 * @param result The resulting point.
 * @param vector The used vector.
 */
COMMON_API GLvoid  Vector2GetPoint3f(GLfloat result[3], const GLfloat vector[2]);

/**
 * Creates a 3D vector orthogonal to u on the u/v plane.
 *
 * @param result The resulting vector.
 * @param u 	 The vector to calculate a orthogonal vector to.
 * @param v 	 The vector, which is projected to the orthogonal line of u.
 *
 * @return GL_TRUE, if a vector could be calculated.
 */
COMMON_API GLboolean  Vector3GramSchmidtOrthof(GLfloat result[3], const GLfloat u[3], const GLfloat v[3]);

/**
 * Creates a 2D vector orthogonal to u.
 *
 * @param result The resulting vector.
 * @param u 	 The vector to calculate a orthogonal vector to.
 * @param v 	 The vector, which is projected to the orthogonal line of u.
 *
 * @return GL_TRUE, if a vector could be calculated.
 */
COMMON_API GLboolean  Vector2GramSchmidtOrthof(GLfloat result[2], const GLfloat u[2], const GLfloat v[2]);

/**
 * Calculate the reflection direction for an incident vector.
 *
 * @param result	The reflection vector.
 * @param incident	The incident vector.
 * @param normal	The normal vector.
 */
COMMON_API GLvoid  Vector3Reflectf(GLfloat result[3], const GLfloat incident[3], const GLfloat normal[3]);

/**
 * Calculate the reflection direction for an incident vector.
 *
 * @param result	The reflection vector.
 * @param incident	The incident vector.
 * @param normal	The normal vector.
 */
COMMON_API GLvoid  Vector2Reflectf(GLfloat result[2], const GLfloat incident[2], const GLfloat normal[2]);

/**
 * Calculate the refraction direction for an incident vector.
 *
 * @param result	The refraction vector.
 * @param incident	The incident vector.
 * @param normal	The normal vector.
 * @param eta		The ratio of indices of refraction.
 */
COMMON_API GLvoid  Vector3Refractf(GLfloat result[3], const GLfloat incident[3], const GLfloat normal[3], const float eta);

/**
 * Calculate the refraction direction for an incident vector.
 *
 * @param result	The refraction vector.
 * @param incident	The incident vector.
 * @param normal	The normal vector.
 * @param eta		The ratio of indices of refraction.
 */
COMMON_API GLvoid  Vector2Refractf(GLfloat result[2], const GLfloat incident[2], const GLfloat normal[2], const float eta);

/**
 * Calculate the specular reflection coefficient, based on Schlick's approximation for the Fresnel term.
 *
 * @param incident	The incident vector.
 * @param normal	The normal vector.
 * @param R0		The reflection coefficient for light incoming parallel to the normal.
 *
 * @return Specular reflection coefficient.
 */
COMMON_API GLfloat  Vector3Fresnelf(const GLfloat incident[3], const GLfloat normal[3], const GLfloat R0);

/**
 * Calculate the specular reflection coefficient, based on Schlick's approximation for the Fresnel term.
 *
 * @param incident	The incident vector.
 * @param normal	The normal vector.
 * @param R0		The reflection coefficient for light incoming parallel to the normal.
 *
 * @return Specular reflection coefficient.
 */
COMMON_API GLfloat  Vector2Fresnelf(const GLfloat incident[2], const GLfloat normal[2], const GLfloat R0);

/**
 * Copies a Vector with N elements.
 *
 * @param result The destination vector.
 * @param vector The source vector.
 * @param n 	 The number of elements.
 */
COMMON_API GLvoid  VectorNCopyc(Complex* result, const Complex* vector, const GLuint n);

/**
 * Converts a complex number Vector with N elements to a float Vector.
 *
 * @param result The destination vector.
 * @param vector The source vector.
 * @param n 	 The number of elements.
 */										   
COMMON_API GLvoid  VectorNComplexToFloatc(GLfloat* result, const Complex* vector, const GLuint n);

/**
 * Converts a float Vector with N elements to a complex Vector.
 *
 * @param result The destination vector.
 * @param vector The source vector.
 * @param n 	 The number of elements.
 */
COMMON_API GLvoid  VectorNFloatToComplexc(Complex* result, const GLfloat* vector, const GLuint n);

/**
 * Multiplies a Vector with N elements by a scalar.
 *
 * @param result The final vector.
 * @param vector The used vector for multiplication.
 * @param n 	 The number of elements.
 * @param scalar The scalar.
 */
COMMON_API GLvoid  VectorNMultiplyScalarc(Complex* result, const Complex* vector, const GLuint n, const GLfloat scalar);

/**
 * Calculates the complex conjugate of a Vector with N elements.
 *
 * @param result The vector, containing the complex conjugate.
 * @param vector The source vector.
 * @param n 	 The number of elements.
 */
COMMON_API GLvoid  VectorNConjugatec(Complex* result, const Complex* vector, const GLuint n);