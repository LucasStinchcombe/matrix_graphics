#include <check.h>
#include <math.h>
#include "graphics.h"

#define TOL 0.0000001

START_TEST(test_rotate_basis_z)
{
    angle3d_t angles = {0.0, 0.0, M_PI_2};
    point3d_t point = {1.0, 1.0, 1.0};

    rotate_basis(&angles, &point);

    ck_assert_float_eq_tol(point.x, 1.0, TOL);
    ck_assert_float_eq_tol(point.y, -1.0, TOL);
    ck_assert_float_eq_tol(point.z, 1.0, TOL);
}
END_TEST

START_TEST(test_rotate_basis_y)
{
    angle3d_t angles = {0.0, M_PI_2, 0.0};
    point3d_t point = {1.0, 1.0, 1.0};

    rotate_basis(&angles, &point);

    ck_assert_float_eq_tol(point.x, -1.0, TOL);
    ck_assert_float_eq_tol(point.y, 1.0, TOL);
    ck_assert_float_eq_tol(point.z, 1.0, TOL);
}
END_TEST

START_TEST(test_rotate_basis_x)
{
    angle3d_t angles = {M_PI_2, 0.0, 0.0};
    point3d_t point = {1.0, 1.0, 1.0};

    rotate_basis(&angles, &point);

    ck_assert_float_eq_tol(point.x, 1.0, TOL);
    ck_assert_float_eq_tol(point.y, 1.0, TOL);
    ck_assert_float_eq_tol(point.z, -1.0, TOL);
}
END_TEST

Suite* graphics_suite()
{
    Suite* s = suite_create("Graphics");
    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_rotate_basis_z);
    tcase_add_test(tc_core, test_rotate_basis_y);
    tcase_add_test(tc_core, test_rotate_basis_x);
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    Suite* s = graphics_suite();
    SRunner* sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (num_failed != 0);
}
