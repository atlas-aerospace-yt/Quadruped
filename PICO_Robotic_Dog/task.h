#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"

namespace task
{

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

    //PRINT("Walking...")
    //subtask::update_gait();
    //subtask::get_positions();
    //actuators::write(subtask::positions);

    delay(150);
  }
}
