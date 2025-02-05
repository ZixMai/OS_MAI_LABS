#pragma once
#include <random>

inline long long monte_carlo_circle_point_count(const double radius, const long long point_count) {
    long long insideCircle = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution dist(-radius, radius);

    for (int i = 0; i < point_count; i++) {
        double x = dist(gen);
        double y = dist(gen);

        if (x * x + y * y <= radius * radius) {
            insideCircle++;
        }
    }
    return insideCircle;
}

