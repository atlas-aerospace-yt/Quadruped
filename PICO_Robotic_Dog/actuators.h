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
  int pos;

  Servo hip;
  Servo knee;

  // SideKick actuator_struct definitions
  ActuatorGroup<Servo,4> dog;

  void init()
  {
    dog.attach(pins);
  }

  void write_leg()
  {

  }

  void write(int values[])
  {
    for (int i=0; i<8; i++)
    {
      if (initial_values[i] > 0)
      {
        servo_values[i] = 180 - values[i];
      }
      else
      {
        servo_values[i] = values[i];
      }
    }
    for (int i=0; i<8; i++)
    {
      PRINT(servo_values[i]);
      PRINT(" , ");
    }
    END_LOG;

    dog.write(servo_values);
  }
}  // namespace actuators
