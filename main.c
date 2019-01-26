#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

// TODO cleanup includes for all sources
#include "adc.h"
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
    ADC_init();

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

    // MUX to 0
    vector3d_t object[12];

    object[0] = (vector3d_t){{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}};
    object[1] =
        (vector3d_t){{0.0, 0.0, 0.0}, {0.5, 0.81649658071, 0.28867513459}};
    object[2] =
        (vector3d_t){{1.0, 0.0, 0.0}, {0.5, 0.81649658071, 0.28867513459}};
    object[3] = (vector3d_t){{0.5, 0.0, 0.86602540378},
                             {0.5, 0.81649658071, 0.28867513459}};
    object[4] = (vector3d_t){{0.5, 0.0, 0.86602540378}, {0.0, 0.0, 0.0}};
    object[5] = (vector3d_t){{0.5, 0.0, 0.86602540378}, {1.0, 0.0, 0.0}};

    float rot_y = 0;
    while (1)
    {
        matrix_clear();
        camera_t camera = {.position = {0.5, 0.5, -2.25},
                           .orientation = {0.0, -rot_y, 0.0},
                           .focal_length = 2.0};

        camera.position.x -= 0.5;
        camera.position.y -= 0.28867513459;
        camera.position.z -= 0.28867513459;

        angle3d_t tb = {0.0, rot_y, 0.0};
        rotate_basis(&tb, &camera.position);

        INFO_LOG("camera position (%f,%f,%f)\n", camera.position.x,
                 camera.position.y, camera.position.z);

        camera.position.x += 0.5;
        camera.position.y += 0.28867513459;
        camera.position.z += 0.28867513459;

        for (int i = 0; i != 6; ++i)
        {
            vector2d_t vec = {perspective(&camera, object[i].p1),
                              perspective(&camera, object[i].p2)};
            matrix_basis(&vec);

            DEBUG_LOG("projected ((%f,%f), (%f,%f))\n", vec.p1.x, vec.p1.y,
                      vec.p2.x, vec.p2.y);
            matrix_draw(vec);
        }

        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC))
            ;

        uint8_t val = get_value(0);
        INFO_LOG("ADC value: %d\n", val);
        float y = (val / 1.0 - 129.0) / 256 * 0.25;
        rot_y += y;
        send_matrix();
        // next_iter();
        //_delay_ms(500);
    }
}
