#pragma once

//-----Internals------
#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"
//-----Internals------

#include "vector.h"
// Tasks go here-- this keeps the main file clean and focused on the "flow" of tasks
// Our general functions will be defined here things like our main loops
// Long sections of code or repeated code loops can be moved to sub_task.h

// The functions in place here can be changed to suit your needs
// The ones listed here serve as inspiration--feel free to change them as you need -- but remember to change your Tasks in main.h
namespace task
{

  // Globals can be defined here
  String data;

  void Setup()
  {
    sensors::init();
    while(!Serial){}
  }

  void ActuatorTest()
  {
  }

  void Calibration()
  {
  }

  void Loop()
  {
    while (Serial.available()) {
      String command = Serial.readStringUntil('\n');

      PRINTLN("Sending... " + command);

      sensors::send_data(command);
    }
  }
}
