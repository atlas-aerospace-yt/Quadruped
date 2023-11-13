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

#define HEIGHT 13.0f
#define GAIT 2000.0f, -5.0f, 5.0f, 6.0f, HEIGHT

// The functions in place here can be changed to suit your needs
// The ones listed here serve as inspiration--feel free to change them as you need -- but remember to change your Tasks in main.h
namespace task
{

    // Globals can be defined here

    // Can be used for code that only runs once
    // This can also be run multiple times by changing the code flow in main.h
    float positions[8];

    gait::Gait leg_br(0, GAIT);
    gait::Gait leg_fl(1, GAIT);
    gait::Gait leg_bl(3, GAIT);
    gait::Gait leg_fr(4, GAIT);

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

      // Graphing outputs
      GRAPH("HeightBR", positions[1], TOP);
      //GRAPH("TranslationBR", positions[0], TOP);

      GRAPH("HeightBL", positions[3], TOP);
      //GRAPH("TranslationBL", positions[2], TOP);

      GRAPH("HeightFR", positions[5], TOP);
      //GRAPH("TranslationFR", positions[4], TOP);

      GRAPH("HeightFL", positions[7], TOP);
      //GRAPH("TranslationFL", positions[6], TOP);
      END_LOG;

      actuators::write(positions);
    }

} // namespace task
