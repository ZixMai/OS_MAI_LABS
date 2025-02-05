#pragma once

struct ThreadWork {
  double radius;
  long long points_count;
  long long inside_points_count;
};

void* threadRoutine(void *arg);
