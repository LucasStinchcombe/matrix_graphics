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

float lin_func(float m, float b, float x);

#endif
