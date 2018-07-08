#include "stdafx.h"
#include "Shape.h"
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Point.h"

using namespace Utility;

static GLvoid ShapeInitf(Shape* shape)
{
    if (!shape)
    {
        return;
    }

    memset(shape, 0, sizeof(Shape));

    shape->mode = GL_TRIANGLES;
}

static GLboolean ShapeCheckf(Shape* shape)
{
    if (!shape)
    {
        return GL_FALSE;
    }

    return shape->vertices && shape->normals && shape->tangents && shape->texCoords && shape->indices;
}

static GLboolean ShapeFinalizef(Shape* shape)
{
    GLuint i;

    // vertex, normal, tangent, bitangent, texCoords
    GLuint stride = 4 + 3 + 3 + 3 + 2;

    if (!shape)
    {
        return GL_FALSE;
    }

    // Add bitangents
    shape->bitangents = (GLfloat*) MemoryMalloc(3 * shape->numberVertices * sizeof(GLfloat));

    if (!shape->bitangents)
    {
        return GL_FALSE;
    }

    for (i = 0; i < shape->numberVertices; i++)
    {
        Vector3Crossf(&(shape->bitangents[i * 3]), &(shape->normals[i * 3]), &(shape->tangents[i * 3]));
    }

    //

    shape->allAttributes = (GLfloat*) MemoryMalloc(stride * shape->numberVertices * sizeof(GLfloat));

    if (!shape->allAttributes)
    {
        return GL_FALSE;
    }

    for (i = 0; i < shape->numberVertices; i++)
    {
        shape->allAttributes[i * stride + 0] = shape->vertices[i * 4 + 0];
        shape->allAttributes[i * stride + 1] = shape->vertices[i * 4 + 1];
        shape->allAttributes[i * stride + 2] = shape->vertices[i * 4 + 2];
        shape->allAttributes[i * stride + 3] = shape->vertices[i * 4 + 3];

        shape->allAttributes[i * stride + 4] = shape->normals[i * 3 + 0];
        shape->allAttributes[i * stride + 5] = shape->normals[i * 3 + 1];
        shape->allAttributes[i * stride + 6] = shape->normals[i * 3 + 2];

        shape->allAttributes[i * stride + 7] = shape->tangents[i * 3 + 0];
        shape->allAttributes[i * stride + 8] = shape->tangents[i * 3 + 1];
        shape->allAttributes[i * stride + 9] = shape->tangents[i * 3 + 2];

        shape->allAttributes[i * stride + 10] = shape->bitangents[i * 3 + 0];
        shape->allAttributes[i * stride + 11] = shape->bitangents[i * 3 + 1];
        shape->allAttributes[i * stride + 12] = shape->bitangents[i * 3 + 2];

        shape->allAttributes[i * stride + 13] = shape->texCoords[i * 2 + 0];
        shape->allAttributes[i * stride + 14] = shape->texCoords[i * 2 + 1];
    }

    return GL_TRUE;
}


