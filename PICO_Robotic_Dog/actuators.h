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
  int initial_values[8] = {0, 180, 180, 0, 0, 180, 180, 0};
  int servo_values[8] = {0, 180, 180, 0, 0, 180, 180, 0};

  // SideKick actuator_struct definitions
  Array<int,8> pins(14, 15, 12, 13, 10, 11, 8, 9);
  ActuatorGroup<Servo,8> dog;

  void init()
  {
    dog.attach(pins);
    dog.writeAll(90);
  }

  void write()
  {
    for(int i=0; i<num_of_servos; i++)
    {
        dog.write(i, servo_values[i]);
    }
  }

}  // namespace actuators
