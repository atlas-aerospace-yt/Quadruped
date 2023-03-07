#pragma once

//-----Internals------

#include "actuator_struct.h"
#include "utility.h"
//#include "internal_defs.h"

//-----Internals------

// Include your Actuator libraries here
#include <Servo.h>

//Include your Actuator libraries here

namespace actuators{

  // Globals can be defined here
  const int num_of_servos = 8;
  int initial_values[] = {0, 180, 180, 0, 0, 180, 180, 0};
  int servo_values[] = {0, 180, 180, 0, 0, 180, 180, 0};
  int pins[] = {14, 15, 12, 13, 10, 11, 8, 9};

  // SideKick actuator_struct definitions
  ActuatorGroup<Servo,8> dog;

  void init()
  {
    dog.attach(pins);
    dog.writeAll(90);
  }

  void write()
  {
    dog.write(initial_values);
  }

}  // namespace actuators
