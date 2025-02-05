#include "threadwork.h"
#include "../monte_carlo/monte_carlo.h"

void* threadRoutine(void *arg) {
    const auto args = static_cast<ThreadWork *>(arg);
    args->inside_points_count = monte_carlo_circle_point_count(args->radius, args->points_count);
    return nullptr;
}
