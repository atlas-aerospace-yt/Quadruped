#pragma once

#include "utility.h"

#define LENGTH 7.5f
#define GEAR_RATIO 3/2

namespace subtask {

  /*
  *
  * Gait and walking motion calculations are in this section
  * of the code.
  *
  */

  const int gait[] = {{0, 14}, {2, 14}, {4, 14}, {0, 10}};

  int stats[] = {0, 2, 0, 2};
  int positions[8];

  void update_gait()
  {
    for (int i=0; i<sizeof(stats); i++)
    {
      stats[i] ++;
      if (stats[i] > sizeof(gait)-1)
      {
        stats[i] = 0;
      }
    }
  }

  void get_positions()
  {
    for (int i=0; i<sizeof(stats); i++)
    {
      for (int j=0; j<sizeof(stats[i]); i++)
      {

      }
    }
  }
  /*
  *
  * Inverse kinematic calculations are in this section of
  * the code.
  *
  */

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
    float alpha = get_alpha(-x, y);
    float theta = get_theta(-x, y);
    float hip = GEAR_RATIO * (alpha + theta);

    return hip < 0 ? 0 : hip;
  }

  // wrapper function to get the knee_output
  float get_knee_output(float x, float y)
  {
    float alpha = get_alpha(-x, y);
    float beta = get_beta(alpha);
    float theta = get_theta(-x, y);
    float u = 180 - (1/2 * (theta + alpha) + beta);
    float knee = GEAR_RATIO * u;

    return knee < 0 ? 0 : knee;
  }
}
