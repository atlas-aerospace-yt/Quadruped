#pragma once

#include "utility.h"

// Other libraries
#include "vector.h"
#include "quaternion.h"

#define LENGTH 7.5f

#define WEIGHT 0.75

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

    return positions;
  }

  /*
  *
  * Orientation calculations are in this section of the
  * code.
  *
  */

  Quat ori_quat = {1.0f, 0.0f, 0.0f, 0.0f};
  Quat gyro_ori = {1.0f, 0.0f, 0.0f, 0.0f};

  Quat get_ori_from_accel(Vec accel){
    // Estimates orientation from acceleration
    // https://uk.mathworks.com/matlabcentral/answers/160681-calculating-dual-quaternion-from-two-vectors
    Vec glob_acc = {0, 0, 9.81};
    Vec u = accel * glob_acc / (accel * glob_acc).magnitude();
    float alpha = acos(accel.dot(glob_acc) / (accel.magnitude() * glob_acc.magnitude()));
    Quat q = {cos(alpha/2), sin(alpha/2)*u.x, sin(alpha/2)*u.y, sin(alpha/2) * u.z};
    q.normalize();

    return q;
  }

  void update_ori(Vec gyro, Vec accel, float dt){
    // Fuses the orientation from accel and gyro
    // https://courses.cs.washington.edu/courses/cse466/14au/labs/l4/madgwick_internal_report.pdf
    Quat acc_ori = get_ori_from_accel(accel);

    Quat gyro_rate = {0.0f, gyro.x, gyro.y, gyro.z};
    gyro_ori += gyro_ori * 0.5f * gyro_rate * dt;
    gyro_ori.normalize();

    ori_quat = gyro_ori * WEIGHT + acc_ori * (1-WEIGHT);
  }
}
