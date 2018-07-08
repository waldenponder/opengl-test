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

#pragma once
#include "common.inner.h"

/**
 * Structure for holding geometry data.
 */
struct COMMON_API Shape
{
	/**
	 * Vertices in homogeneous coordinates.
	 */
    GLfloat* vertices;

    /**
     * Normals.
     */
    GLfloat* normals;

    /**
     * Tangents.
     */
    GLfloat* tangents;

    /**
     * Bitangents.
     */
    GLfloat* bitangents;

    /**
     * Texture coordinates.
     */
    GLfloat* texCoords;

    /**
     * All above values in one array. Not created by the model loader.
     */
    GLfloat* allAttributes;

    /**
     * Indices.
     */
    GLuint* indices;	

    /**
     * Number of vertices.
     */
    GLuint numberVertices;

    /**
     * Number of indices.
     */
    GLuint numberIndices;

    /**
     * Triangle render mode - could be either:
     *
     * GLUS_TRIANGLES
     * GLUS_TRIANGLE_STRIP
     */
    GLenum mode;	   

};


/**
 * Creates a quadratic plane.
 *
 * @param shape The data is stored into this structure.
 * @param halfExtend The length from the center point to any border of the plane.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API GLboolean  ShapeCreatePlanef(Shape* shape, const GLfloat halfExtend);

/**
 * Creates a rectangular plane.
 *
 * @param shape The data is stored into this structure.
 * @param horizontalExtend The length from the center point to the left/right border of the plane.
 * @param verticalExtend The length from the center point to the upper/lower border of the plane.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API  GLboolean  ShapeCreateRectangularPlanef(Shape* shape, const GLfloat horizontalExtend, const GLfloat verticalExtend);

/**
 * Creates a rectangular plane organized as a grid with given number rows and columns.
 *
 * @param shape The data is stored into this structure.
 * @param horizontalExtend The length from the center point to the left/right border of the plane.
 * @param verticalExtend The length from the center point to the upper/lower border of the plane.
 * @param rows The number of rows the grid should have.
 * @param columns The number of columns the grid should have.
 * @param triangleStrip Set to GL_TRUE, if a triangle strip should be created.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API GLboolean  ShapeCreateRectangularGridPlanef(Shape* shape, const GLfloat horizontalExtend, const GLfloat verticalExtend, const GLuint rows, const GLuint columns, const GLboolean triangleStrip);

/**
 * Creates a disc with the given radius and number sectors. More sectors makes the disc more round.
 *
 * @param shape The data is stored into this structure.
 * @param radius The radius of the disc.
 * @param numberSectors The number of sectors the disc should have.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API  GLboolean  ShapeCreateDiscf(Shape* shape, const GLfloat radius, const GLuint numberSectors);

/**
 * Creates a cube.
 *
 * @param shape The data is stored into this structure.
 * @param halfExtend The distance from the center point to any face of the cube.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API GLboolean  ShapeCreateCubef(Shape* shape, const GLfloat halfExtend);

/**
 * Creates a sphere. More slices makes the sphere more round.
 *
 * @param shape The data is stored into this structure.
 * @param radius The radius of the sphere.
 * @param numberSlices The number of slices the sphere should have.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API GLboolean  ShapeCreateSpheref(Shape* shape, const GLfloat radius, const GLuint numberSlices);

/**
 * Creates a dome. More slices makes the dome more round.
 *
 * @param shape The data is stored into this structure.
 * @param radius The radius of the dome.
 * @param numberSlices The number of slices the dome should have.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API  GLboolean  ShapeCreateDomef(Shape* shape, const GLfloat radius, const GLuint numberSlices);

/**
 * Creates a torus / doughnut. More slices and stacks makes the torus more round.
 *
 * @param shape The data is stored into this structure.
 * @param innerRadius The inner radius of the torus. This is the distance from the center point to the closest point from the torus surface.
 * @param outerRadius The outer radius of the torus. This is the distance from the center point to the farthest point from the torus surface.
 * @param numberSlices The number of slices the torus should have.
 * @param numberStacks The number of stacks / elements the torus should have per slice.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API  GLboolean  ShapeCreateTorusf(Shape* shape, const GLfloat innerRadius, const GLfloat outerRadius, const GLuint numberSlices, const GLuint numberStacks);

/**
 * Creates a cylinder. More slices makes the cylinder more round.
 *
 * @param shape The data is stored into this structure.
 * @param halfExtend The distance from the center point to the bottom and top disc of the cylinder.
 * @param radius The radius of the cylinder.
 * @param numberSlices The number of slices the cylinder should have.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API GLboolean  ShapeCreateCylinderf(Shape* shape, const GLfloat halfExtend, const GLfloat radius, const GLuint numberSlices);

/**
 * Creates a cone. More slices and stacks makes the torus more round and smooth.
 *
 * @param shape The data is stored into this structure.
 * @param halfExtend The distance from the center point to the bottom disc of the cone.
 * @param radius The radius of the cone at the bottom.
 * @param numberSlices The number of slices the cone should have.
 * @param numberStacks The number of stacks the cone should have.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API  GLboolean  ShapeCreateConef(Shape* shape, const GLfloat halfExtend, const GLfloat radius, const GLuint numberSlices, const GLuint numberStacks);

/**
 * Calculates and creates the tangent and bitangent vectors. Uses the previous created memory for the tangents and bitangents.
 *
 * @param shape The structure which will be filled with the calculated vectors.
 *
 * @return GL_TRUE, if creation succeeded.
 */
 COMMON_API GLboolean  ShapeCalculateTangentBitangentf(Shape* shape);

/**
 * Copies the shape.
 *
 * @param shape  The target shape.
 * @param source The source shape.
 *
 * @return GL_TRUE, if copy succeeded.
 */
 COMMON_API  GLboolean  ShapeCopyf(Shape* shape, const Shape* source);

/**
 * Destroys the shape by freeing the allocated memory.
 *
 * @param shape The structure which contains the dynamic allocated shape data, which will be freed by this function.
 */
 COMMON_API  GLvoid  ShapeDestroyf(Shape* shape);