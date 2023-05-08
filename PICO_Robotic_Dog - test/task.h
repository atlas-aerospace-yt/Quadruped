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

    for (int i=3; i>-3; i--){
      knee = subtask::get_knee_output(i, 9);
      hip = subtask::get_hip_output(i, 9);

      actuators::hip.write(hip);
      actuators::knee.write(knee);

      delay(50);
    }

    for (int i=-3; i<3; i++){
      knee = subtask::get_knee_output(i, 9);
      hip = subtask::get_hip_output(i, 9);

      actuators::hip.write(hip);
      actuators::knee.write(knee);

      delay(50);
    }
  }
}
