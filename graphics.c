#include "graphics.h"
#include "debug.h"

#include <math.h>

void camera_basis(camera *camera, point_3d *point)
{
    // adjust to camera frame
    point->x -= camera->position.x;
    point->y -= camera->position.y;
    point->z -= camera->position.z;

    // TODO rotate to camera orientation;
    rotate_basis(&camera->orientation, point);
}

point_2d perspective(camera *camera, point_3d point)
{
    TRACE_LOG("point (%f,%f,%f)\n", point.x, point.y, point.z);
    camera_basis(camera, &point);
    LOG("camera-adjusted (%f,%f,%f)\n", point.x, point.y, point.z);

    point_2d retval = {.x = ((camera->focal_length / point.z) * point.x),
                       .y = (camera->focal_length / point.z) * point.y};

    LOG("projected (%f,%f)\n", retval.x, retval.y);
    return retval;
}

void rotate_basis(tb_angles *angles, point_3d *point)
{
    point->x = cos(angles->z) * point->x + sin(angles->z) * point->y;
    point->y = -sin(angles->z) * point->x + cos(angles->z) * point->y;

    point->x = cos(angles->y) * point->x - sin(angles->y) * point->z;
    point->z = sin(angles->y) * point->x + cos(angles->y) * point->z;

    point->y = cos(angles->x) * point->y + sin(angles->x) * point->z;
    point->z = -sin(angles->x) * point->y + cos(angles->x) * point->z;
}
