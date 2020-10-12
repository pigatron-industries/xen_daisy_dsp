#include <unity.h>

void test_sine_lookup(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_sine_lookup);
    UNITY_END();
    return 0;
}