GLboolean  ShapeCreatePlanef(Shape* shape, const GLfloat halfExtend)
{
    GLuint i;

    GLuint numberVertices = 4;
    GLuint numberIndices = 6;

    GLfloat xy_vertices[] = { -1.0f, -1.0f, 0.0f, +1.0f, +1.0f, -1.0f, 0.0f, +1.0f, -1.0f, +1.0f, 0.0f, +1.0f, +1.0f, +1.0f, 0.0f, +1.0f };

    GLfloat xy_normals[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };

    GLfloat xy_tangents[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };

    GLfloat xy_texCoords[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };

    GLuint xy_indices[] = { 0, 1, 2, 1, 3, 2 };

    if (!shape)
    {
        return GL_FALSE;
    }
    ShapeInitf(shape);

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLfloat*) MemoryMalloc(4 * numberVertices * sizeof(GLfloat));
    shape->normals = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->tangents = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->texCoords = (GLfloat*) MemoryMalloc(2 * numberVertices * sizeof(GLfloat));
    shape->indices = (GLuint*) MemoryMalloc(numberIndices * sizeof(GLuint));

    if (!ShapeCheckf(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    memcpy(shape->vertices, xy_vertices, sizeof(xy_vertices));
    for (i = 0; i < numberVertices; i++)
    {
        shape->vertices[i * 4 + 0] *= halfExtend;
        shape->vertices[i * 4 + 1] *= halfExtend;
    }

    memcpy(shape->normals, xy_normals, sizeof(xy_normals));

    memcpy(shape->tangents, xy_tangents, sizeof(xy_tangents));

    memcpy(shape->texCoords, xy_texCoords, sizeof(xy_texCoords));

    memcpy(shape->indices, xy_indices, sizeof(xy_indices));

    if (!ShapeFinalizef(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean  ShapeCreateRectangularPlanef(Shape* shape, const GLfloat horizontalExtend, const GLfloat verticalExtend)
{
    GLuint i;

    GLuint numberVertices = 4;
    GLuint numberIndices = 6;

    GLfloat xy_vertices[] = { -1.0f, -1.0f, 0.0f, +1.0f, +1.0f, -1.0f, 0.0f, +1.0f, -1.0f, +1.0f, 0.0f, +1.0f, +1.0f, +1.0f, 0.0f, +1.0f };

    GLfloat xy_normals[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };

    GLfloat xy_tangents[] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };

    GLfloat xy_texCoords[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };

    GLuint xy_indices[] = { 0, 1, 2, 1, 3, 2 };

    if (!shape)
    {
        return GL_FALSE;
    }
    ShapeInitf(shape);

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLfloat*) MemoryMalloc(4 * numberVertices * sizeof(GLfloat));
    shape->normals = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->tangents = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->texCoords = (GLfloat*) MemoryMalloc(2 * numberVertices * sizeof(GLfloat));
    shape->indices = (GLuint*) MemoryMalloc(numberIndices * sizeof(GLuint));

    if (!ShapeCheckf(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    memcpy(shape->vertices, xy_vertices, sizeof(xy_vertices));
    for (i = 0; i < numberVertices; i++)
    {
        shape->vertices[i * 4 + 0] *= horizontalExtend;
        shape->vertices[i * 4 + 1] *= verticalExtend;
    }

    memcpy(shape->normals, xy_normals, sizeof(xy_normals));

    memcpy(shape->tangents, xy_tangents, sizeof(xy_tangents));

    memcpy(shape->texCoords, xy_texCoords, sizeof(xy_texCoords));

    memcpy(shape->indices, xy_indices, sizeof(xy_indices));

    if (!ShapeFinalizef(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean  ShapeCreateRectangularGridPlanef(Shape* shape, const GLfloat horizontalExtend, const GLfloat verticalExtend, const GLuint rows, const GLuint columns, const GLboolean triangleStrip)
{
    GLuint i, currentRow, currentColumn;

    GLuint numberVertices = (rows + 1) * (columns + 1);
    GLuint numberIndices;

    GLfloat x, y, s, t;

    if (triangleStrip)
    {
    	numberIndices = rows * 2 * (columns + 1);
    }
    else
    {
    	numberIndices = rows * 6 * columns;
    }

    if (rows < 1 || columns < 1 || numberVertices > GLUS_MAX_VERTICES || numberIndices > GLUS_MAX_INDICES)
    {
        return GL_FALSE;
    }

    if (!shape)
    {
        return GL_FALSE;
    }
    ShapeInitf(shape);

    if (triangleStrip)
    {
        shape->mode = GL_TRIANGLE_STRIP;
    }
    else
    {
        shape->mode = GL_TRIANGLES;
    }

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLfloat*) MemoryMalloc(4 * numberVertices * sizeof(GLfloat));
    shape->normals = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->tangents = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->texCoords = (GLfloat*) MemoryMalloc(2 * numberVertices * sizeof(GLfloat));
    shape->indices = (GLuint*) MemoryMalloc(numberIndices * sizeof(GLuint));

    if (!ShapeCheckf(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    for (i = 0; i < numberVertices; i++)
    {
        x = (GLfloat) (i % (columns + 1)) / (GLfloat) columns;
        y = 1.0f - (GLfloat) (i / (columns + 1)) / (GLfloat) rows;

        s = x;
        t = y;

        shape->vertices[i * 4 + 0] = horizontalExtend * (x - 0.5f);
        shape->vertices[i * 4 + 1] = verticalExtend * (y - 0.5f);
        shape->vertices[i * 4 + 2] = 0.0f;
        shape->vertices[i * 4 + 3] = 1.0f;

        shape->normals[i * 3 + 0] = 0.0f;
        shape->normals[i * 3 + 1] = 0.0f;
        shape->normals[i * 3 + 2] = 1.0f;

        shape->tangents[i * 3 + 0] = 1.0f;
        shape->tangents[i * 3 + 1] = 0.0f;
        shape->tangents[i * 3 + 2] = 0.0f;

        shape->texCoords[i * 2 + 0] = s;
        shape->texCoords[i * 2 + 1] = t;
    }

    if (triangleStrip)
    {
		for (i = 0; i < rows * (columns + 1); i++)
		{
			currentColumn = i % (columns + 1);
			currentRow = i / (columns + 1);

			if (currentRow == 0)
			{
				// Left to right, top to bottom
				shape->indices[i * 2] = currentColumn + currentRow * (columns + 1);
				shape->indices[i * 2 + 1] = currentColumn + (currentRow + 1) * (columns + 1);
			}
			else
			{
				// Right to left, bottom to up
				shape->indices[i * 2] = (columns - currentColumn) + (currentRow + 1) * (columns + 1);
				shape->indices[i * 2 + 1] = (columns - currentColumn) + currentRow * (columns + 1);
			}
		}
    }
    else
    {
    	for (i = 0; i < rows * columns; i++)
    	{
			currentColumn = i % columns;
			currentRow = i / columns;

			shape->indices[i * 6 + 0] = currentColumn + currentRow * (columns + 1);
    	    shape->indices[i * 6 + 1] = currentColumn + (currentRow + 1) * (columns + 1);
    	    shape->indices[i * 6 + 2] = (currentColumn + 1) + (currentRow + 1) * (columns + 1);

    	    shape->indices[i * 6 + 3] = (currentColumn + 1) + (currentRow + 1) * (columns + 1);
    	    shape->indices[i * 6 + 4] = (currentColumn + 1) + currentRow * (columns + 1);
    	    shape->indices[i * 6 + 5] = currentColumn + currentRow * (columns + 1);
    	}
    }

    if (!ShapeFinalizef(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean  ShapeCreateDiscf(Shape* shape, const GLfloat radius, const GLuint numberSectors)
{
    GLuint i;

    GLuint numberVertices = numberSectors + 2;
    GLuint numberIndices = numberSectors * 3;

    GLfloat angleStep = (2.0f * PI) / ((GLfloat) numberSectors);

    GLuint indexIndices;
    GLuint indexCounter;

    GLuint vertexCounter = 0;

    if (numberSectors < 3 || numberVertices > GLUS_MAX_VERTICES || numberIndices > GLUS_MAX_INDICES)
    {
        return GL_FALSE;
    }

    if (!shape)
    {
        return GL_FALSE;
    }
    ShapeInitf(shape);

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLfloat*) MemoryMalloc(4 * numberVertices * sizeof(GLfloat));
    shape->normals = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->tangents = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->texCoords = (GLfloat*) MemoryMalloc(2 * numberVertices * sizeof(GLfloat));
    shape->indices = (GLuint*) MemoryMalloc(numberIndices * sizeof(GLuint));

    if (!ShapeCheckf(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    // Center
    shape->vertices[vertexCounter * 4 + 0] = 0.0f;
    shape->vertices[vertexCounter * 4 + 1] = 0.0f;
    shape->vertices[vertexCounter * 4 + 2] = 0.0f;
    shape->vertices[vertexCounter * 4 + 3] = 1.0f;

    shape->normals[vertexCounter * 3 + 0] = 0.0f;
    shape->normals[vertexCounter * 3 + 1] = 0.0f;
    shape->normals[vertexCounter * 3 + 2] = 1.0f;

    shape->tangents[vertexCounter * 3 + 0] = 1.0f;
    shape->tangents[vertexCounter * 3 + 1] = 0.0f;
    shape->tangents[vertexCounter * 3 + 2] = 0.0f;

    shape->texCoords[vertexCounter * 2 + 0] = 0.5f;
    shape->texCoords[vertexCounter * 2 + 1] = 0.5f;

    vertexCounter++;

    for (i = 0; i < numberSectors + 1; i++)
    {
    	GLfloat currentAngle = angleStep * (GLfloat)i;

		shape->vertices[vertexCounter * 4 + 0] = cosf(currentAngle) * radius;
		shape->vertices[vertexCounter * 4 + 1] = sinf(currentAngle) * radius;
		shape->vertices[vertexCounter * 4 + 2] = 0.0f;
		shape->vertices[vertexCounter * 4 + 3] = 1.0f;

		shape->normals[vertexCounter * 3 + 0] = 0.0f;
		shape->normals[vertexCounter * 3 + 1] = 0.0f;
		shape->normals[vertexCounter * 3 + 2] = 1.0f;

		shape->tangents[vertexCounter * 3 + 0] = 1.0f;
		shape->tangents[vertexCounter * 3 + 1] = 0.0f;
		shape->tangents[vertexCounter * 3 + 2] = 0.0f;

		shape->texCoords[vertexCounter * 2 + 0] = 0.5f * cosf(currentAngle) * 0.5f;
		shape->texCoords[vertexCounter * 2 + 1] = 0.5f * sinf(currentAngle) * 0.5f;

		vertexCounter++;
    }

    indexIndices = 0;

    // Bottom
    indexCounter = 1;

    for (i = 0; i < numberSectors; i++)
    {
    	shape->indices[indexIndices++] = 0;
        shape->indices[indexIndices++] = indexCounter;
        shape->indices[indexIndices++] = indexCounter + 1;

        indexCounter++;
    }

    if (!ShapeFinalizef(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

	return GL_TRUE;
}

GLboolean  ShapeCreateCubef(Shape* shape, const GLfloat halfExtend)
{
    GLuint i;

    GLuint numberVertices = 24;
    GLuint numberIndices = 36;

    GLfloat cubeVertices[] = { -1.0f, -1.0f, -1.0f, +1.0f, -1.0f, -1.0f, +1.0f, +1.0f, +1.0f, -1.0f, +1.0f, +1.0f, +1.0f, -1.0f, -1.0f, +1.0f,

    -1.0f, +1.0f, -1.0f, +1.0f, -1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, -1.0f, +1.0f,

    -1.0f, -1.0f, -1.0f, +1.0f, -1.0f, +1.0f, -1.0f, +1.0f, +1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f, -1.0f, +1.0f,

    -1.0f, -1.0f, +1.0f, +1.0f, -1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, -1.0f, +1.0f, +1.0f,

    -1.0f, -1.0f, -1.0f, +1.0f, -1.0f, -1.0f, +1.0f, +1.0f, -1.0f, +1.0f, +1.0f, +1.0f, -1.0f, +1.0f, -1.0f, +1.0f,

    +1.0f, -1.0f, -1.0f, +1.0f, +1.0f, -1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f, -1.0f, +1.0f  };

    GLfloat cubeNormals[] = {  0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

    0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f,

    0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,

    0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f,

    -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f };

    GLfloat cubeTangents[] = { +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f,

    +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f,

    -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f,

    0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, +1.0f,

    0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f };

    GLfloat cubeTexCoords[] =
            { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };

    GLuint cubeIndices[] = { 0, 2, 1, 0, 3, 2, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 15, 14, 12, 14, 13, 16, 17, 18, 16, 18, 19, 20, 23, 22, 20, 22, 21 };

    if (!shape)
    {
        return GL_FALSE;
    }
    ShapeInitf(shape);

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLfloat*) MemoryMalloc(4 * numberVertices * sizeof(GLfloat));
    shape->normals = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->tangents = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->texCoords = (GLfloat*) MemoryMalloc(2 * numberVertices * sizeof(GLfloat));
    shape->indices = (GLuint*) MemoryMalloc(numberIndices * sizeof(GLuint));

    if (!ShapeCheckf(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    memcpy(shape->vertices, cubeVertices, sizeof(cubeVertices));
    for (i = 0; i < numberVertices; i++)
    {
        shape->vertices[i * 4 + 0] *= halfExtend;
        shape->vertices[i * 4 + 1] *= halfExtend;
        shape->vertices[i * 4 + 2] *= halfExtend;
    }

    memcpy(shape->normals, cubeNormals, sizeof(cubeNormals));

    memcpy(shape->tangents, cubeTangents, sizeof(cubeTangents));

    memcpy(shape->texCoords, cubeTexCoords, sizeof(cubeTexCoords));

    memcpy(shape->indices, cubeIndices, sizeof(cubeIndices));

    if (!ShapeFinalizef(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean  ShapeCreateSpheref(Shape* shape, const GLfloat radius, const GLuint numberSlices)
{
    GLuint i, j;

    GLuint numberParallels = numberSlices / 2;
    GLuint numberVertices = (numberParallels + 1) * (numberSlices + 1);
    GLuint numberIndices = numberParallels * numberSlices * 6;

    GLfloat angleStep = (2.0f * PI) / ((GLfloat) numberSlices);

    GLuint indexIndices;

    // used later to help us calculating tangents vectors
    GLfloat helpVector[3] = { 1.0f, 0.0f, 0.0f };
    GLfloat helpQuaternion[4];
    GLfloat helpMatrix[16];

    if (numberSlices < 3 || numberVertices > GLUS_MAX_VERTICES || numberIndices > GLUS_MAX_INDICES)
    {
        return GL_FALSE;
    }

    if (!shape)
    {
        return GL_FALSE;
    }
    ShapeInitf(shape);

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLfloat*) MemoryMalloc(4 * numberVertices * sizeof(GLfloat));
    shape->normals = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->tangents = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->texCoords = (GLfloat*) MemoryMalloc(2 * numberVertices * sizeof(GLfloat));
    shape->indices = (GLuint*) MemoryMalloc(numberIndices * sizeof(GLuint));

    if (!ShapeCheckf(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    for (i = 0; i < numberParallels + 1; i++)
    {
        for (j = 0; j < numberSlices + 1; j++)
        {
            GLuint vertexIndex = (i * (numberSlices + 1) + j) * 4;
            GLuint normalIndex = (i * (numberSlices + 1) + j) * 3;
            GLuint tangentIndex = (i * (numberSlices + 1) + j) * 3;
            GLuint texCoordsIndex = (i * (numberSlices + 1) + j) * 2;

            shape->vertices[vertexIndex + 0] = radius * sinf(angleStep * (GLfloat) i) * sinf(angleStep * (GLfloat) j);
            shape->vertices[vertexIndex + 1] = radius * cosf(angleStep * (GLfloat) i);
            shape->vertices[vertexIndex + 2] = radius * sinf(angleStep * (GLfloat) i) * cosf(angleStep * (GLfloat) j);
            shape->vertices[vertexIndex + 3] = 1.0f;

            shape->normals[normalIndex + 0] = shape->vertices[vertexIndex + 0] / radius;
            shape->normals[normalIndex + 1] = shape->vertices[vertexIndex + 1] / radius;
            shape->normals[normalIndex + 2] = shape->vertices[vertexIndex + 2] / radius;

            shape->texCoords[texCoordsIndex + 0] = (GLfloat) j / (GLfloat) numberSlices;
            shape->texCoords[texCoordsIndex + 1] = 1.0f - (GLfloat) i / (GLfloat) numberParallels;

            // use quaternion to get the tangent vector
            QuaternionRotateRyf(helpQuaternion, 360.0f * shape->texCoords[texCoordsIndex + 0]);
            QuaternionGetMatrix4x4f(helpMatrix, helpQuaternion);

            Matrix4x4MultiplyVector3f(&shape->tangents[tangentIndex], helpMatrix, helpVector);
        }
    }

    indexIndices = 0;
    for (i = 0; i < numberParallels; i++)
    {
        for (j = 0; j < numberSlices; j++)
        {
            shape->indices[indexIndices++] = i * (numberSlices + 1) + j;
            shape->indices[indexIndices++] = (i + 1) * (numberSlices + 1) + j;
            shape->indices[indexIndices++] = (i + 1) * (numberSlices + 1) + (j + 1);

            shape->indices[indexIndices++] = i * (numberSlices + 1) + j;
            shape->indices[indexIndices++] = (i + 1) * (numberSlices + 1) + (j + 1);
            shape->indices[indexIndices++] = i * (numberSlices + 1) + (j + 1);
        }
    }

    if (!ShapeFinalizef(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

	return GL_TRUE;
}

GLboolean  ShapeCreateDomef(Shape* shape, const GLfloat radius, const GLuint numberSlices)
{
    GLuint i, j;

    GLuint numberParallels = numberSlices / 4;
    GLuint numberVertices = (numberParallels + 1) * (numberSlices + 1);
    GLuint numberIndices = numberParallels * numberSlices * 6;

    GLfloat angleStep = (2.0f * PI) / ((GLfloat) numberSlices);

    GLuint indexIndices;

    // used later to help us calculating tangents vectors
    GLfloat helpVector[3] = { 1.0f, 0.0f, 0.0f };
    GLfloat helpQuaternion[4];
    GLfloat helpMatrix[16];

    if (numberSlices < 3 || numberVertices > GLUS_MAX_VERTICES || numberIndices > GLUS_MAX_INDICES)
    {
        return GL_FALSE;
    }

    if (!shape)
    {
        return GL_FALSE;
    }
    ShapeInitf(shape);

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLfloat*) MemoryMalloc(4 * numberVertices * sizeof(GLfloat));
    shape->normals = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->tangents = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->texCoords = (GLfloat*) MemoryMalloc(2 * numberVertices * sizeof(GLfloat));
    shape->indices = (GLuint*) MemoryMalloc(numberIndices * sizeof(GLuint));

    if (!ShapeCheckf(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    for (i = 0; i < numberParallels + 1; i++)
    {
        for (j = 0; j < numberSlices + 1; j++)
        {
            GLuint vertexIndex = (i * (numberSlices + 1) + j) * 4;
            GLuint normalIndex = (i * (numberSlices + 1) + j) * 3;
            GLuint tangentIndex = (i * (numberSlices + 1) + j) * 3;
            GLuint texCoordsIndex = (i * (numberSlices + 1) + j) * 2;

            shape->vertices[vertexIndex + 0] = radius * sinf(angleStep * (GLfloat) i) * sinf(angleStep * (GLfloat) j);
            shape->vertices[vertexIndex + 1] = radius * cosf(angleStep * (GLfloat) i);
            shape->vertices[vertexIndex + 2] = radius * sinf(angleStep * (GLfloat) i) * cosf(angleStep * (GLfloat) j);
            shape->vertices[vertexIndex + 3] = 1.0f;

            shape->normals[normalIndex + 0] = shape->vertices[vertexIndex + 0] / radius;
            shape->normals[normalIndex + 1] = shape->vertices[vertexIndex + 1] / radius;
            shape->normals[normalIndex + 2] = shape->vertices[vertexIndex + 2] / radius;

            shape->texCoords[texCoordsIndex + 0] = (GLfloat) j / (GLfloat) numberSlices;
            shape->texCoords[texCoordsIndex + 1] = 1.0f - (GLfloat) i / (GLfloat) numberParallels;

            // use quaternion to get the tangent vector
            QuaternionRotateRyf(helpQuaternion, 360.0f * shape->texCoords[texCoordsIndex + 0]);
            QuaternionGetMatrix4x4f(helpMatrix, helpQuaternion);

            Matrix4x4MultiplyVector3f(&shape->tangents[tangentIndex], helpMatrix, helpVector);
        }
    }

    indexIndices = 0;
    for (i = 0; i < numberParallels; i++)
    {
        for (j = 0; j < numberSlices; j++)
        {
            shape->indices[indexIndices++] = i * (numberSlices + 1) + j;
            shape->indices[indexIndices++] = (i + 1) * (numberSlices + 1) + j;
            shape->indices[indexIndices++] = (i + 1) * (numberSlices + 1) + (j + 1);

            shape->indices[indexIndices++] = i * (numberSlices + 1) + j;
            shape->indices[indexIndices++] = (i + 1) * (numberSlices + 1) + (j + 1);
            shape->indices[indexIndices++] = i * (numberSlices + 1) + (j + 1);
        }
    }

    if (!ShapeFinalizef(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

	return GL_TRUE;
}

/*
 * @author Pablo Alonso-Villaverde Roza
 * @author Norbert Nopper
 */
GLboolean  ShapeCreateTorusf(Shape* shape, const GLfloat innerRadius, const GLfloat outerRadius, const GLuint numberSlices, const GLuint numberStacks)
{
    // s, t = parametric values of the equations, in the range [0,1]
    GLfloat s = 0;
    GLfloat t = 0;

    // sIncr, tIncr are increment values aplied to s and t on each loop iteration to generate the torus
    GLfloat sIncr;
    GLfloat tIncr;

    // to store precomputed sin and cos values
    GLfloat cos2PIs, sin2PIs, cos2PIt, sin2PIt;

    GLuint numberVertices;
    GLuint numberIndices;

    // used later to help us calculating tangents vectors
    GLfloat helpVector[3] = { 0.0f, 1.0f, 0.0f };
    GLfloat helpQuaternion[4];
    GLfloat helpMatrix[16];

    // indices for each type of buffer (of vertices, indices, normals...)
    GLuint indexVertices, indexIndices, indexNormals, indexTangents, indexTexCoords;

    // loop counters
    GLuint sideCount, faceCount;

    // used to generate the indices
    GLuint v0, v1, v2, v3;

    GLfloat torusRadius = (outerRadius - innerRadius) / 2.0f;
    GLfloat centerRadius = outerRadius - torusRadius;

    numberVertices = (numberStacks + 1) * (numberSlices + 1);
    numberIndices = numberStacks * numberSlices * 2 * 3; // 2 triangles per face * 3 indices per triangle

    if (numberSlices < 3 || numberStacks < 3 || numberVertices > GLUS_MAX_VERTICES || numberIndices > GLUS_MAX_INDICES)
    {
        return GL_FALSE;
    }

    if (!shape)
    {
        return GL_FALSE;
    }
    ShapeInitf(shape);

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLfloat*) MemoryMalloc(4 * numberVertices * sizeof(GLfloat));
    shape->normals = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->tangents = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->texCoords = (GLfloat*) MemoryMalloc(2 * numberVertices * sizeof(GLfloat));
    shape->indices = (GLuint*) MemoryMalloc(numberIndices * sizeof(GLuint));

    if (!ShapeCheckf(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    sIncr = 1.0f / (GLfloat) numberSlices;
    tIncr = 1.0f / (GLfloat) numberStacks;

    // generate vertices and its attributes
    for (sideCount = 0; sideCount <= numberSlices; ++sideCount, s += sIncr)
    {
        // precompute some values
        cos2PIs = (GLfloat) cosf(2.0f * PI * s);
        sin2PIs = (GLfloat) sinf(2.0f * PI * s);

        t = 0.0f;
        for (faceCount = 0; faceCount <= numberStacks; ++faceCount, t += tIncr)
        {
            // precompute some values
            cos2PIt = (GLfloat) cosf(2.0f * PI * t);
            sin2PIt = (GLfloat) sinf(2.0f * PI * t);

            // generate vertex and stores it in the right position
            indexVertices = ((sideCount * (numberStacks + 1)) + faceCount) * 4;
            shape->vertices[indexVertices + 0] = (centerRadius + torusRadius * cos2PIt) * cos2PIs;
            shape->vertices[indexVertices + 1] = (centerRadius + torusRadius * cos2PIt) * sin2PIs;
            shape->vertices[indexVertices + 2] = torusRadius * sin2PIt;
            shape->vertices[indexVertices + 3] = 1.0f;

            // generate normal and stores it in the right position
            // NOTE: cos (2PIx) = cos (x) and sin (2PIx) = sin (x) so, we can use this formula
            //       normal = {cos(2PIs)cos(2PIt) , sin(2PIs)cos(2PIt) ,sin(2PIt)}
            indexNormals = ((sideCount * (numberStacks + 1)) + faceCount) * 3;
            shape->normals[indexNormals + 0] = cos2PIs * cos2PIt;
            shape->normals[indexNormals + 1] = sin2PIs * cos2PIt;
            shape->normals[indexNormals + 2] = sin2PIt;

            // generate texture coordinates and stores it in the right position
            indexTexCoords = ((sideCount * (numberStacks + 1)) + faceCount) * 2;
            shape->texCoords[indexTexCoords + 0] = s;
            shape->texCoords[indexTexCoords + 1] = t;

            // use quaternion to get the tangent vector
            QuaternionRotateRzf(helpQuaternion, 360.0f * s);
            QuaternionGetMatrix4x4f(helpMatrix, helpQuaternion);

            indexTangents = ((sideCount * (numberStacks + 1)) + faceCount) * 3;

            Matrix4x4MultiplyVector3f(&shape->tangents[indexTangents], helpMatrix, helpVector);
        }
    }

    // generate indices
    indexIndices = 0;
    for (sideCount = 0; sideCount < numberSlices; ++sideCount)
    {
        for (faceCount = 0; faceCount < numberStacks; ++faceCount)
        {
            // get the number of the vertices for a face of the torus. They must be < numVertices
            v0 = ((sideCount * (numberStacks + 1)) + faceCount);
            v1 = (((sideCount + 1) * (numberStacks + 1)) + faceCount);
            v2 = (((sideCount + 1) * (numberStacks + 1)) + (faceCount + 1));
            v3 = ((sideCount * (numberStacks + 1)) + (faceCount + 1));

            // first triangle of the face, counter clock wise winding
            shape->indices[indexIndices++] = v0;
            shape->indices[indexIndices++] = v1;
            shape->indices[indexIndices++] = v2;

            // second triangle of the face, counter clock wise winding
            shape->indices[indexIndices++] = v0;
            shape->indices[indexIndices++] = v2;
            shape->indices[indexIndices++] = v3;
        }
    }

    if (!ShapeFinalizef(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean  ShapeCreateCylinderf(Shape* shape, const GLfloat halfExtend, const GLfloat radius, const GLuint numberSlices)
{
    GLuint i, j;

    GLuint numberVertices = (numberSlices + 2) * 2 + (numberSlices + 1) * 2;
    GLuint numberIndices = numberSlices * 3 * 2 + numberSlices * 6;

    GLfloat angleStep = (2.0f * PI) / ((GLfloat) numberSlices);

    GLuint indexIndices;
    GLuint centerIndex;
    GLuint indexCounter;

    GLuint vertexCounter = 0;

    if (numberSlices < 3 || numberVertices > GLUS_MAX_VERTICES || numberIndices > GLUS_MAX_INDICES)
    {
        return GL_FALSE;
    }

    if (!shape)
    {
        return GL_FALSE;
    }
    ShapeInitf(shape);

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLfloat*) MemoryMalloc(4 * numberVertices * sizeof(GLfloat));
    shape->normals = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->tangents = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->texCoords = (GLfloat*) MemoryMalloc(2 * numberVertices * sizeof(GLfloat));
    shape->indices = (GLuint*) MemoryMalloc(numberIndices * sizeof(GLuint));

    if (!ShapeCheckf(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    // Center bottom
    shape->vertices[vertexCounter * 4 + 0] = 0.0f;
    shape->vertices[vertexCounter * 4 + 1] = -halfExtend;
    shape->vertices[vertexCounter * 4 + 2] = 0.0f;
    shape->vertices[vertexCounter * 4 + 3] = 1.0f;

    shape->normals[vertexCounter * 3 + 0] = 0.0f;
    shape->normals[vertexCounter * 3 + 1] = -1.0f;
    shape->normals[vertexCounter * 3 + 2] = 0.0f;

    shape->tangents[vertexCounter * 3 + 0] = 0.0f;
    shape->tangents[vertexCounter * 3 + 1] = 0.0f;
    shape->tangents[vertexCounter * 3 + 2] = 1.0f;

    shape->texCoords[vertexCounter * 2 + 0] = 0.0f;
    shape->texCoords[vertexCounter * 2 + 1] = 0.0f;

    vertexCounter++;

    // Bottom
    for (i = 0; i < numberSlices + 1; i++)
    {
    	GLfloat currentAngle = angleStep * (GLfloat)i;

		shape->vertices[vertexCounter * 4 + 0] = cosf(currentAngle) * radius;
		shape->vertices[vertexCounter * 4 + 1] = -halfExtend;
		shape->vertices[vertexCounter * 4 + 2] = -sinf(currentAngle) * radius;
		shape->vertices[vertexCounter * 4 + 3] = 1.0f;

		shape->normals[vertexCounter * 3 + 0] = 0.0f;
		shape->normals[vertexCounter * 3 + 1] = -1.0f;
		shape->normals[vertexCounter * 3 + 2] = 0.0f;

		shape->tangents[vertexCounter * 3 + 0] = sinf(currentAngle);
		shape->tangents[vertexCounter * 3 + 1] = 0.0f;
		shape->tangents[vertexCounter * 3 + 2] = cosf(currentAngle);

		shape->texCoords[vertexCounter * 2 + 0] = 0.0f;
		shape->texCoords[vertexCounter * 2 + 1] = 0.0f;

		vertexCounter++;
    }

    // Center top
    shape->vertices[vertexCounter * 4 + 0] = 0.0f;
    shape->vertices[vertexCounter * 4 + 1] = halfExtend;
    shape->vertices[vertexCounter * 4 + 2] = 0.0f;
    shape->vertices[vertexCounter * 4 + 3] = 1.0f;

    shape->normals[vertexCounter * 3 + 0] = 0.0f;
    shape->normals[vertexCounter * 3 + 1] = 1.0f;
    shape->normals[vertexCounter * 3 + 2] = 0.0f;

    shape->tangents[vertexCounter * 3 + 0] = 0.0f;
    shape->tangents[vertexCounter * 3 + 1] = 0.0f;
    shape->tangents[vertexCounter * 3 + 2] = -1.0f;

    shape->texCoords[vertexCounter * 2 + 0] = 1.0f;
    shape->texCoords[vertexCounter * 2 + 1] = 1.0f;

    vertexCounter++;

    // Top
    for (i = 0; i < numberSlices + 1; i++)
    {
    	GLfloat currentAngle = angleStep * (GLfloat)i;

		shape->vertices[vertexCounter * 4 + 0] = cosf(currentAngle) * radius;
		shape->vertices[vertexCounter * 4 + 1] = halfExtend;
		shape->vertices[vertexCounter * 4 + 2] = -sinf(currentAngle) * radius;
		shape->vertices[vertexCounter * 4 + 3] = 1.0f;

		shape->normals[vertexCounter * 3 + 0] = 0.0f;
		shape->normals[vertexCounter * 3 + 1] = 1.0f;
		shape->normals[vertexCounter * 3 + 2] = 0.0f;

		shape->tangents[vertexCounter * 3 + 0] = -sinf(currentAngle);
		shape->tangents[vertexCounter * 3 + 1] = 0.0f;
		shape->tangents[vertexCounter * 3 + 2] = -cosf(currentAngle);

		shape->texCoords[vertexCounter * 2 + 0] = 1.0f;
		shape->texCoords[vertexCounter * 2 + 1] = 1.0f;

		vertexCounter++;
    }

    for (i = 0; i < numberSlices + 1; i++)
    {
		GLfloat currentAngle = angleStep * (GLfloat)i;

		GLfloat sign = -1.0f;

		for (j = 0; j < 2; j++)
        {
			shape->vertices[vertexCounter * 4 + 0] = cosf(currentAngle) * radius;
			shape->vertices[vertexCounter * 4 + 1] = halfExtend * sign;
			shape->vertices[vertexCounter * 4 + 2] = -sinf(currentAngle) * radius;
			shape->vertices[vertexCounter * 4 + 3] = 1.0f;

			shape->normals[vertexCounter * 3 + 0] = cosf(currentAngle);
			shape->normals[vertexCounter * 3 + 1] = 0.0f;
			shape->normals[vertexCounter * 3 + 2] = -sinf(currentAngle);

			shape->tangents[vertexCounter * 3 + 0] = -sinf(currentAngle);
			shape->tangents[vertexCounter * 3 + 1] = 0.0f;
			shape->tangents[vertexCounter * 3 + 2] = -cosf(currentAngle);

			shape->texCoords[vertexCounter * 2 + 0] = (GLfloat)i / (GLfloat)numberSlices;
			shape->texCoords[vertexCounter * 2 + 1] = (sign + 1.0f) / 2.0f;

			vertexCounter++;

			sign = 1.0f;
        }
    }

    indexIndices = 0;

    // Bottom
    centerIndex = 0;
    indexCounter = 1;

    for (i = 0; i < numberSlices; i++)
    {
    	shape->indices[indexIndices++] = centerIndex;
        shape->indices[indexIndices++] = indexCounter + 1;
        shape->indices[indexIndices++] = indexCounter;

        indexCounter++;
    }
    indexCounter++;

    // Top
    centerIndex = indexCounter;
    indexCounter++;

    for (i = 0; i < numberSlices; i++)
    {
    	shape->indices[indexIndices++] = centerIndex;
        shape->indices[indexIndices++] = indexCounter;
        shape->indices[indexIndices++] = indexCounter + 1;

        indexCounter++;
    }
    indexCounter++;

    // Sides
    for (i = 0; i < numberSlices; i++)
    {
    	shape->indices[indexIndices++] = indexCounter;
        shape->indices[indexIndices++] = indexCounter + 2;
        shape->indices[indexIndices++] = indexCounter + 1;

    	shape->indices[indexIndices++] = indexCounter + 2;
        shape->indices[indexIndices++] = indexCounter + 3;
        shape->indices[indexIndices++] = indexCounter + 1;

        indexCounter += 2;
    }

    if (!ShapeFinalizef(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

	return GL_TRUE;
}

GLboolean  ShapeCreateConef(Shape* shape, const GLfloat halfExtend, const GLfloat radius, const GLuint numberSlices, const GLuint numberStacks)
{
    GLuint i, j;

    GLuint numberVertices = (numberSlices + 2) + (numberSlices + 1) * (numberStacks + 1);
    GLuint numberIndices = numberSlices * 3 + numberSlices * 6 * numberStacks;

    GLfloat angleStep = (2.0f * PI) / ((GLfloat) numberSlices);

    GLuint indexIndices;
    GLuint centerIndex;
    GLuint indexCounter;

    GLuint vertexCounter = 0;

    GLfloat h = 2.0f * halfExtend;
    GLfloat r = radius;
    GLfloat l = sqrtf(h*h + r*r);

    if (numberSlices < 3 || numberStacks < 1 || numberVertices > GLUS_MAX_VERTICES || numberIndices > GLUS_MAX_INDICES)
    {
        return GL_FALSE;
    }

    if (!shape)
    {
        return GL_FALSE;
    }
    ShapeInitf(shape);

    shape->numberVertices = numberVertices;
    shape->numberIndices = numberIndices;

    shape->vertices = (GLfloat*) MemoryMalloc(4 * numberVertices * sizeof(GLfloat));
    shape->normals = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->tangents = (GLfloat*) MemoryMalloc(3 * numberVertices * sizeof(GLfloat));
    shape->texCoords = (GLfloat*) MemoryMalloc(2 * numberVertices * sizeof(GLfloat));
    shape->indices = (GLuint*) MemoryMalloc(numberIndices * sizeof(GLuint));

    if (!ShapeCheckf(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

    // Center bottom
    shape->vertices[vertexCounter * 4 + 0] = 0.0f;
    shape->vertices[vertexCounter * 4 + 1] = -halfExtend;
    shape->vertices[vertexCounter * 4 + 2] = 0.0f;
    shape->vertices[vertexCounter * 4 + 3] = 1.0f;

    shape->normals[vertexCounter * 3 + 0] = 0.0f;
    shape->normals[vertexCounter * 3 + 1] = -1.0f;
    shape->normals[vertexCounter * 3 + 2] = 0.0f;

    shape->tangents[vertexCounter * 3 + 0] = 0.0f;
    shape->tangents[vertexCounter * 3 + 1] = 0.0f;
    shape->tangents[vertexCounter * 3 + 2] = 1.0f;

    shape->texCoords[vertexCounter * 2 + 0] = 0.0f;
    shape->texCoords[vertexCounter * 2 + 1] = 0.0f;

    vertexCounter++;

    // Bottom
    for (i = 0; i < numberSlices + 1; i++)
    {
    	GLfloat currentAngle = angleStep * (GLfloat)i;

		shape->vertices[vertexCounter * 4 + 0] = cosf(currentAngle) * radius;
		shape->vertices[vertexCounter * 4 + 1] = -halfExtend;
		shape->vertices[vertexCounter * 4 + 2] = -sinf(currentAngle) * radius;
		shape->vertices[vertexCounter * 4 + 3] = 1.0f;

		shape->normals[vertexCounter * 3 + 0] = 0.0f;
		shape->normals[vertexCounter * 3 + 1] = -1.0f;
		shape->normals[vertexCounter * 3 + 2] = 0.0f;

		shape->tangents[vertexCounter * 3 + 0] = sinf(currentAngle);
		shape->tangents[vertexCounter * 3 + 1] = 0.0f;
		shape->tangents[vertexCounter * 3 + 2] = cosf(currentAngle);

		shape->texCoords[vertexCounter * 2 + 0] = 0.0f;
		shape->texCoords[vertexCounter * 2 + 1] = 0.0f;

		vertexCounter++;
    }

	for (j = 0; j < numberStacks + 1; j++)
    {
		GLfloat level = (GLfloat)j / (GLfloat)numberStacks;

		for (i = 0; i < numberSlices + 1; i++)
		{
			GLfloat currentAngle = angleStep * (GLfloat)i;

			shape->vertices[vertexCounter * 4 + 0] = cosf(currentAngle) * radius * (1.0f - level);
			shape->vertices[vertexCounter * 4 + 1] = -halfExtend + 2.0f * halfExtend * level;
			shape->vertices[vertexCounter * 4 + 2] = -sinf(currentAngle) * radius * (1.0f - level);
			shape->vertices[vertexCounter * 4 + 3] = 1.0f;

			shape->normals[vertexCounter * 3 + 0] = h / l * cosf(currentAngle);
			shape->normals[vertexCounter * 3 + 1] = r / l;
			shape->normals[vertexCounter * 3 + 2] = h / l * -sinf(currentAngle);

			shape->tangents[vertexCounter * 3 + 0] = -sinf(currentAngle);
			shape->tangents[vertexCounter * 3 + 1] = 0.0f;
			shape->tangents[vertexCounter * 3 + 2] = -cosf(currentAngle);

			shape->texCoords[vertexCounter * 2 + 0] = (GLfloat)i / (GLfloat)numberSlices;
			shape->texCoords[vertexCounter * 2 + 1] = level;

			vertexCounter++;
        }
    }

    indexIndices = 0;

    // Bottom
    centerIndex = 0;
    indexCounter = 1;

    for (i = 0; i < numberSlices; i++)
    {
    	shape->indices[indexIndices++] = centerIndex;
        shape->indices[indexIndices++] = indexCounter + 1;
        shape->indices[indexIndices++] = indexCounter;

        indexCounter++;
    }
    indexCounter++;

    // Sides
	for (j = 0; j < numberStacks; j++)
	{
		for (i = 0; i < numberSlices; i++)
		{
			shape->indices[indexIndices++] = indexCounter;
			shape->indices[indexIndices++] = indexCounter + 1;
			shape->indices[indexIndices++] = indexCounter + numberSlices + 1;

			shape->indices[indexIndices++] = indexCounter + 1;
			shape->indices[indexIndices++] = indexCounter + numberSlices + 2;
			shape->indices[indexIndices++] = indexCounter + numberSlices + 1;

	        indexCounter++;
    	}
		indexCounter++;
    }

    if (!ShapeFinalizef(shape))
    {
        ShapeDestroyf(shape);

        return GL_FALSE;
    }

	return GL_TRUE;
}

GLboolean  ShapeCalculateTangentBitangentf(Shape* shape)
{
    GLuint i;

    if (!shape || !shape->vertices || !shape->texCoords || shape->mode != GL_TRIANGLES)
    {
        return GL_FALSE;
    }

    // Allocate memory if needed
    if (!shape->tangents)
    {
    	shape->tangents = (GLfloat*) MemoryMalloc(3 * shape->numberVertices * sizeof(GLfloat));

        if (!shape->tangents)
        {
            return GL_FALSE;
        }
    }

    if (!shape->bitangents)
    {
    	shape->bitangents = (GLfloat*) MemoryMalloc(3 * shape->numberVertices * sizeof(GLfloat));

        if (!shape->bitangents)
        {
            return GL_FALSE;
        }
    }

    // Reset all tangents to 0.0f
    for (i = 0; i < shape->numberVertices; i++)
    {
    	shape->tangents[i * 3] = 0.0f;
    	shape->tangents[i * 3 + 1] = 0.0f;
    	shape->tangents[i * 3 + 2] = 0.0f;

    	shape->bitangents[i * 3] = 0.0f;
    	shape->bitangents[i * 3 + 1] = 0.0f;
    	shape->bitangents[i * 3 + 2] = 0.0f;
    }

    if (shape->numberIndices > 0)
    {
    	float s1, t1, s2, t2;
    	float Q1[4];
    	float Q2[4];
    	float tangent[3];
    	float bitangent[3];
    	float scalar;

    	for (i = 0; i < shape->numberIndices; i += 3)
    	{
    		s1 = shape->texCoords[2*shape->indices[i+1]] - shape->texCoords[2*shape->indices[i]];
    		t1 = shape->texCoords[2*shape->indices[i+1]+1] - shape->texCoords[2*shape->indices[i]+1];
    		s2 = shape->texCoords[2*shape->indices[i+2]] - shape->texCoords[2*shape->indices[i]];
    		t2 = shape->texCoords[2*shape->indices[i+2]+1] - shape->texCoords[2*shape->indices[i]+1];

    		scalar = 1.0f / (s1*t2-s2*t1);

    		Point4SubtractPoint4f(Q1, &shape->vertices[4*shape->indices[i+1]], &shape->vertices[4*shape->indices[i]]);
    		Q1[3] = 1.0f;
    		Point4SubtractPoint4f(Q2, &shape->vertices[4*shape->indices[i+2]], &shape->vertices[4*shape->indices[i]]);
    		Q2[3] = 1.0f;

    		tangent[0] = scalar * (t2 * Q1[0] - t1 * Q2[0]);
    		tangent[1] = scalar * (t2 * Q1[1] - t1 * Q2[1]);
    		tangent[2] = scalar * (t2 * Q1[2] - t1 * Q2[2]);

    		bitangent[0] = scalar * (-s2 * Q1[0] + s1 * Q2[0]);
    		bitangent[1] = scalar * (-s2 * Q1[1] + s1 * Q2[1]);
    		bitangent[2] = scalar * (-s2 * Q1[2] + s1 * Q2[2]);

    		Vector3Normalizef(tangent);

    		Vector3Normalizef(bitangent);

        	shape->tangents[3 * shape->indices[i]] += tangent[0];
        	shape->tangents[3 * shape->indices[i] + 1] += tangent[1];
        	shape->tangents[3 * shape->indices[i] + 2] += tangent[2];

        	shape->tangents[3 * shape->indices[i+1]] += tangent[0];
        	shape->tangents[3 * shape->indices[i+1] + 1] += tangent[1];
        	shape->tangents[3 * shape->indices[i+1] + 2] += tangent[2];

        	shape->tangents[3 * shape->indices[i+2]] += tangent[0];
        	shape->tangents[3 * shape->indices[i+2] + 1] += tangent[1];
        	shape->tangents[3 * shape->indices[i+2] + 2] += tangent[2];


        	shape->bitangents[3 * shape->indices[i]] += bitangent[0];
        	shape->bitangents[3 * shape->indices[i] + 1] += bitangent[1];
        	shape->bitangents[3 * shape->indices[i] + 2] += bitangent[2];

        	shape->bitangents[3 * shape->indices[i+1]] += bitangent[0];
        	shape->bitangents[3 * shape->indices[i+1] + 1] += bitangent[1];
        	shape->bitangents[3 * shape->indices[i+1] + 2] += bitangent[2];

        	shape->bitangents[3 * shape->indices[i+2]] += bitangent[0];
        	shape->bitangents[3 * shape->indices[i+2] + 1] += bitangent[1];
        	shape->bitangents[3 * shape->indices[i+2] + 2] += bitangent[2];
    	}
    }
    else
    {
    	float s1, t1, s2, t2;
    	float Q1[4];
    	float Q2[4];
    	float tangent[3];
    	float bitangent[3];
    	float scalar;

    	for (i = 0; i < shape->numberVertices; i += 3)
    	{
    		s1 = shape->texCoords[2*(i+1)] - shape->texCoords[2*i];
    		t1 = shape->texCoords[2*(i+1)+1] - shape->texCoords[2*i+1];
    		s2 = shape->texCoords[2*(i+2)] - shape->texCoords[2*i];
    		t2 = shape->texCoords[2*(i+2)+1] - shape->texCoords[2*i+1];

    		scalar = 1.0f / (s1*t2-s2*t1);

    		Point4SubtractPoint4f(Q1, &shape->vertices[4*(i+1)], &shape->vertices[4*i]);
    		Q1[3] = 1.0f;
    		Point4SubtractPoint4f(Q2, &shape->vertices[4*(i+2)], &shape->vertices[4*i]);
    		Q2[3] = 1.0f;

    		tangent[0] = scalar * (t2 * Q1[0] - t1 * Q2[0]);
    		tangent[1] = scalar * (t2 * Q1[1] - t1 * Q2[1]);
    		tangent[2] = scalar * (t2 * Q1[2] - t1 * Q2[2]);

    		bitangent[0] = scalar * (-s2 * Q1[0] + s1 * Q2[0]);
    		bitangent[1] = scalar * (-s2 * Q1[1] + s1 * Q2[1]);
    		bitangent[2] = scalar * (-s2 * Q1[2] + s1 * Q2[2]);

    		Vector3Normalizef(tangent);

    		Vector3Normalizef(bitangent);

        	shape->tangents[3 * i] += tangent[0];
        	shape->tangents[3 * i + 1] += tangent[1];
        	shape->tangents[3 * i + 2] += tangent[2];

        	shape->tangents[3 * (i+1)] += tangent[0];
        	shape->tangents[3 * (i+1) + 1] += tangent[1];
        	shape->tangents[3 * (i+1) + 2] += tangent[2];

        	shape->tangents[3 * (i+2)] += tangent[0];
        	shape->tangents[3 * (i+2) + 1] += tangent[1];
        	shape->tangents[3 * (i+2) + 2] += tangent[2];


        	shape->bitangents[3 * i] += bitangent[0];
        	shape->bitangents[3 * i + 1] += bitangent[1];
        	shape->bitangents[3 * i + 2] += bitangent[2];

        	shape->bitangents[3 * (i+1)] += bitangent[0];
        	shape->bitangents[3 * (i+1) + 1] += bitangent[1];
        	shape->bitangents[3 * (i+1) + 2] += bitangent[2];

        	shape->bitangents[3 * (i+2)] += bitangent[0];
        	shape->bitangents[3 * (i+2) + 1] += bitangent[1];
        	shape->bitangents[3 * (i+2) + 2] += bitangent[2];
    	}
    }

    // Normalize, as several triangles have added a vector
    for (i = 0; i < shape->numberVertices; i++)
    {
		Vector3Normalizef(&(shape->tangents[i * 3]));
		Vector3Normalizef(&(shape->bitangents[i * 3]));
    }

    return GL_TRUE;
}

GLboolean   ShapeCopyf(Shape* shape, const Shape* source)
{
	GLuint stride = 4 + 3 + 3 + 3 + 2;

	if (!shape || !source)
	{
		return GL_FALSE;
	}

    ShapeInitf(shape);

    shape->numberVertices = source->numberVertices;
    shape->numberIndices = source->numberIndices;
    shape->mode = source->mode;

    if (source->vertices)
    {
    	shape->vertices = (GLfloat*) MemoryMalloc(4 * source->numberVertices * sizeof(GLfloat));
        if (!shape->vertices)
        {
        	ShapeDestroyf(shape);

            return GL_FALSE;
        }
        memcpy(shape->vertices, source->vertices, 4 * source->numberVertices * sizeof(GLfloat));
    }
    if (source->normals)
    {							  
    	shape->normals = (GLfloat*) MemoryMalloc(3 * source->numberVertices * sizeof(GLfloat));
        if (!shape->normals)
        {
        	ShapeDestroyf(shape);

            return GL_FALSE;	  
        }
        memcpy(shape->normals, source->normals, 3 * source->numberVertices * sizeof(GLfloat));
    }
    if (source->tangents)
    {
    	shape->tangents = (GLfloat*) MemoryMalloc(3 * source->numberVertices * sizeof(GLfloat));
        if (!shape->tangents)
        {
        	ShapeDestroyf(shape);

            return GL_FALSE;
        }
        memcpy(shape->tangents, source->tangents, 3 * source->numberVertices * sizeof(GLfloat));
    }
    if (source->bitangents)
    {
    	shape->bitangents = (GLfloat*) MemoryMalloc(3 * source->numberVertices * sizeof(GLfloat));
        if (!shape->bitangents)
        {
        	ShapeDestroyf(shape);

            return GL_FALSE;
        }
        memcpy(shape->bitangents, source->bitangents, 3 * source->numberVertices * sizeof(GLfloat));
    }
    if (source->texCoords)
    {
    	shape->texCoords = (GLfloat*) MemoryMalloc(2 * source->numberVertices * sizeof(GLfloat));
        if (!shape->texCoords)
        {
        	ShapeDestroyf(shape);

            return GL_FALSE;
        }
        memcpy(shape->texCoords, source->texCoords, 2 * source->numberVertices * sizeof(GLfloat));
    }
    if (source->allAttributes)
    {
    	shape->allAttributes = (GLfloat*) MemoryMalloc(stride * source->numberVertices * sizeof(GLfloat));
        if (!shape->allAttributes)
        {
        	ShapeDestroyf(shape);

            return GL_FALSE;
        }
        memcpy(shape->allAttributes, source->allAttributes, stride * source->numberVertices * sizeof(GLfloat));
    }
    if (source->indices)
    {
    	shape->indices = (GLuint*) MemoryMalloc(source->numberIndices * sizeof(GLuint));
        if (!shape->indices)
        {
        	ShapeDestroyf(shape);

            return GL_FALSE;
        }
        memcpy(shape->indices, source->indices, source->numberIndices * sizeof(GLuint));
    }

    return GL_TRUE; 
}

GLvoid  ShapeDestroyf(Shape* shape)
{
    if (!shape)
    {
        return;
    }

    if (shape->vertices)
    {
        MemoryFree(shape->vertices);

        shape->vertices = 0;
    }

    if (shape->normals)
    {
        MemoryFree(shape->normals);

        shape->normals = 0;
    }

    if (shape->tangents)
    {
        MemoryFree(shape->tangents);

        shape->tangents = 0;
    }

    if (shape->bitangents)
    {
        MemoryFree(shape->bitangents);

        shape->bitangents = 0;
    }

    if (shape->texCoords)
    {
        MemoryFree(shape->texCoords);

        shape->texCoords = 0;
    }

    if (shape->allAttributes)
    {
        MemoryFree(shape->allAttributes);

        shape->allAttributes = 0;
    }

    if (shape->indices)
    {
        MemoryFree(shape->indices);

        shape->indices = 0;
    }

    shape->numberVertices = 0;
    shape->numberIndices = 0;
    shape->mode = 0;
}
