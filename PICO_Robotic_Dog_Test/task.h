#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"
#include "sk_math.h"

// Other libraries
#include "vector.h"
#include "control.h"

// My libraries
#include "gait.h"

// interp_pts, min_x, max_x, min_y, max_y
#define GAIT 100.0f, -5.0f, 5.0f, 12.0f, 14.0f
#define NORM 13.0f

namespace task
{

  float dt;

  gait::Gait leg_bl(0, GAIT);
  gait::Gait leg_fr(1, GAIT);
  gait::Gait leg_br(2, GAIT);
  gait::Gait leg_fl(3, GAIT);

  PID<float> PIDY(0.075, 0.005, 0.025);
  PID<float> PIDZ(0.075, 0.005, 0.025);

  void Setup()
  {
    PIDY.setlims(-3, 3);
    PIDZ.setlims(-3, 3);

    actuators::init();
  }

  void ActuatorTest()
  {
    actuators::test();
  }

  void Calibration()
  {
    int iter;
    Vec acc;
    Vec gyro;

    sk_timer.start();

    while (sk_timer.getTime() < 5){
      acc = sensors::get_raw_accel();
      gyro = sensors::get_raw_gyro();

      sensors::accel_offset += acc;
      sensors::gyro_offset += gyro;

      iter ++;
    }

    sensors::gyro_offset /= -iter;

    sensors::accel_offset /= iter;
    sensors::accel_ratio /= sensors::accel_offset.magnitude();
    subtask::ori_quat = subtask::get_ori_from_accel(sensors::accel_offset);
    subtask::gyro_ori = subtask::get_ori_from_accel(sensors::accel_offset);

    sk_timer.start();
    sk_timer.stop();
  }

  void Loop()
  {
    dt = sk_timer.deltaT();
    sk_timer.start();

    Vec accel = sensors::get_accel();
    Vec gyro = sensors::get_gyro();

    subtask::update_ori(gyro, accel, dt);

    PRINT("Delta time: " + String(dt));

    Vec ori = subtask::gyro_ori.QuatToEuler() * 180.0f / PI;

    float y = PIDY.update(ori.y, dt);
    float z = PIDZ.update(ori.z, dt);

    GRAPH("OriX", ori.x, TOP);
    GRAPH("OriY", ori.y, TOP);
    GRAPH("OriZ", ori.z, TOP);

    GRAPH("PIDY", y, BOT);
    GRAPH("PIDZ", z, BOT);

    actuators::write_leg_fl(0.0f, NORM - z + y);
    actuators::write_leg_fr(0.0f, NORM + z + y);
    actuators::write_leg_bl(0.0f, NORM - z - y);
    actuators::write_leg_br(0.0f, NORM + z - y);

    sk_timer.stop();
  }

  void Walk(){
    //
    // A walking demo without any forms of control
    //
    actuators::write_leg_fl(leg_fl.x, leg_fl.y);
    actuators::write_leg_fr(leg_fr.x, leg_fr.y);
    actuators::write_leg_bl(leg_bl.x, leg_bl.y);
    actuators::write_leg_br(leg_br.x, leg_br.y);

    leg_fl.update_forward();
    leg_fr.update_forward();
    leg_bl.update_forward();
    leg_br.update_forward();
  }

  void Graph(){
    GRAPH("FrontLeftX", leg_fl.x, TOP);
    GRAPH("FrontRightX", leg_fr.x, TOP);
    GRAPH("BackLeftX", leg_bl.x, TOP);
    GRAPH("BackRightX", leg_br.x, TOP);

    GRAPH("FrontLeftY", leg_fl.y, BOT);
    GRAPH("FrontRightY", leg_fr.y, BOT);
    GRAPH("BackLeftY", leg_bl.y, BOT);
    GRAPH("BackRightY", leg_br.y, BOT);
  }
}
