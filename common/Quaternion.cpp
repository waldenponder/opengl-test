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
#include "Quaternion.h"
#include "Vector.h"
#include "Utility.h"
using namespace Utility;

GLvoid  QuaternionIdentityf(GLfloat quaternion[4])
{
    quaternion[0] = 0.0f;
    quaternion[1] = 0.0f;
    quaternion[2] = 0.0f;
    quaternion[3] = 1.0f;
}

GLvoid  QuaternionCopyf(GLfloat result[4], const GLfloat quaternion[4])
{
    result[0] = quaternion[0];
    result[1] = quaternion[1];
    result[2] = quaternion[2];
    result[3] = quaternion[3];
}

GLfloat  QuaternionNormf(const GLfloat quaternion[4])
{
    GLfloat x = quaternion[0];
    GLfloat y = quaternion[1];
    GLfloat z = quaternion[2];
    GLfloat w = quaternion[3];

    return sqrtf(x * x + y * y + z * z + w * w);
}

GLboolean  QuaternionNormalizef(GLfloat quaternion[4])
{
    GLint i;

    GLfloat norm = QuaternionNormf(quaternion);

    if (norm == 0.0f)
    {
        return GL_FALSE;
    }

    for (i = 0; i < 4; i++)
    {
        quaternion[i] /= norm;
    }

    return GL_TRUE;
}

GLvoid  QuaternionAddQuaternionf(GLfloat result[4], const GLfloat quaternion0[4], const GLfloat quaternion1[4])
{
    GLint i;

    for (i = 0; i < 4; i++)
    {
        result[i] = quaternion0[i] + quaternion1[i];
    }
}

GLvoid  QuaternionSubQuaternionf(GLfloat result[4], const GLfloat quaternion0[4], const GLfloat quaternion1[4])
{
    GLint i;

    for (i = 0; i < 4; i++)
    {
        result[i] = quaternion0[i] - quaternion1[i];
    }
}

GLvoid  QuaternionMultiplyQuaternionf(GLfloat result[4], const GLfloat quaternion0[4], const GLfloat quaternion1[4])
{
    GLfloat temp[4];

    temp[0] = quaternion0[3] * quaternion1[0] + quaternion0[0] * quaternion1[3] + quaternion0[1] * quaternion1[2] - quaternion0[2] * quaternion1[1];
    temp[1] = quaternion0[3] * quaternion1[1] - quaternion0[0] * quaternion1[2] + quaternion0[1] * quaternion1[3] + quaternion0[2] * quaternion1[0];
    temp[2] = quaternion0[3] * quaternion1[2] + quaternion0[0] * quaternion1[1] - quaternion0[1] * quaternion1[0] + quaternion0[2] * quaternion1[3];
    temp[3] = quaternion0[3] * quaternion1[3] - quaternion0[0] * quaternion1[0] - quaternion0[1] * quaternion1[1] - quaternion0[2] * quaternion1[2];

    QuaternionCopyf(result, temp);
}

GLvoid  QuaternionConjugatef(GLfloat quaternion[4])
{
    quaternion[0] = -quaternion[0];
    quaternion[1] = -quaternion[1];
    quaternion[2] = -quaternion[2];
    // w remains the same
}

GLboolean  QuaternionInversef(GLfloat quaternion[4])
{
    GLint i;

    GLfloat norm = QuaternionNormf(quaternion);

    if (norm == 0.0f)
    {
        return GL_FALSE;
    }

    QuaternionConjugatef(quaternion);

    for (i = 0; i < 4; i++)
    {
        quaternion[i] /= (norm * norm);
    }

    return GL_TRUE;
}

GLvoid  QuaternionInverseUnitf(GLfloat quaternion[4])
{
    QuaternionConjugatef(quaternion);
}

GLvoid  QuaternionRotatef(GLfloat quaternion[4], const GLfloat angle, const GLfloat x, const GLfloat y, const GLfloat z)
{
    GLfloat halfAngleRadian = MathDegToRadf(angle) * 0.5f;

    GLfloat s = sinf(halfAngleRadian);

    GLfloat normalized[3] = { x, y, z };

    Vector3Normalizef(normalized);

    quaternion[0] = normalized[0] * s;
    quaternion[1] = normalized[1] * s;
    quaternion[2] = normalized[2] * s;
    quaternion[3] = cosf(halfAngleRadian);
}

