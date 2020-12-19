#include "stdafx.h"
#include "Matrix.h"
#include "Vector.h"

using namespace Utility;
 
static GLboolean Matrix4x4IsRowZero(const double matrix[16], GLint row)
{
    GLint column;

    for (column = 0; column < 4; column++)
    {
        if (matrix[column * 4 + row] != 0.0)
        {
            return GL_FALSE;
        }
    }

    return GL_TRUE;
}

static GLboolean Matrix4x4IsColumnZero(const double matrix[16], GLint column)
{
    GLint row;

    for (row = 0; row < 4; row++)
    {
        if (matrix[column * 4 + row] != 0.0)
        {
            return GL_FALSE;
        }
    }

    return GL_TRUE;
}

static GLvoid Matrix4x4DivideRowByScalar(double result[16], double matrix[16], GLint row, double  value)
{
    GLint column;
    // No inverse for robustness

    for (column = 0; column < 4; column++)
    {
        matrix[column * 4 + row] /= value;
        result[column * 4 + row] /= value;
    }
}

static GLvoid Matrix4x4SwapRow(double result[16], double matrix[16], GLint rowOne, GLint rowTwo)
{
    GLint column;

    double temp;

    for (column = 0; column < 4; column++)
    {
        temp = matrix[column * 4 + rowOne];
        matrix[column * 4 + rowOne] = matrix[column * 4 + rowTwo];
        matrix[column * 4 + rowTwo] = temp;

        temp = result[column * 4 + rowOne];
        result[column * 4 + rowOne] = result[column * 4 + rowTwo];
        result[column * 4 + rowTwo] = temp;
    }
}

static GLvoid Matrix4x4AddRow(double result[16], double matrix[16], GLint rowOne, GLint rowTwo, double factor)
{
    GLint column;

    for (column = 0; column < 4; column++)
    {
        matrix[column * 4 + rowOne] += matrix[column * 4 + rowTwo] * factor;
        result[column * 4 + rowOne] += result[column * 4 + rowTwo] * factor;
    }
}

//

