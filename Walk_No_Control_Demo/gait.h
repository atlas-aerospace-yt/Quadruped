#pragma once

#include "sk_math.h"

#define SECTIONS 6

namespace gait {

  class Gait
  {
    float t;

    float x_lims[2];
    float y_lims[2];

    float interp_pts;

    bool forward = true;

    void update_x_and_y() {
      if (current_pt <= interp_pts * (SECTIONS-1)/SECTIONS) {
        // Go through min_x -> max_x @ max_y
        t = current_pt / (interp_pts * (SECTIONS-1)/SECTIONS);
        x = sk_math::LERP(x_lims[0], x_lims[1], t);
        y = y_lims[1];
      }
      else if (current_pt <= interp_pts * (SECTIONS*2-1)/(SECTIONS*2)) {
        // Go through max_x -> 1/2(max_x + min_x) & max_y -> min_y
        t = 1.0f - (interp_pts * (SECTIONS*2-1)/(SECTIONS*2) - current_pt) / (interp_pts * 1/(SECTIONS*2));
        x = sk_math::LERP(x_lims[1], 1/2 * (x_lims[0] + x_lims[1]), t);
        y = sk_math::SMOOTHLERP(y_lims[1], y_lims[0], t);
      }
      else if (current_pt <= interp_pts) {
        // Go through 1/2(max_x + min_x) -> min_x & min_y -> max_y
        t = 1.0f - (interp_pts - current_pt) / (interp_pts * 1/(SECTIONS*2));
        x = sk_math::LERP(1/2 * (x_lims[0] + x_lims[1]), x_lims[0],  t);
        y = sk_math::SMOOTHLERP(y_lims[0], y_lims[1], t);
      }
    }

  public:

    float x;
    float y;

    float current_pt = 0;

    Gait(int indx, int interp_pts, float min_x, float max_x, float min_y, float max_y)
    {
      if (0 <= indx < SECTIONS){
        current_pt = interp_pts/SECTIONS * indx;
      }

      this->interp_pts = interp_pts;

      this->x_lims[0] = min_x;
      this->x_lims[1] = max_x;

      this->y_lims[0] = min_y;
      this->y_lims[1] = max_y;
    }

    void update_forward(){
      // Increase the counter and if it exceeds the number of
      // interpolation points, it is reset to 0
      if (current_pt >= interp_pts){
        current_pt = 0;
      }
      current_pt ++;

      update_x_and_y();
    }

    void update_backward(){
      // Decrease the counter and if it falls below 0
      // reset to the number of interpolation points
      if (current_pt <= 0){
        current_pt = interp_pts;
      }
      current_pt --;

      update_x_and_y();
    }
  };
}
