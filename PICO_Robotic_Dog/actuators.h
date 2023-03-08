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
  int initial_values[] = {60, 120, 120, 60, 60, 120, 120, 60};
  int servo_values[] = {50, 240, 240, 50, 50, 240, 240, 50};
  int pins[] = {14, 15, 12, 13, 10, 11, 8, 9};
  int pos;

  // SideKick actuator_struct definitions
  ActuatorGroup<Servo,8> dog;

  void init()
  {
    dog.attach(pins);
    dog.writeAll(90);
  }


  void write()
  {
    for (pos = 50; pos <= 240; pos += 1)
    {
      dog.writeAll(pos);
      delay(15);
      PRINT(pos);
      END_LOG;
    }
    for (pos = 240; pos >= 50; pos -= 1)
    {
      dog.writeAll(pos);
      delay(15);
      PRINT(pos);
      END_LOG;
    }
  }

}  // namespace actuators
