#pragma once

//-----Internals------

#include "actuator_struct.h"
#include "utility.h"
//#include "internal_defs.h"

//-----Internals------

// Include your Actuator libraries here
#include "lerp.h"
#include <Servo.h>

//Include your Actuator libraries here

namespace actuators{

  // Globals can be defined here
  Servo hip_one;
  Servo knee_one;
  Servo hip_two;
  Servo knee_two;

  void init()
  {
    hip_one.attach(12);
    knee_one.attach(13);
    hip_two.attach(10);
    knee_two.attach(11);
  }

}
