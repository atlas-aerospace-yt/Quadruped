#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"

namespace task
{
  subtask::Gait leg_br(0);
  subtask::Gait leg_fl(1);
  subtask::Gait leg_bl(2);
  subtask::Gait leg_fr(3);

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
    leg_br.update_forward();
    leg_bl.update_forward();
    leg_fr.update_forward();
    leg_fl.update_forward();

    actuators::write_leg_bl(leg_bl.get_x(), leg_bl.get_y());
    actuators::write_leg_br(leg_br.get_x(), leg_br.get_y());
    actuators::write_leg_fl(leg_fl.get_x(), leg_fl.get_y());
    actuators::write_leg_fr(leg_fr.get_x(), leg_fr.get_y());

    delay(250);
  }
}
