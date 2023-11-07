#pragma once
//-----Internals------
#include "utility.h"
#include "sensor_struct.h"
//-----Internals------

// Include your sensor libraries here
#include "bmi088.h"
#include "vector.h"

#include "skServo.h"

namespace sensors {

  Imu bmi;

  void init() {
    bmi.begin();
  }

  void update() {
    //Vec data = bmi.getGyro();

    //GRAPH("X", data.x, TOP);
    //GRAPH("Y", data.y, TOP);
    //GRAPH("Z", data.z, TOP);
    PRINTLN("Hello world!");
  }

}  // namespace sensors
