#ifndef MATRIX_GRAPHICS_GRAPHICS_H
#define MATRIX_GRAPHICS_GRAPHICS_H

#include "vector.h"

typedef struct Tb_angles
{
    float x;
    float y;
    float z;
} angle3d_t;

typedef struct Camera
{
    point3d_t position;
    angle3d_t orientation;
    float focal_length;
} camera_t;

point2d_t perspective(camera_t *camera_t, point3d_t point);
void rotate_basis(angle3d_t *angles, point3d_t *point);

#endif
