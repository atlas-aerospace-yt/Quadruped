#pragma once
//-----Internals------
#include "utility.h"
#include "sensor_struct.h"
//-----Internals------

// Include your sensor libraries here
#include "BMI088.h"
#include "vector.h"

#define G 9.81

namespace sensors {

  BMI088 bmi088(0x18, 0x68);

  Vec gyro_offset = {0.0f, 0.0f, 0.0f};
  Vec accel_offset = {0.0f, 0.0f, 0.0f};

  float accel_ratio = G;

  void init() {
    Wire.begin();

    while (1) {
      if (bmi088.isConnection()) {
        bmi088.initialize();
        PRINT("BMI088 is connected");
        break;
      } else {
        PRINT("BMI088 is not connected");
        END_LOG;
      }
    }
  }

  Vec get_accel() {
    Vec acc;
    bmi088.getAcceleration(&acc.x, &acc.y, &acc.z);

    return acc * accel_ratio;
  }

  Vec get_gyro() {
    Vec gyro;
    bmi088.getGyroscope(&gyro.x, &gyro.y, &gyro.z);

    gyro.x += gyro_offset.x;
    gyro.y += gyro_offset.y;
    gyro.z += gyro_offset.z;

    return gyro * PI / 180.0f;
  }

  Vec get_raw_accel() {
    Vec acc;
    bmi088.getAcceleration(&acc.x, &acc.y, &acc.z);
    return acc;
  }

  Vec get_raw_gyro() {
    Vec gyro;
    bmi088.getGyroscope(&gyro.x, &gyro.y, &gyro.z);
    return gyro;
  }
}  // namespace sensors