GLvoid  QuaternionRotateRxf(GLfloat quaternion[4], const GLfloat angle)
{
    GLfloat halfAngleRadian = MathDegToRadf(angle) * 0.5f;

    quaternion[0] = sinf(halfAngleRadian);
    quaternion[1] = 0.0f;
    quaternion[2] = 0.0f;
    quaternion[3] = cosf(halfAngleRadian);
}

GLvoid  QuaternionRotateRyf(GLfloat quaternion[4], const GLfloat angle)
{
    GLfloat halfAngleRadian = MathDegToRadf(angle) * 0.5f;

    quaternion[0] = 0.0f;
    quaternion[1] = sinf(halfAngleRadian);
    quaternion[2] = 0.0f;
    quaternion[3] = cosf(halfAngleRadian);
}

GLvoid  QuaternionRotateRzf(GLfloat quaternion[4], const GLfloat angle)
{
    GLfloat halfAngleRadian = MathDegToRadf(angle) * 0.5f;

    quaternion[0] = 0.0f;
    quaternion[1] = 0.0f;
    quaternion[2] = sinf(halfAngleRadian);
    quaternion[3] = cosf(halfAngleRadian);
}

GLvoid  QuaternionRotateRzRxRyf(GLfloat quaternion[4], const GLfloat anglez, const GLfloat anglex, const GLfloat angley)
{
	GLfloat rotZ[4];
	GLfloat rotX[4];
	GLfloat rotY[4];

    QuaternionRotateRzf(rotZ, anglez);
    QuaternionRotateRxf(rotX, anglex);
	QuaternionRotateRyf(rotY, angley);

	QuaternionMultiplyQuaternionf(quaternion, rotZ, rotX);
	QuaternionMultiplyQuaternionf(quaternion, quaternion, rotY);
}

COMMON_API GLvoid  QuaternionRotateRzRyRxf(GLfloat quaternion[4], const GLfloat anglez, const GLfloat angley, const GLfloat anglex)
{
	GLfloat rotZ[4];
	GLfloat rotY[4];
	GLfloat rotX[4];

    QuaternionRotateRzf(rotZ, anglez);
	QuaternionRotateRyf(rotY, angley);
    QuaternionRotateRxf(rotX, anglex);

	QuaternionMultiplyQuaternionf(quaternion, rotZ, rotY);
	QuaternionMultiplyQuaternionf(quaternion, quaternion, rotX);
}

