#include <unity.h>

#define RECT_PACK_H_IMPL
#include "rect_pack.h"

void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

void test_rect_pack_uniform_paging() {
    
    rect_r rects[100];

    for(int i = 0; i < sizeof(rects)/sizeof(rect_r); i++) {
        rects[i].id = i;
        rects[i].w = i+1;
        rects[i].h = i+1;
    }

    TEST_ASSERT_TRUE(rect_pack(512, 512, true, rects, sizeof(rects)/sizeof(rect_r)));
}

void test_rect_pack_one_rect_per_page_paging() {
    
    rect_r rects[] = {
        {.id = 0, .w = 6, .h = 7},
        {.id = 1, .w = 8, .h = 7},
        {.id = 2, .w = 8, .h = 9},
        {.id = 3, .w = 10, .h = 9},
    };

    int n = sizeof(rects)/sizeof(rect_r);

    TEST_ASSERT_TRUE(rect_pack(10, 10, true, rects, n));
    
    for(int i = 0; i < n; i++) {
        TEST_ASSERT_TRUE(rects[i].info.packed);
        TEST_ASSERT_EQUAL(rects[i].info.page, i);
    }
}

void test_rect_pack_fill() {
    rect_r rects[100];

    for(int i = 0; i < sizeof(rects)/sizeof(rect_r); i++) {
        rects[i].id = i;
        rects[i].w = 1;
        rects[i].h = 1;
    }

    TEST_ASSERT_TRUE(rect_pack(10, 10, false, rects, sizeof(rects)/sizeof(rect_r)));
    
    for(int i = 0; i < sizeof(rects)/sizeof(rect_r); i++) {
        TEST_ASSERT_TRUE(rects[i].info.packed);
        TEST_ASSERT_EQUAL(rects[i].info.page, 0);
    }
}

void test_rect_pack_no_paging() {
    rect_r rects[] = {
        {.id = 0, .w = 6, .h = 7},
        {.id = 1, .w = 8, .h = 7},
        {.id = 2, .w = 8, .h = 9},
        {.id = 3, .w = 10, .h = 9},
    };

    TEST_ASSERT_FALSE(rect_pack(10, 10, false, rects, sizeof(rects)/sizeof(rect_r)));

    TEST_ASSERT_TRUE(rects[0].info.packed);
    TEST_ASSERT_FALSE(rects[1].info.packed);
    TEST_ASSERT_FALSE(rects[2].info.packed);
    TEST_ASSERT_FALSE(rects[3].info.packed);
}

void test_rect_pack_fail_paging() {

    rect_r rects[2];

    rects[0].id = 0;
    rects[0].w = 900;
    rects[0].h = 900;

    rects[1].id = 1;
    rects[1].w = 1100;
    rects[1].h = 1100;

    TEST_ASSERT_FALSE(rect_pack(1000, 1000, true, rects, sizeof(rects)/sizeof(rect_r)));
    TEST_ASSERT_FALSE(rects[0].info.packed);
    TEST_ASSERT_TRUE(rects[1].info.packed);
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_rect_pack_uniform_paging);
    RUN_TEST(test_rect_pack_fail_paging);
    RUN_TEST(test_rect_pack_one_rect_per_page_paging);
    RUN_TEST(test_rect_pack_fill);

    return UNITY_END();
}