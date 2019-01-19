#ifndef ONETWO_VECTOR_H
#define ONETWO_VECTOR_H

typedef struct Point2D
{
    float x;
    float y;
} point_2d;

typedef struct Vector2D
{
    point_2d p1;
    point_2d p2;
} vector_2d;

typedef struct Point3D
{
    float x;
    float y;
    float z;
} point_3d;

typedef struct Vector3D
{
    point_3d p1;
    point_3d p2;
} vector_3d;

float lin_func(float m, float b, float x);

#endif