GLvoid  Matrix4x4Identityf(GLfloat matrix[16])
{
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

GLvoid  Matrix3x3Identityf(GLfloat matrix[9])
{
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;

    matrix[3] = 0.0f;
    matrix[4] = 1.0f;
    matrix[5] = 0.0f;

    matrix[6] = 0.0f;
    matrix[7] = 0.0f;
    matrix[8] = 1.0f;
}

GLvoid  Matrix2x2Identityf(GLfloat matrix[4])
{
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;

    matrix[2] = 0.0f;
    matrix[3] = 1.0f;
}

GLvoid  Matrix4x4Initf(GLfloat matrix[16], const GLfloat column0[4], const GLfloat column1[4], const GLfloat column2[4], const GLfloat column3[4])
{
    matrix[0] = column0[0];
    matrix[1] = column0[1];
    matrix[2] = column0[2];
    matrix[3] = column0[3];

    matrix[4] = column1[0];
    matrix[5] = column1[1];
    matrix[6] = column1[2];
    matrix[7] = column1[3];

    matrix[8] = column2[0];
    matrix[9] = column2[1];
    matrix[10] = column2[2];
    matrix[11] = column2[3];

    matrix[12] = column3[0];
    matrix[13] = column3[1];
    matrix[14] = column3[2];
    matrix[15] = column3[3];
}

GLvoid  Matrix3x3Initf(GLfloat matrix[9], const GLfloat column0[3], const GLfloat column1[3], const GLfloat column2[3])
{
    matrix[0] = column0[0];
    matrix[1] = column0[1];
    matrix[2] = column0[2];

    matrix[3] = column1[0];
    matrix[4] = column1[1];
    matrix[5] = column1[2];

    matrix[6] = column2[0];
    matrix[7] = column2[1];
    matrix[8] = column2[2];
}

GLvoid  Matrix2x2Initf(GLfloat matrix[4], const GLfloat column0[2], const GLfloat column1[2])
{
    matrix[0] = column0[0];
    matrix[1] = column0[1];

    matrix[2] = column0[1];
    matrix[3] = column1[1];
}

GLvoid  Matrix4x4Copyf(GLfloat matrix[16], const GLfloat source[16], const GLboolean rotationOnly)
{
    GLint i;

    if (rotationOnly)
    {
        for (i = 0; i < 12; i++)
        {
            if ((i + 1) % 4 == 0)
            {
                continue;
            }

            matrix[i] = source[i];
        }

        matrix[3] = 0.0f;
        matrix[7] = 0.0f;
        matrix[11] = 0.0f;

        matrix[12] = 0.0f;
        matrix[13] = 0.0f;
        matrix[14] = 0.0f;
        matrix[15] = 1.0f;
    }
    else
    {
        for (i = 0; i < 16; i++)
        {
            matrix[i] = source[i];
        }
    }
}

GLvoid  Matrix3x3Copyf(GLfloat matrix[9], const GLfloat source[9], const GLboolean rotationOnly)
{
    GLint i;

    if (rotationOnly)
    {
		for (i = 0; i < 6; i++)
		{
			if ((i + 1) % 3 == 0)
			{
				continue;
			}

			matrix[i] = source[i];
		}

		matrix[2] = 0.0f;
		matrix[5] = 0.0f;

		matrix[6] = 0.0f;
		matrix[7] = 0.0f;
		matrix[8] = 1.0f;
	}
    else
    {
    	for (i = 0; i < 9; i++)
    	{
    		matrix[i] = source[i];
    	}
    }
}

GLvoid  Matrix2x2Copyf(GLfloat matrix[4], const GLfloat source[4])
{
    GLint i;

    for (i = 0; i < 4; i++)
    {
        matrix[i] = source[i];
    }
}

GLvoid  Matrix4x4ExtractMatrix3x3f(GLfloat matrix[9], const GLfloat source[16])
{
    matrix[0] = source[0];
    matrix[1] = source[1];
    matrix[2] = source[2];

    matrix[3] = source[4];
    matrix[4] = source[5];
    matrix[5] = source[6];

    matrix[6] = source[8];
    matrix[7] = source[9];
    matrix[8] = source[10];
}

GLvoid  Matrix4x4ExtractMatrix2x2f(GLfloat matrix[4], const GLfloat source[16])
{
    matrix[0] = source[0];
    matrix[1] = source[1];

    matrix[2] = source[4];
    matrix[3] = source[5];
}

GLvoid  Matrix3x3ExtractMatrix2x2f(GLfloat matrix[4], const GLfloat source[9])
{
    matrix[0] = source[0];
    matrix[1] = source[1];

    matrix[2] = source[3];
    matrix[3] = source[4];
}

GLvoid  Matrix3x3CreateMatrix4x4f(GLfloat matrix[16], const GLfloat source[9])
{
	matrix[0] = source[0];
	matrix[1] = source[1];
	matrix[2] = source[2];
	matrix[3] = 0.0f;

	matrix[4] = source[3];
	matrix[5] = source[4];
	matrix[6] = source[5];
	matrix[7] = 0.0f;

	matrix[8] = source[6];
	matrix[9] = source[7];
	matrix[10] = source[8];
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

GLvoid  Matrix2x2CreateMatrix4x4f(GLfloat matrix[16], const GLfloat source[4])
{
	matrix[0] = source[0];
	matrix[1] = source[1];
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = source[2];
	matrix[5] = source[3];
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

GLvoid  Matrix2x2CreateMatrix3x3f(GLfloat matrix[9], const GLfloat source[4])
{
	matrix[0] = source[0];
	matrix[1] = source[1];
	matrix[2] = 0.0f;

	matrix[3] = source[2];
	matrix[4] = source[3];
	matrix[5] = 0.0f;

	matrix[6] = 0.0f;
	matrix[7] = 0.0f;
	matrix[8] = 1.0f;
}

GLvoid  Matrix4x4Addf(GLfloat matrix[16], const GLfloat matrix0[16], const GLfloat matrix1[16])
{
    GLint i;

    for (i = 0; i < 16; i++)
    {
    	matrix[i] = matrix0[i] + matrix1[i];
    }
}

GLvoid  Matrix3x3Addf(GLfloat matrix[9], const GLfloat matrix0[9], const GLfloat matrix1[9])
{
    GLint i;

    for (i = 0; i < 9; i++)
    {
    	matrix[i] = matrix0[i] + matrix1[i];
    }
}

GLvoid  Matrix2x2Addf(GLfloat matrix[4], const GLfloat matrix0[4], const GLfloat matrix1[4])
{
    GLint i;

    for (i = 0; i < 4; i++)
    {
    	matrix[i] = matrix0[i] + matrix1[i];
    }
}

GLvoid  Matrix4x4Subtractf(GLfloat matrix[16], const GLfloat matrix0[16], const GLfloat matrix1[16])
{
    GLint i;

    for (i = 0; i < 16; i++)
    {
    	matrix[i] = matrix0[i] - matrix1[i];
    }
}

GLvoid  Matrix3x3Subtractf(GLfloat matrix[9], const GLfloat matrix0[9], const GLfloat matrix1[9])
{
    GLint i;

    for (i = 0; i < 9; i++)
    {
    	matrix[i] = matrix0[i] - matrix1[i];
    }
}

GLvoid  Matrix2x2Subtractf(GLfloat matrix[4], const GLfloat matrix0[4], const GLfloat matrix1[4])
{
    GLint i;

    for (i = 0; i < 4; i++)
    {
    	matrix[i] = matrix0[i] - matrix1[i];
    }
}

GLfloat  Matrix4x4Determinantf(const GLfloat matrix[16])
{
	GLint row, column, inner_row, inner_column, index;
	GLfloat det = 0.0f;
	GLfloat sign = 1.0f;
	GLfloat innerMatrix[9];

	column = 0;

	for (row = 0; row < 4; row++)
	{
		index = 0;

		for (inner_column = 0; inner_column < 4; inner_column++)
		{
			if (inner_column == column)
			{
				continue;
			}

			for (inner_row = 0; inner_row < 4; inner_row++)
			{
				if (inner_row == row)
				{
					continue;
				}

				innerMatrix[index] = matrix[inner_row + 4 * inner_column];

				index++;
			}
		}

		det += sign * matrix[row + 4 * column] * Matrix3x3Determinantf(innerMatrix);

		sign *= -1.0f;
	}

	return det;
}

GLfloat  Matrix3x3Determinantf(const GLfloat matrix[9])
{
	return matrix[0] * matrix[4] * matrix[8] + matrix[3] * matrix[7] * matrix[2] + matrix[6] * matrix[1] * matrix[5] - matrix[6] * matrix[4] * matrix[2] - matrix[3] * matrix[1] * matrix[8] - matrix[0] * matrix[7] * matrix[5];
}

GLfloat  Matrix2x2Determinantf(const GLfloat matrix[4])
{
	return matrix[0] * matrix[3]  - matrix[2] * matrix[1];
}

GLboolean  Matrix4x4Inversef(GLfloat matrix[16])
{
    GLint i;

    GLint column;
    GLint row;

    double matrix_as_double[16] = {1.0, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0, 0.0,  0.0, 0.0, 1.0, 0.0,  0.0, 0.0, 0.0, 1.0};
    double copy[16];

    //
    // Copy the original matrix as we want to manipulate it
    //
    for (i = 0; i < 16; i++)
    {
        copy[i] = (double)matrix[i];
    }

    //
    // Make triangle form
    //
    for (column = 0; column < 4; column++)
    {
        GLint row;

        for (row = column; row < 4; row++)
        {
        	//
            // Is row all zero, then return false
            //
            if (Matrix4x4IsRowZero(copy, row))
            {
                return GL_FALSE;
            }

            //
            // Divide, if not zero, by copy[column*4+row]
            //
            if (copy[column * 4 + row] != 0.0)
            {
                Matrix4x4DivideRowByScalar(matrix_as_double, copy, row, copy[column * 4 + row]);
            }
        }

        //
        // Is column all zero, then return false
        //
        if (Matrix4x4IsColumnZero(copy, column))
        {
            return GL_FALSE;
        }

        //
        // Is pivot [column*4+row] = 1.0
        //
        for (row = column + 1; row < 4; row++)
        {
            if (copy[column * 4 + row] == 1.0)
            {
                //
                // Swap with pivot row = column
                //
                Matrix4x4SwapRow(matrix_as_double, copy, column, row);

                break;
            }
        }

        for (row = column + 1; row < 4; row++)
        {
            //
            // Subtract, [column*4+row] not zero, current row minus pivot row = column
            //
            if (copy[column * 4 + row] != 0.0)
            {
                Matrix4x4AddRow(matrix_as_double, copy, row, column, -1.0);
            }
        }
    }

    //
    // Make diagonal form
    //
    for (column = 3; column >= 0; column--)
    {
        for (row = column - 1; row >= 0; row--)
        {
            //
            // Subtract, if [column*4+row] not zero, current row minus pivot row = column with factor [column*4+row]
            //
            if (copy[column * 4 + row] != 0.0)
            {
                Matrix4x4AddRow(matrix_as_double, copy, row, column, -copy[column * 4 + row]);
            }
        }
    }

    for (i = 0; i < 16; i++)
    {
        matrix[i] = (float)matrix_as_double[i];
    }

    return GL_TRUE;
}

GLboolean  Matrix3x3Inversef(GLfloat matrix[9])
{
    GLint i, j;
    GLint index[4];
    GLint counter;
    GLint column;
    GLint row;

    GLfloat det;
    GLfloat temp[9];
    GLfloat sign;

    det = matrix[0] * matrix[4] * matrix[8] + matrix[3] * matrix[7] * matrix[2] + matrix[6] * matrix[1] * matrix[5] - matrix[6] * matrix[4] * matrix[2] - matrix[3] * matrix[1] * matrix[8] - matrix[0] * matrix[7] * matrix[5];

    if (det == 0.0f)
    {
        return GL_FALSE;
    }

    Matrix3x3Copyf(temp, matrix, GL_FALSE);

    for (i = 0; i < 9; i++)
    {
        column = i / 3;
        row = i % 3;

        counter = 0;

        for (j = 0; j < 9; j++)
        {
            // Leave out column depending on given row and row depending on given column.
            if (j / 3 == row || j % 3 == column)
            {
                continue;
            }

            index[counter] = j;

            counter++;
        }

        sign = (column + row) % 2 == 0 ? 1.0f : -1.0f;

        matrix[i] = sign * (temp[index[0]] * temp[index[3]] - temp[index[2]] * temp[index[1]]) / det;
    }

    return GL_TRUE;
}

GLboolean  Matrix2x2Inversef(GLfloat matrix[4])
{
    GLfloat det;
    GLfloat temp[4];

    det = matrix[0] * matrix[3]  - matrix[2] * matrix[1];

    if (det == 0.0f)
    {
        return GL_FALSE;
    }

    Matrix2x2Copyf(temp, matrix);

    matrix[0] = temp[3] / det;
    matrix[1] = -temp[1] / det;
    matrix[2] = -temp[2] / det;
    matrix[3] = temp[0] / det;

    return GL_TRUE;
}


GLvoid  Matrix4x4InverseRigidBodyf(GLfloat matrix[16])
{
	GLfloat scales[3];
    GLfloat inverseScale[16];
    GLfloat inverseRotation[16];
    GLfloat inverseTranslation[16];

    Matrix4x4GetScalef(scales, matrix);
    Matrix4x4Identityf(inverseScale);
    // Square of it, as rotation still contains the scale
    inverseScale[0] = 1.0f / (scales[0] * scales[0]);
    inverseScale[5] = 1.0f / (scales[1] * scales[1]);
    inverseScale[10] = 1.0f / (scales[2] * scales[2]);

    Matrix4x4Copyf(inverseRotation, matrix, GL_TRUE);
    Matrix4x4Transposef(inverseRotation);

    Matrix4x4Identityf(inverseTranslation);
    inverseTranslation[12] = -matrix[12];
    inverseTranslation[13] = -matrix[13];
    inverseTranslation[14] = -matrix[14];

    Matrix4x4Multiplyf(matrix, inverseRotation, inverseTranslation);
    Matrix4x4Multiplyf(matrix, inverseScale, matrix);
}

GLvoid  Matrix3x3InverseRigidBodyf(GLfloat matrix[9], const GLboolean is2D)
{
	if (is2D)
	{
		GLfloat scales[3];
		GLfloat inverseScale[9];
		GLfloat inverseRotation[9];
		GLfloat inverseTranslation[9];

		Matrix3x3GetScalef(scales, matrix);
		Matrix3x3Identityf(inverseScale);
		// Square of it, as rotation still contains the scale
		inverseScale[0] = 1.0f / (scales[0] * scales[0]);
		inverseScale[4] = 1.0f / (scales[1] * scales[1]);
		// Last column is 2D translate

		Matrix3x3Copyf(inverseRotation, matrix, is2D);
		Matrix3x3Transposef(inverseRotation);

	    Matrix3x3Identityf(inverseTranslation);
	    inverseTranslation[6] = -matrix[6];
	    inverseTranslation[7] = -matrix[7];

	    Matrix3x3Multiplyf(matrix, inverseRotation, inverseTranslation);
	    Matrix3x3Multiplyf(matrix, inverseScale, matrix);
	}
	else
	{
		GLfloat scales[3];
		GLfloat inverseScale[9];
		GLfloat inverseRotation[9];

		Matrix3x3GetScalef(scales, matrix);
		Matrix3x3Identityf(inverseScale);
		// Square of it, as rotation still contains the scale
		inverseScale[0] = 1.0f / (scales[0] * scales[0]);
		inverseScale[4] = 1.0f / (scales[1] * scales[1]);
		inverseScale[8] = 1.0f / (scales[2] * scales[2]);

		Matrix3x3Copyf(inverseRotation, matrix, is2D);
		Matrix3x3Transposef(inverseRotation);

		Matrix3x3Multiplyf(matrix, inverseScale, inverseRotation);
	}
}

GLvoid  Matrix2x2InverseRigidBodyf(GLfloat matrix[4])
{
	GLfloat scales[2];
    GLfloat inverseScale[4];
    GLfloat inverseRotation[4];

    Matrix2x2GetScalef(scales, matrix);
    Matrix2x2Identityf(inverseScale);
    // Square of it, as rotation still contains the scale
    inverseScale[0] = 1.0f / (scales[0] * scales[0]);
    inverseScale[3] = 1.0f / (scales[1] * scales[1]);

    Matrix2x2Copyf(inverseRotation, matrix);
    Matrix2x2Transposef(inverseRotation);

    Matrix2x2Multiplyf(matrix, inverseScale, inverseRotation);
}

GLvoid  Matrix4x4Transposef(GLfloat matrix[16])
{
    GLint column;
    GLint row;

    GLfloat temp[16];

    Matrix4x4Copyf(temp, matrix, GL_FALSE);

    for (column = 0; column < 4; column++)
    {
        for (row = 0; row < 4; row++)
        {
            matrix[row * 4 + column] = temp[column * 4 + row];
        }
    }
}

GLvoid  Matrix3x3Transposef(GLfloat matrix[9])
{
    GLint column;
    GLint row;

    GLfloat temp[9];

    Matrix3x3Copyf(temp, matrix, GL_FALSE);

    for (column = 0; column < 3; column++)
    {
        for (row = 0; row < 3; row++)
        {
            matrix[row * 3 + column] = temp[column * 3 + row];
        }
    }
}

GLvoid  Matrix2x2Transposef(GLfloat matrix[4])
{
    GLint column;
    GLint row;

    GLfloat temp[4];

    Matrix2x2Copyf(temp, matrix);

    for (column = 0; column < 2; column++)
    {
        for (row = 0; row < 2; row++)
        {
            matrix[row * 2 + column] = temp[column * 2 + row];
        }
    }
}

GLvoid  Matrix4x4Translatef(GLfloat matrix[16], const GLfloat x, const GLfloat y, const GLfloat z)
{
    GLfloat temp[16];

    Matrix4x4Identityf(temp);

    temp[12] = x;
    temp[13] = y;
    temp[14] = z;

    Matrix4x4Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix3x3Translatef(GLfloat matrix[9], const GLfloat x, const GLfloat y)
{
    GLfloat temp[9];

    Matrix3x3Identityf(temp);

    temp[6] = x;
    temp[7] = y;

    Matrix3x3Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix4x4Rotatef(GLfloat matrix[16], const GLfloat angle, const GLfloat x, const GLfloat y, const GLfloat z)
{
    GLfloat temp[16];

    GLfloat s = sinf(2.0f * PI * angle / 360.0f);
    GLfloat c = cosf(2.0f * PI * angle / 360.0f);

    GLfloat vector[3] = { x, y, z };

    GLfloat xn, yn, zn;

    Vector3Normalizef(vector);

    xn = vector[0];
    yn = vector[1];
    zn = vector[2];

    Matrix4x4Identityf(temp);

    temp[0] = xn * xn * (1 - c) + c;
    temp[1] = xn * yn * (1 - c) + zn * s;
    temp[2] = xn * zn * (1 - c) - yn * s;

    temp[4] = xn * yn * (1 - c) - zn * s;
    temp[5] = yn * yn * (1 - c) + c;
    temp[6] = yn * zn * (1 - c) + xn * s;

    temp[8] = xn * zn * (1 - c) + yn * s;
    temp[9] = yn * zn * (1 - c) - xn * s;
    temp[10] = zn * zn * (1 - c) + c;

    Matrix4x4Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix3x3Rotatef(GLfloat matrix[9], const GLfloat angle, const GLfloat x, const GLfloat y, const GLfloat z)
{
    GLfloat temp[9];

    GLfloat s = sinf(2.0f * PI * angle / 360.0f);
    GLfloat c = cosf(2.0f * PI * angle / 360.0f);

    GLfloat vector[3] = { x, y, z };

    GLfloat xn, yn, zn;

    Vector3Normalizef(vector);

    xn = vector[0];
    yn = vector[1];
    zn = vector[2];

    Matrix3x3Identityf(temp);

    temp[0] = xn * xn * (1 - c) + c;
    temp[1] = xn * yn * (1 - c) + zn * s;
    temp[2] = xn * zn * (1 - c) - yn * s;

    temp[3] = xn * yn * (1 - c) - zn * s;
    temp[4] = yn * yn * (1 - c) + c;
    temp[5] = yn * zn * (1 - c) + xn * s;

    temp[6] = xn * zn * (1 - c) + yn * s;
    temp[7] = yn * zn * (1 - c) - xn * s;
    temp[8] = zn * zn * (1 - c) + c;

    Matrix3x3Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix2x2Rotatef(GLfloat matrix[4], const GLfloat angle)
{
    GLfloat temp[4];

    GLfloat s = sinf(2.0f * PI * angle / 360.0f);
    GLfloat c = cosf(2.0f * PI * angle / 360.0f);

    Matrix2x2Identityf(temp);

    temp[0] = c;
    temp[1] = s;

    temp[2] = -s;
    temp[3] = c;

    Matrix2x2Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix4x4RotateRxf(GLfloat matrix[16], const GLfloat angle)
{
    GLfloat temp[16];

    GLfloat s = sinf(2.0f * PI * angle / 360.0f);
    GLfloat c = cosf(2.0f * PI * angle / 360.0f);

    Matrix4x4Identityf(temp);

    temp[5] = c;
    temp[6] = s;

    temp[9] = -s;
    temp[10] = c;

    Matrix4x4Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix3x3RotateRxf(GLfloat matrix[9], const GLfloat angle)
{
    GLfloat temp[9];

    GLfloat s = sinf(2.0f * PI * angle / 360.0f);
    GLfloat c = cosf(2.0f * PI * angle / 360.0f);

    Matrix3x3Identityf(temp);

    temp[4] = c;
    temp[5] = s;

    temp[7] = -s;
    temp[8] = c;

    Matrix3x3Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix4x4RotateRyf(GLfloat matrix[16], const GLfloat angle)
{
    GLfloat temp[16];

    GLfloat s = sinf(2.0f * PI * angle / 360.0f);
    GLfloat c = cosf(2.0f * PI * angle / 360.0f);

    Matrix4x4Identityf(temp);

    temp[0] = c;
    temp[2] = -s;

    temp[8] = s;
    temp[10] = c;

    Matrix4x4Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix3x3RotateRyf(GLfloat matrix[9], const GLfloat angle)
{
    GLfloat temp[9];

    GLfloat s = sinf(2.0f * PI * angle / 360.0f);
    GLfloat c = cosf(2.0f * PI * angle / 360.0f);

    Matrix3x3Identityf(temp);

    temp[0] = c;
    temp[2] = -s;

    temp[6] = s;
    temp[8] = c;

    Matrix3x3Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix4x4RotateRzf(GLfloat matrix[16], const GLfloat angle)
{
    GLfloat temp[16];

    GLfloat s = sinf(2.0f * PI * angle / 360.0f);
    GLfloat c = cosf(2.0f * PI * angle / 360.0f);

    Matrix4x4Identityf(temp);

    temp[0] = c;
    temp[1] = s;

    temp[4] = -s;
    temp[5] = c;

    Matrix4x4Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix3x3RotateRzf(GLfloat matrix[9], const GLfloat angle)
{
    GLfloat temp[9];

    GLfloat s = sinf(2.0f * PI * angle / 360.0f);
    GLfloat c = cosf(2.0f * PI * angle / 360.0f);

    Matrix3x3Identityf(temp);

    temp[0] = c;
    temp[1] = s;

    temp[3] = -s;
    temp[4] = c;

    Matrix3x3Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix4x4RotateRzRxRyf(GLfloat matrix[16], const GLfloat anglez, const GLfloat anglex, const GLfloat angley)
{
    GLfloat temp[16];

    GLfloat rz = 2.0f * PI * anglez / 360.0f;
    GLfloat rx = 2.0f * PI * anglex / 360.0f;
    GLfloat ry = 2.0f * PI * angley / 360.0f;
    GLfloat sy = sinf(ry);
    GLfloat cy = cosf(ry);
    GLfloat sx = sinf(rx);
    GLfloat cx = cosf(rx);
    GLfloat sz = sinf(rz);
    GLfloat cz = cosf(rz);

    Matrix4x4Identityf(temp);

    temp[0] = cy * cz - sx * sy * sz;
    temp[1] = cz * sx * sy + cy * sz;
    temp[2] = -cx * sy;

    temp[4] = -cx * sz;
    temp[5] = cx * cz;
    temp[6] = sx;

    temp[8] = cz * sy + cy * sx * sz;
    temp[9] = -cy * cz * sx + sy * sz;
    temp[10] = cx * cy;

    Matrix4x4Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix4x4RotateRzRyRxf(GLfloat matrix[16], const GLfloat anglez, const GLfloat angley, const GLfloat anglex)
{
    GLfloat temp[16];

    GLfloat rz = 2.0f * PI * anglez / 360.0f;
    GLfloat ry = 2.0f * PI * angley / 360.0f;
    GLfloat rx = 2.0f * PI * anglex / 360.0f;
    GLfloat sx = sinf(rx);
    GLfloat cx = cosf(rx);
    GLfloat sy = sinf(ry);
    GLfloat cy = cosf(ry);
    GLfloat sz = sinf(rz);
    GLfloat cz = cosf(rz);

    Matrix4x4Identityf(temp);

    temp[0] = cy * cz;
    temp[1] = cy * sz;
    temp[2] = -sy;

    temp[4] = -cx * sz + cz * sx * sy;
    temp[5] = cx * cz + sx * sy * sz;
    temp[6] = cy * sx;

    temp[8] = sz * sx + cx * cz * sy;
    temp[9] = -cz * sx + cx * sy * sz;
    temp[10] = cx * cy;

    Matrix4x4Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix3x3RotateRzRxRyf(GLfloat matrix[9], const GLfloat anglez, const GLfloat anglex, const GLfloat angley)
{
    GLfloat temp[9];

    GLfloat rz = 2.0f * PI * anglez / 360.0f;
    GLfloat rx = 2.0f * PI * anglex / 360.0f;
    GLfloat ry = 2.0f * PI * angley / 360.0f;
    GLfloat sy = sinf(ry);
    GLfloat cy = cosf(ry);
    GLfloat sx = sinf(rx);
    GLfloat cx = cosf(rx);
    GLfloat sz = sinf(rz);
    GLfloat cz = cosf(rz);

    Matrix3x3Identityf(temp);

    temp[0] = cy * cz - sx * sy * sz;
    temp[1] = cz * sx * sy + cy * sz;
    temp[2] = -cx * sy;

    temp[3] = -cx * sz;
    temp[4] = cx * cz;
    temp[5] = sx;

    temp[6] = cz * sy + cy * sx * sz;
    temp[7] = -cy * cz * sx + sy * sz;
    temp[8] = cx * cy;

    Matrix3x3Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix3x3RotateRzRyRxf(GLfloat matrix[9], const GLfloat anglez, const GLfloat angley, const GLfloat anglex)
{
    GLfloat temp[9];

    GLfloat rz = 2.0f * PI * anglez / 360.0f;
    GLfloat ry = 2.0f * PI * angley / 360.0f;
    GLfloat rx = 2.0f * PI * anglex / 360.0f;
    GLfloat sx = sinf(rx);
    GLfloat cx = cosf(rx);
    GLfloat sy = sinf(ry);
    GLfloat cy = cosf(ry);
    GLfloat sz = sinf(rz);
    GLfloat cz = cosf(rz);

    Matrix3x3Identityf(temp);

    temp[0] = cy * cz;
    temp[1] = cy * sz;
    temp[2] = -sy;

    temp[3] = -cx * sz + cz * sx * sy;
    temp[4] = cx * cz + sx * sy * sz;
    temp[5] = cy * sx;

    temp[6] = sz * sx + cx * cz * sy;
    temp[7] = -cz * sx + cx * sy * sz;
    temp[8] = cx * cy;

    Matrix3x3Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix4x4Scalef(GLfloat matrix[16], const GLfloat x, const GLfloat y, const GLfloat z)
{
    GLfloat temp[16];

    Matrix4x4Identityf(temp);

    temp[0] = x;
    temp[5] = y;
    temp[10] = z;

    Matrix4x4Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix3x3Scalef(GLfloat matrix[9], const GLfloat x, const GLfloat y, const GLfloat z)
{
    GLfloat temp[9];

    Matrix3x3Identityf(temp);

    temp[0] = x;
    temp[4] = y;
    temp[8] = z;

    Matrix3x3Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix2x2Scalef(GLfloat matrix[4], const GLfloat x, const GLfloat y)
{
    GLfloat temp[4];

    Matrix2x2Identityf(temp);

    temp[0] = x;
    temp[3] = y;

    Matrix2x2Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix4x4Shearf(GLfloat matrix[16], const GLfloat shxy, const GLfloat shxz, const GLfloat shyx, const GLfloat shyz, const GLfloat shzx, const GLfloat shzy)
{
    GLfloat temp[16];

    Matrix4x4Identityf(temp);

    temp[4] = shxy;
    temp[8] = shxz;

    temp[1] = shyx;
    temp[9] = shyz;

    temp[2] = shzx;
    temp[6] = shzy;

    Matrix4x4Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix3x3Shearf(GLfloat matrix[9], const GLfloat shxy, const GLfloat shxz, const GLfloat shyx, const GLfloat shyz, const GLfloat shzx, const GLfloat shzy)
{
    GLfloat temp[9];

    Matrix3x3Identityf(temp);

    temp[3] = shxy;
    temp[6] = shxz;

    temp[1] = shyx;
    temp[7] = shyz;

    temp[2] = shzx;
    temp[5] = shzy;

    Matrix3x3Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix2x2Shearf(GLfloat matrix[4], const GLfloat shx, const GLfloat shy)
{
    GLfloat temp[4];

    Matrix2x2Identityf(temp);

    temp[2] = shx;

    temp[1] = shy;

    Matrix2x2Multiplyf(matrix, matrix, temp);
}

GLvoid  Matrix4x4MultiplyVector3f(GLfloat result[3], const GLfloat matrix[16], const GLfloat vector[3])
{
    GLint i;

    GLfloat temp[3];

    for (i = 0; i < 3; i++)
    {
        temp[i] = matrix[i] * vector[0] + matrix[4 + i] * vector[1] + matrix[8 + i] * vector[2];
    }

    for (i = 0; i < 3; i++)
    {
        result[i] = temp[i];
    }
}

GLvoid  Matrix4x4MultiplyVector2f(GLfloat result[2], const GLfloat matrix[16], const GLfloat vector[2])
{
    GLint i;

    GLfloat temp[2];

    for (i = 0; i < 2; i++)
    {
        temp[i] = matrix[i] * vector[0] + matrix[4 + i] * vector[1];
    }

    for (i = 0; i < 2; i++)
    {
        result[i] = temp[i];
    }
}

GLvoid  Matrix3x3MultiplyVector3f(GLfloat result[3], const GLfloat matrix[9], const GLfloat vector[3])
{
    GLint i;

    GLfloat temp[3];

    for (i = 0; i < 3; i++)
    {
        temp[i] = matrix[i] * vector[0] + matrix[3 + i] * vector[1] + matrix[6 + i] * vector[2];
    }

    for (i = 0; i < 3; i++)
    {
        result[i] = temp[i];
    }
}

GLvoid  Matrix3x3MultiplyVector2f(GLfloat result[2], const GLfloat matrix[9], const GLfloat vector[2])
{
    GLint i;

    GLfloat temp[2];

    for (i = 0; i < 2; i++)
    {
        temp[i] = matrix[i] * vector[0] + matrix[3 + i] * vector[1];
    }

    for (i = 0; i < 2; i++)
    {
        result[i] = temp[i];
    }
}

GLvoid  Matrix2x2MultiplyVector2f(GLfloat result[2], const GLfloat matrix[4], const GLfloat vector[2])
{
    GLint i;

    GLfloat temp[2];

    for (i = 0; i < 2; i++)
    {
        temp[i] = matrix[i] * vector[0] + matrix[2 + i] * vector[1];
    }

    for (i = 0; i < 2; i++)
    {
        result[i] = temp[i];
    }
}

GLvoid  Matrix4x4MultiplyPoint4f(GLfloat result[4], const GLfloat matrix[16], const GLfloat point[4])
{
    GLint i;

    GLfloat temp[4];

    for (i = 0; i < 4; i++)
    {
        temp[i] = matrix[i] * point[0] + matrix[4 + i] * point[1] + matrix[8 + i] * point[2] + matrix[12 + i] * point[3];
    }

    for (i = 0; i < 4; i++)
    {
        result[i] = temp[i];
    }

    if (result[3] != 0.0f && result[3] != 1.0f)
    {
        for (i = 0; i < 4; i++)
        {
            result[i] /= temp[3];
        }
    }
}

GLvoid  Matrix3x3MultiplyPoint3f(GLfloat result[3], const GLfloat matrix[9], const GLfloat point[3])
{
    GLint i;

    GLfloat temp[3];

    for (i = 0; i < 3; i++)
    {
        temp[i] = matrix[i] * point[0] + matrix[3 + i] * point[1] + matrix[6 + i] * point[2];
    }

    for (i = 0; i < 3; i++)
    {
        result[i] = temp[i];
    }

    if (result[2] != 0.0f && result[2] != 1.0f)
    {
        for (i = 0; i < 3; i++)
        {
            result[i] /= temp[2];
        }
    }
}

GLvoid  Matrix4x4MultiplyPlanef(GLfloat result[4], const GLfloat matrix[16], const GLfloat plane[4])
{
    GLint i;

    GLfloat temp[4];

    for (i = 0; i < 4; i++)
    {
        temp[i] = matrix[i] * plane[0] + matrix[4 + i] * plane[1] + matrix[8 + i] * plane[2] + matrix[12 + i] * plane[3];
    }

    for (i = 0; i < 4; i++)
    {
        result[i] = temp[i];
    }
}

GLboolean  Matrix4x4GetEulerRzRxRyf(GLfloat angles[3], const GLfloat matrix[16])
{
	GLfloat scales[3];

	Matrix4x4GetScalef(scales, matrix);

	if (scales[0] == 0.0f || scales[1] == 0.0f || scales[2] == 0.0f)
	{
		return GL_FALSE;
	}

    if (!(matrix[2] == 0.0f && matrix[10] == 0.0f) && !(matrix[4] == 0.0f && matrix[5] == 0.0f))
    {
        angles[0] = MathRadToDegf(asinf(matrix[6] / scales[1]));
        angles[1] = MathRadToDegf(atan2f(-matrix[2] / scales[0], matrix[10] / scales[2]));
        angles[2] = MathRadToDegf(atan2f(-matrix[4] / scales[1], matrix[5] / scales[1]));
    }
    else if (!(matrix[1] == 0.0f && matrix[0] == 0.0f))
    {
        angles[0] = MathRadToDegf(asinf(matrix[6] / scales[1]));
        angles[1] = 0.0f;
        angles[2] = MathRadToDegf(atan2f(matrix[1] / scales[0], matrix[0] / scales[0]));
    }
    else
    {
    	return GL_FALSE;
    }

	return GL_TRUE;
}

GLboolean  Matrix4x4GetEulerRzRyRxf(GLfloat angles[3], const GLfloat matrix[16])
{
	GLfloat scales[3];

	Matrix4x4GetScalef(scales, matrix);

	if (scales[0] == 0.0f || scales[1] == 0.0f || scales[2] == 0.0f)
	{
		return GL_FALSE;
	}

	if (!(matrix[6] == 0.0f && matrix[10] == 0.0f) && !(matrix[1] == 0.0f && matrix[0] == 0.0f))
    {
        angles[0] = MathRadToDegf(atan2f(matrix[6] / scales[1], matrix[10] / scales[2]));
    	angles[1] = MathRadToDegf(asinf(-matrix[2] / scales[0]));
    	angles[2] = MathRadToDegf(atan2f(matrix[1] / scales[0], matrix[0] / scales[0]));
    }
    else if (!(matrix[4] == 0.0f && matrix[5] == 0.0f))
    {
        angles[0] = MathRadToDegf(atan2f(matrix[4] / scales[1], matrix[5] / scales[1]));
    	angles[1] = MathRadToDegf(asinf(-matrix[2]) / scales[0]);
    	angles[2] = 0.0f;
    }
    else
    {
    	return GL_FALSE;
    }

	return GL_TRUE;
}
	  

GLboolean  Matrix3x3GetEulerRzRxRyf(GLfloat angles[3], const GLfloat matrix[9])
{
	GLfloat scales[3];

	Matrix3x3GetScalef(scales, matrix);

	if (scales[0] == 0.0f || scales[1] == 0.0f || scales[2] == 0.0f)
	{
		return GL_FALSE;
	}

	if (!(matrix[2] == 0.0f && matrix[8] == 0.0f) && !(matrix[3] == 0.0f && matrix[4] == 0.0f))
    {
        angles[0] = MathRadToDegf(asinf(matrix[5] / scales[1]));
        angles[1] = MathRadToDegf(atan2f(-matrix[2] / scales[0], matrix[8] / scales[2]));
        angles[2] = MathRadToDegf(atan2f(-matrix[3] / scales[1], matrix[4] / scales[1]));
    }
    else if (!(matrix[1] == 0.0f && matrix[0] == 0.0f))
    {
        angles[0] = MathRadToDegf(asinf(matrix[5] / scales[1]));
        angles[1] = 0.0f;
        angles[2] = MathRadToDegf(atan2f(matrix[1] / scales[0], matrix[0] / scales[0]));
    }
    else
    {
    	return GL_FALSE;
    }

	return GL_TRUE;
}

GLboolean  Matrix3x3GetEulerRzRyRxf(GLfloat angles[3], const GLfloat matrix[9])
{
	GLfloat scales[3];

	Matrix3x3GetScalef(scales, matrix);

	if (scales[0] == 0.0f || scales[1] == 0.0f || scales[2] == 0.0f)
	{
		return GL_FALSE;
	}

	if (!(matrix[5] == 0.0f && matrix[8] == 0.0f) && !(matrix[1] == 0.0f && matrix[0] == 0.0f))
    {
        angles[0] = MathRadToDegf(atan2f(matrix[5] / scales[1], matrix[8] / scales[2]));
    	angles[1] = MathRadToDegf(asinf(-matrix[2] / scales[0]));
    	angles[2] = MathRadToDegf(atan2f(matrix[1] / scales[0], matrix[0] / scales[0]));
    }
    else if (!(matrix[3] == 0.0f && matrix[4] == 0.0f))
    {
        angles[0] = MathRadToDegf(atan2f(matrix[3] / scales[1], matrix[4] / scales[1]));
    	angles[1] = MathRadToDegf(asinf(-matrix[2] / scales[0]));
    	angles[2] = 0.0f;
    }
    else
    {
    	return GL_FALSE;
    }

	return GL_TRUE;
}

GLboolean  Matrix3x3GetAnglef(GLfloat* angle, const GLfloat matrix[9])
{
	GLfloat scales[3];

	Matrix3x3GetScalef(scales, matrix);

	if (scales[0] == 0.0f)
	{
		return GL_FALSE;
	}

	*angle = MathRadToDegf(acosf(matrix[0] / scales[0]));

	return GL_TRUE;
}

GLboolean  Matrix2x2GetAnglef(GLfloat* angle, const GLfloat matrix[4])
{
	GLfloat scales[2];

	Matrix2x2GetScalef(scales, matrix);

	if (scales[0] == 0.0f)
	{
		return GL_FALSE;
	}

	*angle = MathRadToDegf(acosf(matrix[0] / scales[0]));

	return GL_TRUE;
}

GLvoid  Matrix4x4GetScalef(GLfloat scales[3], const GLfloat matrix[16])
{
	GLint i;

	for (i = 0; i < 3; i++)
	{
		scales[i] = sqrtf(matrix[4*i] * matrix[4*i] + matrix[4*i+1] * matrix[4*i+1] + matrix[4*i+2] * matrix[4*i+2]);
	}
}

GLvoid  Matrix3x3GetScalef(GLfloat scales[3], const GLfloat matrix[9])
{
	GLint i;

	for (i = 0; i < 3; i++)
	{
		scales[i] = sqrtf(matrix[3*i] * matrix[3*i] + matrix[3*i+1] * matrix[3*i+1] + matrix[3*i+2] * matrix[3*i+2]);
	}
}

GLvoid  Matrix2x2GetScalef(GLfloat scales[2], const GLfloat matrix[4])
{
	GLint i;

	for (i = 0; i < 2; i++)
	{
		scales[i] = sqrtf(matrix[2*i] * matrix[2*i] + matrix[2*i+1] * matrix[2*i+1]);
	}
}

GLvoid  Matrix4x4GetTranslatef(GLfloat translates[3], const GLfloat matrix[16])
{
	translates[0] = matrix[12];
	translates[1] = matrix[13];
	translates[2] = matrix[14];
}

GLvoid  Matrix3x3GetTranslatef(GLfloat translates[2], const GLfloat matrix[9])
{
	translates[0] = matrix[6];
	translates[1] = matrix[7];
}

//

GLboolean  MatrixNxNMultiplyVectorNc(Complex* result, const Complex* matrix, const Complex* vector, const GLint n)
{
	GLint row, column;

	Complex* temp = (Complex*)MemoryMalloc(n * sizeof(Complex));

	Complex muliplication;

	if (!temp)
	{
		return GL_FALSE;
	}

	for (row = 0; row < n; row++)
	{
		for (column = 0; column < n; column++)
		{
			if (column == 0)
			{
				temp[row].real = 0.0f;
				temp[row].imaginary = 0.0f;
			}

			//////////////////////////////		ComplexMultiplyComplexc(&muliplication, &matrix[column * n + row], &vector[column]);
			//////////////////////////////		ComplexAddComplexc(&temp[row], &temp[row], &muliplication);
		}
	}

	for (row = 0; row < n; row++)
	{
		result[row] = temp[row];
	}

	MemoryFree(temp);

	return GL_TRUE;
}

GLvoid Matrix4x4Multiplyf(GLfloat matrix[16], const GLfloat matrix0[16], const GLfloat matrix1[16])
{
	{
		GLint i;

		GLfloat temp[16];

		GLint row;
		GLint column;
		for (column = 0; column < 4; column++)
		{
			for (row = 0; row < 4; row++)
			{
				temp[column * 4 + row] = 0.0f;

				for (i = 0; i < 4; i++)
				{
					temp[column * 4 + row] += matrix0[i * 4 + row] * matrix1[column * 4 + i];
				}
			}
		}

		for (i = 0; i < 16; i++)
		{
			matrix[i] = temp[i];
		}
	}
}

GLvoid Matrix2x2Multiplyf(GLfloat matrix[4], const GLfloat matrix0[4], const GLfloat matrix1[4])
{
	GLint i;

	GLfloat temp[16];

	GLint row;
	GLint column;
	for (column = 0; column < 2; column++)
	{
		for (row = 0; row < 2; row++)
		{
			temp[column * 2 + row] = 0.0f;

			for (i = 0; i < 2; i++)
			{
				temp[column * 2 + row] += matrix0[i * 2 + row] * matrix1[column * 2 + i];
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		matrix[i] = temp[i];
	}
}

GLvoid Matrix3x3Multiplyf(GLfloat matrix[9], const GLfloat matrix0[9], const GLfloat matrix1[9])
{
	GLint i;

	GLfloat temp[16];

	GLint row;
	GLint column;
	for (column = 0; column < 3; column++)
	{
		for (row = 0; row < 3; row++)
		{
			temp[column * 3 + row] = 0.0f;

			for (i = 0; i < 3; i++)
			{
				temp[column * 3 + row] += matrix0[i * 3 + row] * matrix1[column * 3 + i];
			}
		}
	}

	for (i = 0; i < 9; i++)
	{
		matrix[i] = temp[i];
	}
}