#include "graphics.h"
#include "debug.h"

#include <math.h>

void camera_t_basis(camera_t *camera_t, point3d_t *point)
{
    // adjust to camera_t frame
    point->x -= camera_t->position.x;
    point->y -= camera_t->position.y;
    point->z -= camera_t->position.z;

    // TODO rotate to camera_t orientation;
    rotate_basis(&camera_t->orientation, point);
}

point2d_t perspective(camera_t *camera_t, point3d_t point)
{
    TRACE_LOG("point (%f,%f,%f)\n", point.x, point.y, point.z);
    camera_t_basis(camera_t, &point);
    LOG("camera_t-adjusted (%f,%f,%f)\n", point.x, point.y, point.z);

    point2d_t retval = {.x = ((camera_t->focal_length / point.z) * point.x),
                       .y = (camera_t->focal_length / point.z) * point.y};

    LOG("projected (%f,%f)\n", retval.x, retval.y);
    return retval;
}

void rotate_basis(angle3d_t *angles, point3d_t *point)
{
    float x = cos(angles->z) * point->x + sin(angles->z) * point->y;
    point->y = -sin(angles->z) * point->x + cos(angles->z) * point->y;
    point->x = x;

    x = cos(angles->y) * point->x - sin(angles->y) * point->z;
    point->z = sin(angles->y) * point->x + cos(angles->y) * point->z;
    point->x = x;

    x = cos(angles->x) * point->y + sin(angles->x) * point->z;
    point->z = -sin(angles->x) * point->y + cos(angles->x) * point->z;
    point->y = x;
}
