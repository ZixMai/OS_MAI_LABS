#include <fstream>
#include <filesystem>
#include <chrono>
#include "../src/circle_area/circle_area.h"
#include "gtest/gtest.h";

TEST(BASE_TEST, SHOULD_DONE_SUCCESFULLY_ONE_THREAD) {
    constexpr double radius = 20;
    const auto area = circle_area(radius, 16);

    EXPECT_NEAR(area, 1257, 0.5);
}

TEST(BASE_TEST, SHOULD_DONE_SUCCESFULLY_16_THREADS) {
    constexpr double radius = 20;
    const double area_multi_thread = circle_area_multi_thread(radius, 16);

    EXPECT_NEAR(area_multi_thread, 1257, 0.5);
}

TEST(BASE_TEST, SHOULD_FAIL) {
    constexpr double radius = 1;
    const auto area = circle_area(radius, 16);

    EXPECT_NEAR(area, 3.14, 0.5);
}

TEST(BASE_TEST, SHOULD_WORK_FASTER_WITH_SEVERAL_THREADS) {
    constexpr double radius = 20;

    const auto start_one_thread = std::chrono::high_resolution_clock::now();
    circle_area(radius, 16);
    const auto end_one_thread = std::chrono::high_resolution_clock::now();

    const auto start_16_threads = std::chrono::high_resolution_clock::now();
    circle_area_multi_thread(radius, 16);
    const auto end_16_threads = std::chrono::high_resolution_clock::now();

    EXPECT_TRUE(
        std::chrono::duration_cast<std::chrono::microseconds>(end_one_thread - start_one_thread).count() >
        std::chrono::duration_cast<std::chrono::microseconds>(end_16_threads - start_16_threads).count()
    );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}