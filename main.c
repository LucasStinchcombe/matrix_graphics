#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

// TODO cleanup includes for all sources
#include "conway.h"
#include "debug.h"
#include "graphics.h"
#include "led_matrix.h"
#include "math.h"
#include "spi.h"
#include "vector.h"

int main()
{
    LOG_INIT();

    matrix_init();

    // disable test mode
    send_matrix_code(0x0F00);

    // disable decode
    send_matrix_code(0x0900);

    // scan all digits
    send_matrix_code(0x0B07);

    // set min intensity
    send_matrix_code(0x0A01);

    // disable shutdown mode
    send_matrix_code(0x0C01);

    camera_t camera = {.position = {0.5, 0.5, -2.25},
                       .orientation = {0.0, 0.0, 0.0},
                       //.orientation = {0.0, 0.0, 0.0},
                       .focal_length = 2.0};

    /*
    camera.position.x -= 0.5;
    camera.position.y -= 0.5;
    camera.position.z -= 0.5;

    angle3d_t tb= {0.0, -M_PI_4, 0.0};
    rotate_basis(&tb, &camera.position);

    INFO_LOG("camera position (%f,%f,%f)\n",
            camera.position.x, camera.position.y, camera.position.z);

    camera.position.x += 0.5;
    camera.position.y += 0.5;
    camera.position.z += 0.5;
    */

    vector3d_t cube[12];
    /*
    cube[0] = (vector3d_t){{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}};
    cube[1] = (vector3d_t){{0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    cube[2] = (vector3d_t){{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}};
    cube[3] = (vector3d_t){{0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}};
    cube[4] = (vector3d_t){{0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}};
    cube[5] = (vector3d_t){{0.0, 1.0, 0.0}, {0.0, 1.0, 1.0}};
    cube[6] = (vector3d_t){{1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}};
    cube[7] = (vector3d_t){{1.0, 1.0, 1.0}, {1.0, 0.0, 1.0}};
    cube[8] = (vector3d_t){{1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};
    cube[9] = (vector3d_t){{1.0, 1.0, 0.0}, {1.0, 0.0, 0.0}};
    cube[10] = (vector3d_t){{1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}};
    cube[11] = (vector3d_t){{1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}};
    */

    /*
    cube[0] = (vector3d_t){{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}};
    cube[1] = (vector3d_t){{0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    cube[2] = (vector3d_t){{0.0, 1.0, 0.0}, {1.0, 1.0, 0.0}};
    cube[3] = (vector3d_t){{1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}};
    */

    cube[0] = (vector3d_t){{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}};
    cube[1] = (vector3d_t){{0.0, 0.0, 0.0}, {0.5, 0.81649658071, 0.28867513459 }};
    cube[2] = (vector3d_t){{1.0, 0.0, 0.0}, {0.5, 0.81649658071, 0.28867513459 }};
    cube[3] = (vector3d_t){{0.5, 0.0, 0.86602540378}, {0.5, 0.81649658071, 0.28867513459 }};
    cube[4] = (vector3d_t){{0.5, 0.0, 0.86602540378}, {0.0, 0.0, 0.0 }};
    cube[5] = (vector3d_t){{0.5, 0.0, 0.86602540378}, {1.0, 0.0, 0.0 }};

    for (int i = 0; i != 6; ++i)
    {
        vector2d_t vec = {perspective(&camera, cube[i].p1),
                         perspective(&camera, cube[i].p2)};
        matrix_basis(&vec);

        DEBUG_LOG("projected ((%f,%f), (%f,%f))\n", vec.p1.x, vec.p1.y, vec.p2.x,
            vec.p2.y);
        matrix_draw(vec);
        send_matrix();
    }
    while (1)
    {
        send_matrix();
        // next_iter();
        _delay_ms(500);
    }
}
