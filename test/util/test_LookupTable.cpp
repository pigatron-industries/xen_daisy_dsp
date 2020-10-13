#include <unity.h>
#include <math.h>
#include "../../src/util/LookupTable.h"

TrigLookup<5> testSineLookup = TrigLookup<5>();

void test_TrigLookup_toIndex(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 0, testSineLookup.toIndex(0));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 1, testSineLookup.toIndex(M_PI*0.125));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 2, testSineLookup.toIndex(M_PI*0.25));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 3, testSineLookup.toIndex(M_PI*0.375));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 4, testSineLookup.toIndex(M_PI*0.5));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 5, testSineLookup.toIndex(M_PI*0.625));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 6, testSineLookup.toIndex(M_PI*0.75));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 7, testSineLookup.toIndex(M_PI*0.875));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, 8, testSineLookup.toIndex(M_PI*1));
}

void test_TrigLookup_getByIndex(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.0001,  sinf(0), testSineLookup.getByIndex(0));
    TEST_ASSERT_FLOAT_WITHIN(0.0001,  sinf(M_PI*0.125), testSineLookup.getByIndex(1));
    TEST_ASSERT_FLOAT_WITHIN(0.0001,  sinf(M_PI*0.25), testSineLookup.getByIndex(2));
    TEST_ASSERT_FLOAT_WITHIN(0.0001,  sinf(M_PI*0.375), testSineLookup.getByIndex(3));
    TEST_ASSERT_FLOAT_WITHIN(0.0001,  sinf(M_PI*0.5), testSineLookup.getByIndex(4));
}

void test_TrigLookup_sin(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*0), testSineLookup.sin(M_PI*0));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*0.125), testSineLookup.sin(M_PI*0.125));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*0.25), testSineLookup.sin(M_PI*0.25));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*0.375), testSineLookup.sin(M_PI*0.375));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*0.5), testSineLookup.sin(M_PI*0.5));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*0.625), testSineLookup.sin(M_PI*0.625));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*0.75), testSineLookup.sin(M_PI*0.75));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*0.875), testSineLookup.sin(M_PI*0.875));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*1), testSineLookup.sin(M_PI*1));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*1.125), testSineLookup.sin(M_PI*1.125));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*1.25), testSineLookup.sin(M_PI*1.25));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*1.375), testSineLookup.sin(M_PI*1.375));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*1.5), testSineLookup.sin(M_PI*1.5));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*1.625), testSineLookup.sin(M_PI*1.625));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*1.75), testSineLookup.sin(M_PI*1.75));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*1.875), testSineLookup.sin(M_PI*1.875));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*2), testSineLookup.sin(M_PI*2));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, sinf(M_PI*2.125), testSineLookup.sin(M_PI*2.125));
}

void test_TrigLookup_cos(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*0), testSineLookup.cos(M_PI*0));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*0.125), testSineLookup.cos(M_PI*0.125));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*0.25), testSineLookup.cos(M_PI*0.25));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*0.375), testSineLookup.cos(M_PI*0.375));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*0.5), testSineLookup.cos(M_PI*0.5));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*0.625), testSineLookup.cos(M_PI*0.625));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*0.75), testSineLookup.cos(M_PI*0.75));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*0.875), testSineLookup.cos(M_PI*0.875));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*1), testSineLookup.cos(M_PI*1));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*1.125), testSineLookup.cos(M_PI*1.125));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*1.25), testSineLookup.cos(M_PI*1.25));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*1.375), testSineLookup.cos(M_PI*1.375));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*1.5), testSineLookup.cos(M_PI*1.5));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*1.625), testSineLookup.cos(M_PI*1.625));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*1.75), testSineLookup.cos(M_PI*1.75));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*1.875), testSineLookup.cos(M_PI*1.875));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*2), testSineLookup.cos(M_PI*2));
    TEST_ASSERT_FLOAT_WITHIN(0.0001, cosf(M_PI*2.125), testSineLookup.cos(M_PI*2.125));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_TrigLookup_toIndex);
    RUN_TEST(test_TrigLookup_getByIndex);
    RUN_TEST(test_TrigLookup_sin);
    RUN_TEST(test_TrigLookup_cos);
    UNITY_END();
    return 0;
}
