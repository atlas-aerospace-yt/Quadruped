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
#define INTERP_PTS 100

namespace actuators{

  // Globals can be defined here
  Servo hip;
  Servo knee;

  void init()
  {
    hip.attach(12);
    knee.attach(13);
  }

}
