#include "graphics.h"
#include "debug.h"

void camera_basis(camera *camera, point_3d *point)
{
    // adjust to camera frame
    point->x -= camera->position.x;
    point->y -= camera->position.y;
    point->z -= camera->position.z;

    // TODO rotate to camera orientation;
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
