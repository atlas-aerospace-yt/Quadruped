#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"
#include "sk_math.h"

#define INTERP_PTS 10.0f

namespace task
{
  float interp = 0;

  float x, y;

  subtask::Gait leg_bl(0);
  subtask::Gait leg_fr(2);
  subtask::Gait leg_br(4);
  subtask::Gait leg_fl(6);

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

    x = sk_math::LERP(leg_bl.get_prev_x(), leg_bl.get_x(), interp);
    y = sk_math::LERP(leg_bl.get_prev_y(), leg_bl.get_y(), interp);
    actuators::write_leg_bl(x, y);

    x = sk_math::LERP(leg_br.get_prev_x(), leg_br.get_x(), interp);
    y = sk_math::LERP(leg_br.get_prev_y(), leg_br.get_y(), interp);
    actuators::write_leg_br(x, y);

    x = sk_math::LERP(leg_fl.get_prev_x(), leg_fl.get_x(), interp);
    y = sk_math::LERP(leg_fl.get_prev_y(), leg_fl.get_y(), interp);
    actuators::write_leg_fl(x, y);

    x = sk_math::LERP(leg_fr.get_prev_x(), leg_fr.get_x(), interp);
    y = sk_math::LERP(leg_fr.get_prev_y(), leg_fr.get_y(), interp);
    actuators::write_leg_fr(x, y);

    PRINT("Interp: " + String(interp) + " Pos: " + String(x) + " , " + String(y))
    //PRINT("X: " + String(leg_fr.get_prev_x()) + " , " + leg_fr.get_x())
    //PRINT("Y: " + String(leg_fr.get_prev_y()) + " , " + leg_fr.get_y())
    PRINT("INDX: " + String(leg_fr.indx))

    GRAPH("LERP_X", x, TOP);
    GRAPH("LERP_Y", y, BOT);

    //GRAPH("Front Right", leg_fr.get_x(), TOP);
    //GRAPH("Front Right", leg_fr.get_y(), BOT);


    delay(10);

    if (interp < 1){
      interp += 1 / INTERP_PTS;
    } else {
      interp = 0;
      leg_br.update_forward();
      leg_bl.update_forward();
      leg_fr.update_forward();
      leg_fl.update_forward();
    }
  }
}
