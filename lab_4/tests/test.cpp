#include <gtest/gtest.h>
#include <random>
#include "../src/f1.h"
#include "../src/f2.h"

TEST(EuclidGcdTests, ShouldFindGcdCorrectly){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> rand(0,100);
    int num1 = rand(rng);
    int num2 = rand(rng);

    auto result = GcdEuclid(num1, num2);

    EXPECT_EQ(result, std::gcd(num1, num2));
}

TEST(GcdTests, ShouldFindGcdCorrectly){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> rand(0,100);
    int num1 = rand(rng);
    int num2 = rand(rng);

    auto result = Gcd(num1, num2);

    EXPECT_EQ(result, std::gcd(num1, num2));
}

TEST(PiTests, ShouldCalculatePiCorrectlyWithLeibniz){
    EXPECT_NEAR(std::numbers::pi, PiLeibniz(1e6), 1e-5);
}

TEST(PiTests, ShouldCalculatePiCorrectlyWithValles){
    EXPECT_NEAR(std::numbers::pi, PiVallis(1e6), 3e-4);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}