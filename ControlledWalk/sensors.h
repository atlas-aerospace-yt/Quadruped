#pragma once
//-----Internals------
#include "utility.h"
#include "sensor_struct.h"
#include "sub_task.h"
//-----Internals------

// Include your sensor libraries here
#include "BMI088.h"
#include "Wire.h"

namespace sensors {

  BMI088 bmi088(0x18, 0x68);

  float x_offset=0;
  float y_offset=0;
  float z_offset=0;

  unsigned long i = 0;

  void init() {
    Wire.begin();

    while (1){
      if (bmi088.isConnection()) {
        bmi088.initialize();
        PRINTLN("BMI088 is connected");
        break;
      } else {
        PRINTLN("BMI088 is not connected");
      }
    }
  }

  void update(float dt) {
    float gx, gy, gz;

    bmi088.getGyroscope(&gx, &gy, &gz);

    gx += x_offset;
    gy += y_offset;
    gz += z_offset;

    Vec gyro = {gx * PI / 180.0f, gy * PI / 180.0f, gz * PI / 180.0f};
    subtask::update_ori(gyro, dt);
  }

  void calibrate() {
    float gx, gy, gz;
    bmi088.getGyroscope(&gx, &gy, &gz);

    x_offset -= gx;
    y_offset -= gy;
    z_offset -= gz;
    i ++;
  }

  void end_calibration() {
    x_offset = float(x_offset/i);
    y_offset = float(y_offset/i);
    z_offset = float(z_offset/i);
  }

}  // namespace sensors
