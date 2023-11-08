#pragma once

//-----Internals------
#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"
//-----Internals------

// Tasks go here-- this keeps the main file clean and focused on the "flow" of tasks
// Our general functions will be defined here things like our main loops
// Long sections of code or repeated code loops can be moved to sub_task.h

// The functions in place here can be changed to suit your needs
// The ones listed here serve as inspiration--feel free to change them as you need -- but remember to change your Tasks in main.h
namespace task
{

    // Globals can be defined here

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
    }

    // Can be used to print sensor values and any other required calibration
    void Calibration()
    {
      sk_timer.start();
      sk_timer.stop();
    }

    // Code that loops
    void Loop()
    {
      float dt = subtask::get_dt();
      sensors::update(dt);
      Vec ori = subtask::ori_quat.toEuler();

      float positions[8] = {0.0f, 12.0f,
                            0.0f, 12.0f,
                            0.0f, 12.0f,
                            0.0f, 12.0f};

      actuators::write(positions, ori, dt);

      GRAPH("x", ori.x * 180.0f / PI, TOP);
      GRAPH("y", ori.y * 180.0f / PI, TOP);
      GRAPH("z", ori.z * 180.0f / PI, TOP);
      PRINTLN("");
    }

} // namespace task
