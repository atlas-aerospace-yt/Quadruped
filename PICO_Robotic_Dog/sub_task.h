#pragma once

#include "utility.h"

#define LENGTH 0.075f
#define GEAR_RATIO 3/2

namespace subtask {
  // mathematical functions for leg position
  float get_alpha(float x, float y)
  {
    float length_new = 0.5f * sqrt(sq(x) + sq(y));
    return acos(length_new/LENGTH) * 180.0f/PI;
  }

  float get_beta(float alpha)
  {
    return 180 - 2 * alpha;
  }

  float get_theta(float x, float y)
  {
    return atan(x/y) * 180.0f/PI;
  }

  // wrapper function to get the hip_output
  float get_hip_output(float x, float y)
  {
    float alpha = get_alpha(x, y);
    float theta = get_theta(x, y);

    return GEAR_RATIO * (alpha + theta);
  }

  // wrapper function to get the knee_output
  float get_knee_output(float x, float y)
  {
    float alpha = get_alpha(x, y);
    float beta = get_beta(alpha);
    float theta = get_theta(x, y);
    float u = 180 - (1/2 * theta + beta);

    return GEAR_RATIO * u;
  }
}
