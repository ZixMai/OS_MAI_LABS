#include <iostream>
#include <thread>
#include "src/circle_area/circle_area.h"

int main(int argv, char** argc) {
    const unsigned int n = std::thread::hardware_concurrency();
    std::cout << "Рекомендуемое количество потоков: " << n << std::endl;

    long long radius;
    std::cin >> radius;

    const auto area = circle_area(radius, n);
    std::cout << "Площадь: " << area << std::endl;

    double area_multi_thread = circle_area_multi_thread(radius, 2);
    std::cout << "Площадь: " << area_multi_thread << std::endl;

    area_multi_thread = circle_area_multi_thread(radius, 4);
    std::cout << "Площадь: " << area_multi_thread << std::endl;

    area_multi_thread = circle_area_multi_thread(radius, 8);
    std::cout << "Площадь: " << area_multi_thread << std::endl;

    area_multi_thread = circle_area_multi_thread(radius, 16);
    std::cout << "Площадь: " << area_multi_thread << std::endl;
}

