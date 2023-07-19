#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"
#include "sk_math.h"

// My libraries
#include "gait.h"

// interp_pts, min_x, max_x, min_y, max_y
#define GAIT 100.0f, -3.0f, 3.0f, 12.0f, 14.5f

namespace task
{

  gait::Gait leg_bl(0, GAIT);
  gait::Gait leg_fr(1, GAIT);
  gait::Gait leg_br(2, GAIT);
  gait::Gait leg_fl(3, GAIT);

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
    actuators::write_leg_fl(leg_fl.x, leg_fl.y);
    actuators::write_leg_fr(leg_fr.x, leg_fr.y);
    actuators::write_leg_bl(leg_bl.x, leg_bl.y);
    actuators::write_leg_br(leg_br.x, leg_br.y);

    leg_fl.update_forward();
    leg_fr.update_forward();
    leg_bl.update_forward();
    leg_br.update_forward();

    PRINT("Current point: " + String(leg_bl.current_pt));

    GRAPH("FrontLeftX", leg_fl.x, TOP);
    GRAPH("FrontRightX", leg_fr.x, TOP);
    GRAPH("BackLeftX", leg_bl.x, TOP);
    GRAPH("BackRightX", leg_br.x, TOP)

    GRAPH("FrontLeftY", leg_fl.y, BOT);
    GRAPH("FrontRightY", leg_fr.y, BOT);
    GRAPH("BackLeftY", leg_bl.y, BOT);
    GRAPH("BackRightY", leg_br.y, BOT)

    delay(10);
  }
}
