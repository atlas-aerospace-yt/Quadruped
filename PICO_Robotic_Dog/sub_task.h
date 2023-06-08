#pragma once

#include "utility.h"

#define LENGTH 7.5f

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

  float get_gamma(float value)
  {
    return -7.0f/10.0f * value + 180;
  }

  int* get_positions(float x, float y)
  {
    static int positions[2];

    float alpha = get_alpha(x, y);
    float beta = get_beta(alpha);
    float theta = get_theta(x, y);

    positions[0] = static_cast<int>(get_gamma(alpha + theta) - beta);
    positions[1] = static_cast<int>(alpha + theta);

    /*PRINT(" Alpha: ");
    PRINT(alpha);
    PRINT(" Beta: ");
    PRINT(get_beta(alpha));
    PRINT(" Theta: ");
    PRINT(theta);*/

    return positions;
  }

  /*
  *
  * Gait and walking motion calculations are in this section
  * of the code.
  *
  */

  class Gait
  {
    int res_one;
    int res_two;
    int indx;

    float min_x;
    float min_h;
    float max_x;
    float max_h;

    public:

      Gait(int indx, int min_x, int max_x, int max_h, int min_h, int res)
      {
        this->res_one = res * 3/4;
        this->res_two = res * 1/4;
        this->indx = indx;
        this->min_x = min_x;
        this->max_x = max_x;
        this->min_h = min_h;
        this->max_h = max_h;
      }

      void update_forward()
      {
        if (indx < (res_two + res_one))
        {
          indx ++;
        }
        else
        {
          indx = 0;
        }
      }

      float get_x()
      {
        if (indx < res_one)
        {
          return min_x + (max_x - min_x) / res_one * indx;
        }
        else
        {
          return max_x + (min_x - max_x) / res_two * (indx-res_one);
        }
      }

      float get_y()
      {
        if (indx > res_one)
        {
          return min_h;
        }
        return max_h;
      }

      int get_indx()
      {
        return indx;
      }
  };
}
