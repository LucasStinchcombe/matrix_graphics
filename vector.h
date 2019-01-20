#ifndef MATRIX_GRAPHICS_VECTOR_H
#define MATRIX_GRAPHICS_VECTOR_H

typedef struct Point2D
{
    float x;
    float y;
} point2d_t;

typedef struct Vector2D
{
    point2d_t p1;
    point2d_t p2;
} vector2d_t;

typedef struct Point3D
{
    float x;
    float y;
    float z;
} point3d_t;

typedef struct Vector3D
{
    point3d_t p1;
    point3d_t p2;
} vector3d_t;

float lin_func(float m, float b, float x);

#endif
