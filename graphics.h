#ifndef MATRIX_GRAPHICS_GRAPHICS_H
#define MATRIX_GRAPHICS_GRAPHICS_H

#include "vector.h"

typedef struct Tb_angles
{
    float x;
    float y;
    float z;
} tb_angles;

typedef struct Camera
{
    point_3d position;
    tb_angles orientation;
    float focal_length;
} camera;

point_2d perspective(camera *camera, point_3d point);
void rotate_basis(tb_angles *angles, point_3d *point);

#endif
