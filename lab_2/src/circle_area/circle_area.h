#pragma once
#include <chrono>
#include <iostream>
#include <pthread.h>
#include <vector>
#include "../threadwork/threadwork.h"
#include "../monte_carlo/monte_carlo.h"


inline double circle_area(const long long radius, const unsigned int k) {
    const auto start = std::chrono::high_resolution_clock::now();

    const long long points = radius * radius * radius * radius * k;
    const auto inside_points_count = monte_carlo_circle_point_count(static_cast<double>(radius), points);
    const long long squareArea = (2 * radius) * (2 * radius);
    const auto area = (static_cast<double>(inside_points_count) / static_cast<double>(points)) * static_cast<double>(squareArea);

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Микросекунд с 1 потоком: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    return area;
}

inline double circle_area_multi_thread(const long long radius, const unsigned int k, const unsigned int threads) {
    std::vector<ThreadWork> work;
    std::vector<pthread_t> threads_array(k);

    const long long points = radius * radius * radius * radius * threads;
    for (size_t i = 0; i < k; ++i) {
        work.emplace_back(radius, points / k, 0);
    }

    const auto start = std::chrono::high_resolution_clock::now();

    //run threads
    for (size_t i = 0; i < k; ++i) {
        pthread_t t;
        if (pthread_create(&t, nullptr, threadRoutine, &work[i]) != 0) {
            std::cerr << "Failed to create thread" << std::endl;
            return 1;
        }
        threads_array[i] = t;
    }

    //waiting all threads
    for (size_t i = 0; i < k; ++i) {
        pthread_join(threads_array[i], nullptr);
    }

    //merging all parts
    long long total_points = 0;
    for (const auto& w : work) {
        total_points += w.inside_points_count;
    }

    const long long squareArea = (2 * radius) * (2 * radius);
    const auto area = (static_cast<double>(total_points) / static_cast<double>(points)) * static_cast<double>(squareArea);

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Микросекунд с " << k << " потоками: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

    return area;
}