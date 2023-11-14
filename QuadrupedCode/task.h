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
#define INTERP_PTS 200.0f
#define GAIT INTERP_PTS, -3.0f, 3.0f, 6.0f, NORM_HEIGHT

#define DEFAULT_POSITION {0.0f, NORM_HEIGHT, 0.0f, NORM_HEIGHT, 0.0f, NORM_HEIGHT, 0.0f, NORM_HEIGHT}

// The functions in place here can be changed to suit your needs
// The ones listed here serve as inspiration--feel free to change them as you need -- but remember to change your Tasks in main.h
namespace task
{
  // Globals can be defined here
  gait::Gait leg_bl(0, GAIT);
  gait::Gait leg_fr(1, GAIT);
  gait::Gait leg_br(3, GAIT);
  gait::Gait leg_fl(4, GAIT);

  float positions[8];

  float dt;
  Vec ori;

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
    float default_pos[8] = DEFAULT_POSITION;
    actuators::write(default_pos);
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

  void WalkLoop(int dist)
  {
    unsigned long i=0;
    while (i < dist*10*INTERP_PTS) {
      dt = subtask::get_dt();
      sensors::update(dt);
      ori = subtask::ori_quat.toEuler();

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

      i ++;

      PRINTLN("Walking loop: " + String(i));
    }
  }

  // Code that loops
  void Loop(){
    // Raido loop
    String command = sensors::recv_data();
    PRINTLN(command);
    if (command == "WALK"){
      WalkLoop(1);
      PRINTLN("TRIGGERED")
    }

    // Control loops
    dt = subtask::get_dt();
    sensors::update(dt);
    ori = subtask::ori_quat.toEuler();
    float default_pos[8] = DEFAULT_POSITION;
    actuators::write(default_pos, ori, dt, true);
    END_LOG;
  }
} // namespace task
