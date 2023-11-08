#pragma once
//-----Internals------
#include "utility.h"
#include "sensor_struct.h"
#include "sub_task.h"
//-----Internals------

// Include your sensor libraries here
#include "BMI088.h"
#include "Wire.h"

#define X_OFFSET 0.34f
#define Y_OFFSET -0.06f
#define Z_OFFSET 0.21f

namespace sensors {

  BMI088 bmi088(0x18, 0x68);

  float x=0;
  float y=0;
  float z=0;

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

    gx += X_OFFSET;
    gy += Y_OFFSET;
    gz += Z_OFFSET;

    Vec gyro = {gx * PI / 180.0f, gy * PI / 180.0f, gz * PI / 180.0f};
    subtask::update_ori(gyro, dt);

    x += gx;
    y += gy;
    z += gz;
    i ++;

    //GRAPH("x_dot", gx, BOT);
    //GRAPH("y_dot", gy, BOT);
    //GRAPH("z_dot", gz, BOT);
  }

}  // namespace sensors
