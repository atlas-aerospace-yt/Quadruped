/*
*
* Sort out the kinematics
*
*/

#pragma once

//-----Internals------

#include "actuator_struct.h"
#include "utility.h"
#include "sub_task.h"

//-----Internals------

// Include your Actuator libraries here
#include "lerp.h"
#include <Servo.h>

//Include your Actuator libraries here
#define MAX 180
#define MIN 0
#define LERP_PTS 100

namespace actuators{

  // Globals can be defined here
  int pins_fr[] = {15, 14};
  int pins_fl[] = {13, 12};
  int pins_br[] = {11, 10};
  int pins_bl[] = {9, 8};

  // SideKick actuator_struct definitions
  ActuatorGroup<Servo,2> leg_bl;
  ActuatorGroup<Servo,2> leg_br;
  ActuatorGroup<Servo,2> leg_fl;
  ActuatorGroup<Servo,2> leg_fr;

  //Lerp(0, 180);

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

    leg_bl.write(pos_forward);
    leg_br.write(pos_backward);
    leg_fr.write(pos_forward);
    leg_fl.write(pos_backward);

    delay(2500);
  }

  int servo_forward(int value){
    return static_cast<int>(36.0/19.0 * value);
  }

  int servo_backward(int value){
    return static_cast<int>(-36.0/19.0 * value + 180);
  }

  void write_leg_bl(float x, float y){
    int* pos;
    pos = subtask::get_positions(x, y);

    int values[] = {servo_forward(pos[0]), servo_backward(pos[1])};
    leg_bl.write(values);
  }

  void write_leg_br(float x, float y){
    int* pos;
    pos = subtask::get_positions(x, y);

    int values[] = {servo_backward(pos[0]), servo_forward(pos[1])};
    leg_br.write(values);
  }

  void write_leg_fr(float x, float y){
    int* pos;
    pos = subtask::get_positions(-x, y);

    int values[] = {servo_forward(pos[0]), servo_backward(pos[1])};
    leg_fr.write(values);
  }

  void write_leg_fl(float x, float y){
    int* pos;
    pos = subtask::get_positions(-x, y);

    int values[] = {servo_backward(pos[0]), servo_forward(pos[1])};
    leg_fl.write(values);
  }

}  // namespace actuators
