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
    int x[4] = {0, 2, 0 , -2};
    int y[4] = {14, 14, 10, 10};
    int indx = 0;

    public:

      Gait(int indx){
        this->indx = indx;
      }

      void update_forward(){
        indx ++;
        if (indx > 3){
          indx = 0;
        }
      }

      void update_backward(){
        indx --;
        if (indx < 0){
          indx = 3;
        }
      }

      int get_x(){
        return x[indx];
      }

      int get_y(){
        return y[indx];
      }

      int get_indx(){
        return indx;
      }
  };
}
