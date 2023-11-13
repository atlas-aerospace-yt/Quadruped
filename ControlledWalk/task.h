#pragma once

//-----Internals------
#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"
//-----Internals------

#include "gait.h"
// Tasks go here-- this keeps the main file clean and focused on the "flow" of tasks
// Our general functions will be defined here things like our main loops
// Long sections of code or repeated code loops can be moved to sub_task.h
#define NORM_HEIGHT 13.0f
#define GAIT 200.0f, -3.0f, 3.0f, 6.0f, NORM_HEIGHT

// The functions in place here can be changed to suit your needs
// The ones listed here serve as inspiration--feel free to change them as you need -- but remember to change your Tasks in main.h
namespace task
{

    // Globals can be defined here
    gait::Gait leg_bl(0, GAIT);
    gait::Gait leg_fr(1, GAIT);
    gait::Gait leg_br(2, GAIT);
    gait::Gait leg_fl(3, GAIT);

    // Can be used for code that only runs once
    // This can also be run multiple times by changing the code flow in main.h

    void Setup()
    {
      actuators::init();
      sensors::init();
    }

    // Can be used to automatically test actuators
    // Very useful for quick plug and play testing
    void ActuatorTest()
    {
      PRINTLN("Calibrating...");
      float positions[8] = {0.0f, 15.0f,
                            0.0f, 15.0f,
                            0.0f, 15.0f,
                            0.0f, 15.0f};
      actuators::write(positions);
      delay(2500);
    }

    // Can be used to print sensor values and any other required calibration
    void Calibration()
    {
      PRINTLN("Calibrating...");
      delay(2500);
      sk_timer.start();
      while (sk_timer.getTime() < 10.0f){
        sensors::calibrate();
      }
      sensors::end_calibration();

      sk_timer.start();
      sk_timer.stop();
    }

    // Code that loops
    void Loop()
    {
      float dt = subtask::get_dt();
      sensors::update(dt);
      Vec ori = subtask::ori_quat.toEuler();

      float positions[8];

      positions[0] = leg_br.x;
      positions[2] = leg_bl.x;
      positions[4] = -leg_fr.x;
      positions[6] = -leg_fl.x;

      positions[1] = leg_br.y;
      positions[3] = leg_bl.y;
      positions[5] = leg_fr.y;
      positions[7] = leg_fl.y;

      leg_fl.update_forward();
      leg_fr.update_forward();
      leg_bl.update_forward();
      leg_br.update_forward();

      actuators::write(positions, ori, dt, true);

      GRAPH("x", ori.x * 180.0f / PI, TOP);
      GRAPH("y", ori.y * 180.0f / PI, TOP);
      GRAPH("z", ori.z * 180.0f / PI, TOP);
      PRINTLN("");
    }

} // namespace task
