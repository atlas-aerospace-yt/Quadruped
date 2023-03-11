#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"

#define NUM_OF_LEGS 4

namespace task
{

  int values[8];
  float hip;
  float knee;

  void Setup()
  {
      actuators::init();
  }

  void ActuatorTest()
  {
  }

  void Calibration()
  {
  }

  void Loop()
  {
    for (int width=0; width<7; width++)
    {
      for (int i=0; i<8; i ++)
      {
        if (i%2 == 0){
          values[i] = subtask::get_hip_output(width, 12);
        }
        else
        {
          values[i] = subtask::get_knee_output(width, 12);
        }
      }
      PRINT(width);
      PRINT(" , ");
      actuators::write(values);
      delay(200);
    }
    for (int width=7; width>0; width--)
    {
      for (int i=0; i<8; i ++)
      {
        if (i%2 == 0){
          values[i] = subtask::get_hip_output(width, 12);
        }
        else
        {
          values[i] = subtask::get_knee_output(width, 12);
        }
      }
      PRINT(width);
      PRINT(" , ");
      actuators::write(values);
      delay(200);
    }
  }
}
