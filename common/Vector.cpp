#include "stdafx.h"
#include "Vector.h"

GLvoid  Vector3Copyf(GLfloat result[3], const GLfloat vector[3])
{
	result[0] = vector[0];
	result[1] = vector[1];
	result[2] = vector[2];
}

GLvoid  Vector2Copyf(GLfloat result[2], const GLfloat vector[2])
{
	result[0] = vector[0];
	result[1] = vector[1];
}

GLvoid  Vector3AddVector3f(GLfloat result[3], const GLfloat vector0[3], const GLfloat vector1[3])
{
	result[0] = vector0[0] + vector1[0];
	result[1] = vector0[1] + vector1[1];
	result[2] = vector0[2] + vector1[2];
}

GLvoid  Vector2AddVector2f(GLfloat result[2], const GLfloat vector0[2], const GLfloat vector1[2])
{
	result[0] = vector0[0] + vector1[0];
	result[1] = vector0[1] + vector1[1];
}

GLvoid  Vector3SubtractVector3f(GLfloat result[3], const GLfloat vector0[3], const GLfloat vector1[3])
{
	result[0] = vector0[0] - vector1[0];
	result[1] = vector0[1] - vector1[1];
	result[2] = vector0[2] - vector1[2];
}

GLvoid  Vector2SubtractVector2f(GLfloat result[2], const GLfloat vector0[2], const GLfloat vector1[2])
{
	result[0] = vector0[0] - vector1[0];
	result[1] = vector0[1] - vector1[1];
}

GLvoid  Vector3MultiplyScalarf(GLfloat result[3], const GLfloat vector[3], const GLfloat scalar)
{
	result[0] = vector[0] * scalar;
	result[1] = vector[1] * scalar;
	result[2] = vector[2] * scalar;
}

GLvoid  Vector2MultiplyScalarf(GLfloat result[2], const GLfloat vector[2], const GLfloat scalar)
{
	result[0] = vector[0] * scalar;
	result[1] = vector[1] * scalar;
}

