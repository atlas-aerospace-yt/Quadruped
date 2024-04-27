#pragma once

#include "utility.h"
#include "sidekick.h"

#include "quaternion.h"
#include "vector.h"

#include "control.h"

// Units for lenfth are cm
#define LENGTH 7.5f
#define BODY_LENGTH 30.0f
#define BODY_WIDTH 15.0f

#define MIN_CONTROL_X -1.0f
#define MAX_CONTROL_X 1.0f

#define MIN_CONTROL_Y -2.0f
#define MAX_CONTROL_Y 2.0f

namespace subtask {
  /*
  *
  * Inverse kinematic calculations are in this section of
  * the code.
  *
  */

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
    return -2.0f/3.0f * value + 180;
  }

  float* get_positions(float x, float y)
  {
    static float positions[2];

    float alpha = get_alpha(x, y);
    float beta = get_beta(alpha);
    float theta = get_theta(x, y);

    positions[0] = static_cast<int>(get_gamma(alpha + theta) - beta);
    positions[1] = static_cast<int>(alpha + theta);

    return positions;
  }

  /*
  * General functions
  */

  Quat ori_quat = {1.0f, 0.0f, 0.0f, 0.0f};

  PID<float> y_axis(1.2f, 0.5f, 0.001f);
  PID<float> x_axis(1.2f, 0.5f, 0.001f);

  float init(){
      y_axis.setlims(2*MIN_CONTROL_Y/BODY_LENGTH, 2*MAX_CONTROL_Y/BODY_LENGTH);
      x_axis.setlims(2*MIN_CONTROL_X/BODY_WIDTH, 2*MAX_CONTROL_X/BODY_WIDTH);
  }

  float get_dt(){
    sk_timer.stop();
    float dt = sk_timer.deltaT();
    sk_timer.start();
    return dt;
  }

  void update_ori(Vec gyro, float dt)
  {
    Quat gyro_rate = {0.0f, gyro.x, gyro.y, gyro.z};
    ori_quat += ori_quat * 0.5f * gyro_rate * dt;
    ori_quat.normalize();
  }

  // This returns an array and so uses a pointer
  float* control_loop(Vec ori, float dt)
  {
    // Add to front
    static float output[2];
    output[0] = BODY_LENGTH / 2 * sin(y_axis.update(ori.y, dt));
    output[1] = BODY_WIDTH / 2 * sin(x_axis.update(ori.z, dt));
    return output;
  }
}  // namespace subtask
