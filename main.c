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

    camera g_camera = {.position = {0.5, 0.5, -3.0},
                       .orientation = {0.0, M_PI_4 / 16, 0.0},
                       .focal_length = 2.0};

    /*
    g_camera.position.x -= 0.5;
    g_camera.position.y -= 0.5;
    g_camera.position.z -= 0.5;

    tb_angles tb= {0.0, -M_PI_4, 0.0};
    rotate_basis(&tb, &g_camera.position);

    g_camera.position.x += 0.5;
    g_camera.position.y += 0.5;
    g_camera.position.z += 0.5;
    */

    vector_3d cube[12];
    /*
    cube[0] = (vector_3d){{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}};
    cube[1] = (vector_3d){{0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    cube[2] = (vector_3d){{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}};
    cube[3] = (vector_3d){{0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}};
    cube[4] = (vector_3d){{0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}};
    cube[5] = (vector_3d){{0.0, 1.0, 0.0}, {0.0, 1.0, 1.0}};
    cube[6] = (vector_3d){{1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}};
    cube[7] = (vector_3d){{1.0, 1.0, 1.0}, {1.0, 0.0, 1.0}};
    cube[8] = (vector_3d){{1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};
    cube[9] = (vector_3d){{1.0, 1.0, 0.0}, {1.0, 0.0, 0.0}};
    cube[10] = (vector_3d){{1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}};
    cube[11] = (vector_3d){{1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}};
    */

    cube[0] = (vector_3d){{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}};
    cube[1] = (vector_3d){{0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    cube[2] = (vector_3d){{0.0, 1.0, 0.0}, {1.0, 1.0, 0.0}};
    cube[3] = (vector_3d){{1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}};

    for (int i = 0; i != 4; ++i)
    {
        vector_2d vec = {perspective(&g_camera, cube[i].p1),
                         perspective(&g_camera, cube[i].p2)};
        matrix_basis(&vec);

        LOG("projected ((%f,%f), (%f,%f))\n", vec.p1.x, vec.p1.y, vec.p2.x,
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
