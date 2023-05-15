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
    return -6.0f/10.0f * value + 180;
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
    int res = 0;
    int indx = 0;

    float min_x = 0;
    float min_h = 0;
    float max_x = 0;
    float max_h = 0;

    public:

      Gait(int indx, int min_x, int max_x, int max_h, int min_h, int res)
      {
        this->res = res-2;
        this->indx = indx;
        this->min_x = min_x;
        this->max_x = max_x;
        this->min_h = min_h;
        this->max_h = max_h;
      }

      void update_forward()
      {
        indx ++;
        if (indx > res + 1)
        {
          delay(100);
          indx = 0;
        }
      }

      void update_backward()
      {
        indx --;
        if (indx < 0)
        {
          indx = res;
        }
      }

      float get_x()
      {
        if (indx > res)
        {
          return 0;
        }

        return min_x + (max_x - min_x) / res * indx;
      }

      float get_y()
      {
        if (indx > res)
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
