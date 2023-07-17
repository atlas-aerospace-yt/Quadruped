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
    float x[] = {-3, -2, -1, 0, 1, 2, 3, 0};
    float y[] = {14.5, 14.5, 14.5, 14.5, 14.5, 14.5, 14.5, 12};

    public:

      int indx;

      Gait(int indx)
      {
        this->indx = indx;
      }

      void update_forward()
      {
        if (indx < 3) {
          indx ++;
        } else {
          indx = 0;
        }
      }

      float get_x(){
        return x[indx];
      }

      float get_prev_x(){
        if (indx > 0){
          return x[indx-1];
        } else {
          return x[3];
        }
      }

      float get_y(){
        return y[indx];
      }

      float get_prev_y(){
        if (indx > 0){
          return y[indx-1];
        } else {
          return y[3];
        }
      }
  };
}