GLvoid  QuaternionGetMatrix4x4f(GLfloat matrix[16], const GLfloat quaternion[4])
{
    GLfloat x = quaternion[0];
    GLfloat y = quaternion[1];
    GLfloat z = quaternion[2];
    GLfloat w = quaternion[3];

    matrix[0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
    matrix[1] = 2.0f * x * y + 2.0f * w * z;
    matrix[2] = 2.0f * x * z - 2.0f * w * y;
    matrix[3] = 0.0f;

    matrix[4] = 2.0f * x * y - 2.0f * w * z;
    matrix[5] = 1.0f - 2.0f * x * x - 2.0f * z * z;
    matrix[6] = 2.0f * y * z + 2.0f * w * x;
    matrix[7] = 0.0f;

    matrix[8] = 2.0f * x * z + 2.0f * w * y;
    matrix[9] = 2.0f * y * z - 2.0f * w * x;
    matrix[10] = 1.0f - 2.0f * x * x - 2.0f * y * y;
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

GLvoid  QuaternionGetMatrix3x3f(GLfloat matrix[9], const GLfloat quaternion[4])
{
    GLfloat x = quaternion[0];
    GLfloat y = quaternion[1];
    GLfloat z = quaternion[2];
    GLfloat w = quaternion[3];

    matrix[0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
    matrix[1] = 2.0f * x * y + 2.0f * w * z;
    matrix[2] = 2.0f * x * z - 2.0f * w * y;

    matrix[3] = 2.0f * x * y - 2.0f * w * z;
    matrix[4] = 1.0f - 2.0f * x * x - 2.0f * z * z;
    matrix[5] = 2.0f * y * z + 2.0f * w * x;

    matrix[6] = 2.0f * x * z + 2.0f * w * y;
    matrix[7] = 2.0f * y * z - 2.0f * w * x;
    matrix[8] = 1.0f - 2.0f * x * x - 2.0f * y * y;
}

GLboolean  QuaternionGetPoint4f(GLfloat point[4], const GLfloat quaternion[4])
{
	if (quaternion[3] != 0.0f)
	{
		return GL_FALSE;
	}

	point[0] = quaternion[0];
	point[1] = quaternion[1];
	point[2] = quaternion[2];
	point[3] = 1.0f;

	return GL_TRUE;
}

GLboolean  QuaternionGetVector3f(GLfloat vector[3], const GLfloat quaternion[4])
{
	if (quaternion[3] != 0.0f)
	{
		return GL_FALSE;
	}

	vector[0] = quaternion[0];
	vector[1] = quaternion[1];
	vector[2] = quaternion[2];

	return GL_TRUE;
}

GLboolean  QuaternionGetEulerRzRxRyf(GLfloat angles[3], const GLfloat quaternion[4])
{
    GLfloat x = quaternion[0];
    GLfloat y = quaternion[1];
    GLfloat z = quaternion[2];
    GLfloat w = quaternion[3];

    GLfloat f00 = 1.0f - 2.0f * y * y - 2.0f * z * z;
    GLfloat f10 = 2.0f * x * y + 2.0f * w * z;
    GLfloat f20 = 2.0f * x * z - 2.0f * w * y;

    GLfloat f01 = 2.0f * x * y - 2.0f * w * z;
    GLfloat f11 = 1.0f - 2.0f * x * x - 2.0f * z * z;
    GLfloat f21 = 2.0f * y * z + 2.0f * w * x;

    GLfloat f22 = 1.0f - 2.0f * x * x - 2.0f * y * y;

    if (!(f20 == 0.0f && f22 == 0.0f) && !(f01 == 0.0f && f11 == 0.0f))
    {
        angles[0] = MathRadToDegf(asinf(f21));
        angles[1] = MathRadToDegf(atan2f(-f20, f22));
        angles[2] = MathRadToDegf(atan2f(-f01, f11));
    }
    else if (!(f10 == 0.0f && f00 == 0.0f))
    {
        angles[0] = MathRadToDegf(asinf(f21));
        angles[1] = 0.0f;
        angles[2] = MathRadToDegf(atan2f(f10, f00));
    }
    else
    {
    	return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean   QuaternionGetEulerRzRyRxf(GLfloat angles[3], const GLfloat quaternion[4])
{
    GLfloat x = quaternion[0];
    GLfloat y = quaternion[1];
    GLfloat z = quaternion[2];
    GLfloat w = quaternion[3];

    GLfloat f00 = 1.0f - 2.0f * y * y - 2.0f * z * z;
	GLfloat f10 = 2.0f * x * y + 2.0f * w * z;
    GLfloat f20 = 2.0f * x * z - 2.0f * w * y;

	GLfloat f01 = 2.0f * x * y - 2.0f * w * z;
	GLfloat f11 = 1.0f - 2.0f * x * x - 2.0f * z * z;
	GLfloat f21 = 2.0f * y * z + 2.0f * w * x;

	GLfloat f22 = 1.0f - 2.0f * x * x - 2.0f * y * y;

    if (!(f21 == 0.0f && f22 == 0.0f) && !(f10 == 0.0f && f00 == 0.0f))
    {
        angles[0] = MathRadToDegf(atan2f(f21, f22));
    	angles[1] = MathRadToDegf(asinf(-f20));
    	angles[2] = MathRadToDegf(atan2f(f10, f00));
    }
    else if (!(f01 == 0.0f && f11 == 0.0f))
    {
        angles[0] = MathRadToDegf(atan2f(f01, f11));
    	angles[1] = MathRadToDegf(asinf(-f20));
    	angles[2] = 0.0f;
    }
    else
    {
    	return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean  QuaternionSlerpf(GLfloat result[4], const GLfloat quaternion0[4], const GLfloat quaternion1[4], const GLfloat t)
{
    GLint i;

    GLfloat cosAlpha = quaternion0[0] * quaternion1[0] + quaternion0[1] * quaternion1[1] + quaternion0[2] * quaternion1[2] + quaternion0[3] * quaternion1[3];

    GLfloat alpha = acosf(MathClampf(cosAlpha, -1.0f, 1.0f));

    GLfloat sinAlpha = sinf(alpha);

    GLfloat a;
    GLfloat b;

    if (sinAlpha == 0.0f)
    {
    	QuaternionCopyf(result, quaternion0);

    	return GL_FALSE;
    }

    a = sinf(alpha * (1.0f - t)) / sinAlpha;

    b = sinf(alpha * t) / sinAlpha;

    for (i = 0; i < 4; i++)
    {
        result[i] = a * quaternion0[i] + b * quaternion1[i];
    }

    return GL_TRUE;
}
