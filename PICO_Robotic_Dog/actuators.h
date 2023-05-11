/*
*
* Sort out the kinematics
*
*/

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
#define MAX 180
#define MIN 0

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
    leg_fr.attach(pins_fl);
    leg_fl.attach(pins_fr);
  }

  void test()
  {
    int pos_forward[] = {0, 180};
    int pos_backward[] = {180, 0};

    leg_bl.write(pos_backward);
    leg_br.write(pos_forward);
    leg_fr.write(pos_backward);
    leg_fl.write(pos_forward);

    delay(2500);
  }

  int servo_forward(int value){
    //return static_cast<int>(36.0/19.0 * value);
    return value;
  }

  int servo_backward(int value){
    //return static_cast<int>(-36.0/19.0 * value + 180);
    return 180 - value;
  }

  void write_leg_bl(int hip, int knee){
    int pos[] = {servo_backward(knee), servo_forward(hip)};
    PRINT("Positions: ")
    PRINT(hip)
    PRINT(", ")
    PRINT(knee)

    PRINT("Output for pos[0]: ")
    PRINT(pos[0])

    PRINT("Output for pos[1]: ")
    PRINT(pos[1])
    leg_bl.write(pos);
  }

  void write_leg_br(int hip, int knee){
    int pos[] = {servo_forward(knee), servo_backward(hip)};
    leg_br.write(pos);
  }

  void write_leg_fr(int hip, int knee){
    int pos[] = {servo_backward(knee), servo_forward(hip)};
    leg_fr.write(pos);
  }

  void write_leg_fl(int hip, int knee){
    int pos[] = {servo_forward(knee), servo_backward(hip)};
    leg_fl.write(pos);
  }

}  // namespace actuators
