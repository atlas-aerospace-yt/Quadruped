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
  int pins_bl[] = {15, 14};
  int pins_br[] = {13, 12};
  int pins_fl[] = {11, 10};
  int pins_fr[] = {9, 8};

  // SideKick actuator_struct definitions
  ActuatorGroup<Servo,2> leg_bl;
  ActuatorGroup<Servo,2> leg_br;
  ActuatorGroup<Servo,2> leg_fl;
  ActuatorGroup<Servo,2> leg_fr;

  void init()
  {
    leg_bl.attach(pins_bl);
    leg_br.attach(pins_br);
    leg_fl.attach(pins_fl);
    leg_fr.attach(pins_fr);
  }

  void test()
  {
    int pos_forward[] = {0, 180};
    int pos_backward[] = {180, 0};

    leg_bl.write(pos_backward);
    leg_br.write(pos_forward);
    leg_fl.write(pos_backward);
    leg_fr.write(pos_forward);

    delay(2500);
  }
}  // namespace actuators
