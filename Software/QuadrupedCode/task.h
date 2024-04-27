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
#define WALK_INTERP 250
#define WALK_GAIT WALK_INTERP, -3.0f, 3.0f, 6.0f, NORM_HEIGHT, 6

#define TROT_INTERP 200
#define TROT_GAIT TROT_INTERP, -3.0f, 3.0f, 8.0f, NORM_HEIGHT, 6

#define DEFAULT_POSITION {0.0f, NORM_HEIGHT, 0.0f, NORM_HEIGHT, 0.0f, NORM_HEIGHT, 0.0f, NORM_HEIGHT}

#define MIN_HEIGHT 10.0f
#define MAX_HEIGHT 15.0f
#define STEPS 1000.0f

// The functions in place here can be changed to suit your needs
// The ones listed here serve as inspiration--feel free to change them as you need -- but remember to change your Tasks in main.h
namespace task
{
  // Globals can be defined here
  float positions[8];

  float dt;
  Vec ori;

  // Can be used for code that only runs once
  // This can also be run multiple times by changing the code flow in main.h

  void Setup()
  {
    actuators::init();
    sensors::init();
    subtask::init();
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

    gait::Gait leg_bl(0, WALK_GAIT);
    gait::Gait leg_fr(1, WALK_GAIT);
    gait::Gait leg_br(3, WALK_GAIT);
    gait::Gait leg_fl(4, WALK_GAIT);

    while (i < dist*100/6*WALK_INTERP) {
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
    subtask::ori_quat = {1.0f, 0.0f, 0.0f, 0.0f};
    subtask::get_dt();
  }

  void TrotLoop(int dist)
  {
    unsigned long i=0;

    gait::Gait leg_bl(0, TROT_GAIT);
    gait::Gait leg_fr(0, TROT_GAIT);
    gait::Gait leg_br(3, TROT_GAIT);
    gait::Gait leg_fl(3, TROT_GAIT);

    while (i < dist*100/6*TROT_INTERP) {
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
      PRINTLN("Trotting loop: " + String(i));
    }
    subtask::ori_quat = {1.0f, 0.0f, 0.0f, 0.0f};
    subtask::get_dt();
  }

  void Squat(int reps){
    unsigned long counter=0;
    int i = 0;
    int prev_i = 0;

    while (counter < reps*STEPS*2){

      if (i < STEPS && prev_i <= i || i < 0){
        prev_i = i;
        i++;
      } else {
        prev_i = i;
        i--;
      }

      float x = 0.0f;
      float y = sk_math::SMOOTHLERP(MIN_HEIGHT, MAX_HEIGHT, i/STEPS);

      for (int i=0; i<8; i++){
        if (i % 2 == 0){
          positions[i] = x;
        } else {
          positions[i] = y;
        }
      }
      counter++;
      actuators::write(positions);
      delay(2);
    }
    subtask::ori_quat = {1.0f, 0.0f, 0.0f, 0.0f};
    subtask::get_dt();
  }

  void Reset(){
    subtask::ori_quat = {1.0f, 0.0f, 0.0f, 0.0f};
    float default_pos[8] = DEFAULT_POSITION;
    actuators::write(default_pos);
  }

  // Code that loops
  void Loop(){
    // Raido loop
    String command = sensors::recv_data();

    if (command == "WALK"){
      WalkLoop(1);
    }
    else if (command == "TROT"){
      TrotLoop(1);
    }
    else if (command == "SQUAT"){
      Squat(3);
    }
    else if (command == "RESET"){
      Reset();
    }
    else if (command != ""){
      PRINTLN("Invalid command!")
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
