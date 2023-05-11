#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"

namespace task
{

  bool inc = true;
  int i = 13;
  int min = 12;
  int max = 15;

  void Setup()
  {
    actuators::init();
  }

  void ActuatorTest()
  {
    actuators::test();
  }

  void Calibration()
  {
  }

  void Loop()
  {
    //
    // A walking demo without any forms of control.
    //

    if (i >= max || i <= min){
      inc = !inc;
    }

    if (inc){
      i ++;
    }
    else {
      i --;
    }

    int hip = subtask::get_hip_output(0, i);
    int knee = subtask::get_knee_output(0, i);

    actuators::write_leg_bl(hip, knee);
    actuators::write_leg_br(hip, knee);
    actuators::write_leg_fl(hip, knee);
    actuators::write_leg_fr(hip, knee);

    delay(250);
  }
}
