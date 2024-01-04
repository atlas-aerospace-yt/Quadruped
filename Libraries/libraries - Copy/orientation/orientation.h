#pragma once
#include "utility.h"
#include "quaternion.h"
#include "sk_math.h"
#include "vector.h"

namespace orientation{

  class orientation {
    private:
      Quat ori;

    public:
      Vec euler = {0.0f, 0.0f, 0.0f};

      orientation(Quat ori={1.0f, 0.0f, 0.0f, 0.0f}){
        this->ori = ori;
      }

      void update_gyro(Vec gyro, float dt){
        // Resolves orientation from gyroscope
        Quat rate = ori.fromAngularRate(gyro);
        ori += rate * dt;
        euler = ori.quatToVec();
      }

      void update_accel(Vec acc){
        // Estimates orientation from acceleration
        // https://uk.mathworks.com/matlabcentral/answers/160681-calculating-dual-quaternion-from-two-vectors
        // accel should be {x, y, z} where x, y = 0 and z = 9.81
        acc.normalize();
        Quat ori;

        if (acc.z > 0){
          ori.w = sqrt((acc.z + 1)/2);
          ori.i = -acc.y/sqrt(2*(acc.z+1));
          ori.j = acc.z/sqrt(2*(acc.z+1));
        } else {
          ori.w = -acc.y/sqrt(2*(1-acc.z));
          ori.i = sqrt((1-acc.z)/2);
          ori.k = acc.x/sqrt(2*(1-acc.z));
        }

        ori.normalize();

        euler = ori.quatToVec();
      }
  };

}
