#include "Unity-master/src/unity.h"
#include "stdio.h"

void setUp(void) {}    /* Is run before every test, put unit init calls here. */
void tearDown(void) {} /* Is run after every test, put unit clean-up calls here. */

int add(int a, int b) {
    return a + b;
}

void test_add() {
    TEST_ASSERT_EQUAL_INT(5, add(2, 3));
    TEST_ASSERT_EQUAL_INT(-1, add(2, -3));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_add);
    return UNITY_END();
}