GLfloat  Vector3Lengthf(const GLfloat vector[3])
{
	return sqrtf(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
}

GLfloat  Vector2Lengthf(const GLfloat vector[2])
{
	return sqrtf(vector[0] * vector[0] + vector[1] * vector[1]);
}

GLboolean  Vector3Normalizef(GLfloat vector[3])
{
	GLuint i; 

	GLfloat length = Vector3Lengthf(vector);

	if (length == 0.0f)
	{
		return GL_FALSE;
	}

	for (i = 0; i < 3; i++)
	{
		vector[i] /= length;
	}

	return GL_TRUE;
}

GLboolean  Vector2Normalizef(GLfloat vector[2])
{
	GLuint i;

	GLfloat length = Vector2Lengthf(vector);

	if (length == 0.0f)
	{
		return GL_FALSE;	
	}

	for (i = 0; i < 2; i++)
	{
		vector[i] /= length;
	}

	return GL_TRUE;
}

GLfloat  Vector3Dotf(const GLfloat vector0[3], const GLfloat vector1[3])
{
	return vector0[0] * vector1[0] + vector0[1] * vector1[1] + vector0[2] * vector1[2];
}

GLfloat  Vector2Dotf(const GLfloat vector0[2], const GLfloat vector1[2])
{
	return vector0[0] * vector1[0] + vector0[1] * vector1[1];
}

GLvoid  Vector3Crossf(GLfloat result[3], const GLfloat vector0[3], const GLfloat vector1[3])
{
	GLuint i;

	GLfloat temp[3];

	temp[0] = vector0[1] * vector1[2] - vector0[2] * vector1[1];
	temp[1] = vector0[2] * vector1[0] - vector0[0] * vector1[2];
	temp[2] = vector0[0] * vector1[1] - vector0[1] * vector1[0];

	for (i = 0; i < 3; i++)
	{
		result[i] = temp[i];
	}
}

GLvoid  Vector3GetQuaternionf(GLfloat result[4], const GLfloat vector[3])
{
	result[0] = vector[0];
	result[1] = vector[1];
	result[2] = vector[2];
	result[3] = 0.0f;
}

GLvoid  Vector3GetPoint4f(GLfloat result[4], const GLfloat vector[3])
{
	result[0] = vector[0];
	result[1] = vector[1];
	result[2] = vector[2];
	result[3] = 1.0f;
}

GLvoid  Vector2GetPoint3f(GLfloat result[3], const GLfloat vector[2])
{
	result[0] = vector[0];
	result[1] = vector[1];
	result[2] = 1.0f;
}

GLboolean  Vector3GramSchmidtOrthof(GLfloat result[3], const GLfloat u[3], const GLfloat v[3])
{
	GLfloat uProjV[3];

	GLfloat vDotU;

	GLfloat uDotU = Vector3Dotf(u, u);

	if (uDotU == 0.0f)
	{
		return GL_FALSE;
	}

	vDotU = Vector3Dotf(v, u);

	uProjV[0] = u[0] * vDotU / uDotU;
	uProjV[1] = u[1] * vDotU / uDotU;
	uProjV[2] = u[2] * vDotU / uDotU;

	Vector3SubtractVector3f(result, v, uProjV);

	return GL_TRUE;
}

GLboolean  Vector2GramSchmidtOrthof(GLfloat result[2], const GLfloat u[2], const GLfloat v[2])
{
	GLfloat uProjV[2];

	GLfloat vDotU;

	GLfloat uDotU = Vector2Dotf(u, u);

	if (uDotU == 0.0f)
	{
		return GL_FALSE;
	}

	vDotU = Vector2Dotf(v, u);

	uProjV[0] = u[0] * vDotU / uDotU;
	uProjV[1] = u[1] * vDotU / uDotU;

	Vector2SubtractVector2f(result, v, uProjV);

	return GL_TRUE;
}

GLvoid  Vector3Reflectf(GLfloat result[3], const GLfloat incident[3], const GLfloat normal[3])
{
	Vector3MultiplyScalarf(result, normal, 2.0f * Vector3Dotf(normal, incident));

	Vector3SubtractVector3f(result, incident, result);
}

GLvoid  Vector2Reflectf(GLfloat result[2], const GLfloat incident[2], const GLfloat normal[2])
{
	Vector2MultiplyScalarf(result, normal, 2.0f * Vector2Dotf(normal, incident));

	Vector2SubtractVector2f(result, incident, result);
}

GLvoid  Vector3Refractf(GLfloat result[3], const GLfloat incident[3], const GLfloat normal[3], const float eta)
{
	// see http://www.opengl.org/sdk/docs/manglsl/xhtml/refract.xml
	// see http://en.wikipedia.org/wiki/Snell%27s_law
	// see http://www.hugi.scene.org/online/coding/hugi%2023%20-%20torefrac.htm for a and b vector.
	// In this implementation, the incident vector points into the interface. So the sings do change.

	GLfloat nDotI = Vector3Dotf(normal, incident);

	GLfloat k = 1.0f - eta * eta * (1.0f - nDotI * nDotI);

	if (k < 0.0f)
	{
		result[0] = 0.0f;
		result[1] = 0.0f;
		result[2] = 0.0f;
	}
	else
	{
		GLfloat a[3];
		GLfloat b[3];

		Vector3MultiplyScalarf(a, incident, eta);

		Vector3MultiplyScalarf(b, normal, eta * nDotI + sqrtf(k));

		Vector3SubtractVector3f(result, a, b);
	}
}

GLvoid  Vector2Refractf(GLfloat result[2], const GLfloat incident[2], const GLfloat normal[2], const float eta)
{
	GLfloat nDotI = Vector2Dotf(normal, incident);

	GLfloat k = 1.0f - eta * eta * (1.0f - nDotI * nDotI);

	if (k < 0.0f)
	{
		result[0] = 0.0f;
		result[1] = 0.0f;
	}
	else
	{
		GLfloat a[2];
		GLfloat b[2];

		Vector2MultiplyScalarf(a, incident, eta);

		Vector2MultiplyScalarf(b, normal, eta * nDotI + sqrtf(k));

		Vector2SubtractVector2f(result, a, b);
	}
}

GLfloat  Vector3Fresnelf(const GLfloat incident[3], const GLfloat normal[3], const GLfloat R0)
{
	// see http://en.wikipedia.org/wiki/Schlick%27s_approximation

	GLfloat negIncident[3];

	Vector3MultiplyScalarf(negIncident, incident, -1.0f);

	return R0 + (1.0f - R0) * powf(1.0f - Vector3Dotf(negIncident, normal), 5.0f);
}

GLfloat  Vector2Fresnelf(const GLfloat incident[2], const GLfloat normal[2], const GLfloat R0)
{
	GLfloat negIncident[2];

	Vector2MultiplyScalarf(negIncident, incident, -1.0f);

	return R0 + (1.0f - R0) * powf(1.0f - Vector2Dotf(negIncident, normal), 5.0f);
}

//

GLvoid  VectorNCopyc(Complex* result, const Complex* vector, const GLuint n)
{
	GLuint i;

	for (i = 0; i < n; i++)
	{
		result[i] = vector[i];
	}
}

GLvoid  VectorNComplexToFloatc(GLfloat* result, const Complex* vector, const GLuint n)
{
	GLuint i;

	for (i = 0; i < n; i++)
	{
		result[2 * i + 0] = vector[i].real;
		result[2 * i + 1] = vector[i].imaginary;
	}
}

GLvoid  VectorNFloatToComplexc(Complex* result, const GLfloat* vector, const GLuint n)
{
	GLuint i;

	for (i = 0; i < n; i++)
	{
		result[i].real = vector[2 * i + 0];
		result[i].imaginary = vector[2 * i + 1];
	}
}

GLvoid  VectorNMultiplyScalarc(Complex* result, const Complex* vector, const GLuint n, const GLfloat scalar)
{
	GLuint i;

	for (i = 0; i < n; i++)
	{
		//////////////////////////////ComplexMultiplyScalarc(&result[i], &vector[i], scalar);
	}
}

GLvoid  VectorNConjugatec(Complex* result, const Complex* vector, const GLuint n)
{
	GLuint i;

	for (i = 0; i < n; i++)
	{
		//////////////////////////////ComplexConjugatec(&result[i], &vector[i]);
	}
}
