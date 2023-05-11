#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"

#define NUM_OF_LOOPS 10
#define NUM_OF_LEGS 4

#define UP_HEIGHT 15
#define DOWN_HEIGHT 8

namespace task
{
  float hip;
  float knee;

  void Setup()
  {
    actuators::init();
  }

  void ActuatorTest()
  {
  }

  void Calibration()
  {
  }

  void Loop()
  {
    //
    // A walking demo without any forms of control.
    //

    for (int i=15; i>10; i--){
      knee = subtask::get_knee_output(0, i);
      hip = subtask::get_hip_output(0, i);

      actuators::hip_one.write(subtask::get_servo_angle_backward(hip));
      actuators::knee_one.write(subtask::get_servo_angle_forward(knee));
      actuators::hip_two.write(subtask::get_servo_angle_forward(hip));
      actuators::knee_two.write(subtask::get_servo_angle_backward(knee));

      delay(100);
    }

    for (int i=10; i<15; i++){
      knee = subtask::get_knee_output(0, i);
      hip = subtask::get_hip_output(0, i);

      actuators::hip_one.write(subtask::get_servo_angle_backward(hip));
      actuators::knee_one.write(subtask::get_servo_angle_forward(knee));
      actuators::hip_two.write(subtask::get_servo_angle_forward(hip));
      actuators::knee_two.write(subtask::get_servo_angle_backward(knee));

      delay(100);
    }
  }
}
