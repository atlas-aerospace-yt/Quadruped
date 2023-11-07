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
#define MIN_HEIGHT -4.0f
#define MAX_HEIGHT 4.0f

#define STEPS 1000.0f

// The functions in place here can be changed to suit your needs
// The ones listed here serve as inspiration--feel free to change them as you need -- but remember to change your Tasks in main.h
namespace task
{

    // Globals can be defined here

    // Can be used for code that only runs once
    // This can also be run multiple times by changing the code flow in main.h
    int i = 0;
    int prev_i = 0;
    float positions[8];

    void Setup()
    {
      PRINT("Setting Up...")
      actuators::init();
      delay(2500);
    }

    // Can be used to automatically test actuators
    // Very useful for quick plug and play testing
    void ActuatorTest()
    {
    }

    // Can be used to print sensor values and any other required calibration
    void Calibration()
    {
      PRINTLN("Calibrating...")

      for (int i=0; i<8; i++){
        if (i % 2 == 0){
          positions[i] = 0;
        } else {
          positions[i] = 15;
        }
      }

      actuators::write(positions);
      delay(5000);
    }

    // Code that loops
    void Loop()
    {
      if (i < STEPS && prev_i <= i || i < 0){
        prev_i = i;
        i++;
      } else {
        prev_i = i;
        i--;
      }

      // Compute the positions array
      float x = sk_math::SMOOTHLERP(MIN_HEIGHT, MAX_HEIGHT, i/STEPS);
      float y = 13.0f;

      for (int i=0; i<8; i++){
        if (i % 2 == 0){
          positions[i] = x;
        } else {
          if (i < 5){
            positions[i] = y;
          } else {
            positions[i] = -y;
          }
        }
      }

      // Graphing outputs
      GRAPH("Height", y-MAX_HEIGHT, TOP);
      GRAPH("Translation", x, TOP);
      END_LOG;

      actuators::write(positions);
      delay(2);
    }

} // namespace task
