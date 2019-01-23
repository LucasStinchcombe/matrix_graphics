#include <check.h>
#include "matrix.h"

START_TEST(test_matrix_draw_vertical)
{
    vector2d_t vec = {{0.0, 0.0}, {0.0, 16.0}};
    matrix_draw(vec);

    for(int i = 0; i != MATRIX_SIZE; ++i)
    {
        ck_assert_int_eq(matrix[i], 1 << MATRIX_SIZE -1);
    }

    matrix_clear();

    vector2d_t vec2 = {{0.0, 16.0}, {0.0, 0.0}};
    matrix_draw(vec2);

    for(int i = 0; i != MATRIX_SIZE; ++i)
    {
        ck_assert_int_eq(matrix[i], 1 << MATRIX_SIZE -1);
    }
}
END_TEST

START_TEST(test_matrix_draw_horizontal)
{
    vector2d_t vec = {{0.0, 0.0}, {16.0, 0.0}};
    matrix_draw(vec);

    ck_assert_int_eq(matrix[MATRIX_SIZE-1], 0b1111111111111111);

    matrix_clear();

    vector2d_t vec2 = {{16.0, 0.0}, {0.0, 0.0}};
    matrix_draw(vec2);

    ck_assert_int_eq(matrix[MATRIX_SIZE-1], 0b1111111111111111);
}
END_TEST

START_TEST(test_matrix_draw_diagonal)
{
    vector2d_t vec = {{0.0, 0.0}, {16.0, 16.0}};
    matrix_draw(vec);

    for(int i = 0; i != MATRIX_SIZE; ++i)
    {
        ck_assert_int_eq(matrix[i], 1 << i);
    }

    matrix_clear();

    vector2d_t vec2 = {{16.0, 16.0}, {0.0, 0.0}};
    matrix_draw(vec2);

    for(int i = 0; i != MATRIX_SIZE; ++i)
    {
        ck_assert_int_eq(matrix[i], 1 << i);
    }
}
END_TEST

Suite* matrix_suite()
{
    Suite* s = suite_create("Matrix");
    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_matrix_draw_vertical);
    tcase_add_test(tc_core, test_matrix_draw_horizontal);
    tcase_add_test(tc_core, test_matrix_draw_diagonal);
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    Suite* s = matrix_suite();
    SRunner* sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (num_failed != 0);
}
