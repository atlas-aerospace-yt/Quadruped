#pragma once

#include "utility.h"

#define LENGTH 7.5f
#define GEAR_RATIO 2

#define MAX 180
#define MIN 0

namespace subtask {

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
  int get_hip_output(float x, float y)
  {
    float alpha = get_alpha(x, y);
    float theta = get_theta(x, y);
    float hip = GEAR_RATIO * (alpha + theta);

    return hip < MIN ? MIN : hip > MAX ? MAX : hip;
  }

  // wrapper function to get the knee_output
  int get_knee_output(float x, float y)
  {
    float alpha = get_alpha(x, y);
    float beta = get_beta(alpha);
    float theta = get_theta(x, y);
    float u = 180 - ((theta + alpha) + beta);
    float knee = GEAR_RATIO * u;

    return knee < MIN ? MIN : knee > MAX ? MAX : knee;
  }

  /*
  *
  * Gait and walking motion calculations are in this section
  * of the code.
  *
  */

  int front_gait[][2] = {{-5, 14}, {-2, 14}, {0, 14}, {0, 8}};
  int back_gait[][2] = {{-5, 12}, {-2, 12}, {0, 12}, {0, 8}};
  int stats[] = {2, 0, 0, 2};
  int positions[8];

  void update_gait()
  {
    for (int i=0; i<4; i++)
    {
      stats[i] ++;
      if (stats[i] > 3)
      {
        stats[i] = 0;
      }
    }
  }

  void get_positions()
  {
    for (int i=0; i<4; i++)
    {
      int stat = stats[i];

      int hip_indx = 2 * i;
      int knee_indx = 2 * i + 1;

      if (i < 2)
      {
        positions[hip_indx] = get_hip_output(front_gait[stat][0], front_gait[stat][1]);
        positions[knee_indx] = get_knee_output(front_gait[stat][0], front_gait[stat][1]);
      }
      else
      {
        positions[hip_indx] = get_hip_output(back_gait[stat][0], back_gait[stat][1]);
        positions[knee_indx] = get_knee_output(back_gait[stat][0], back_gait[stat][1]);
      }
    }
  }
}
