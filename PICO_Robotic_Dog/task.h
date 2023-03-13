#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"

#define NUM_OF_LEGS 4

#define UP_HEIGHT 14
#define DOWN_HEIGHT 10

namespace task
{

  int values[8];
  int height;
  float hip;
  float knee;

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
    /*for (int width=0; width<8; width++)
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
      delay(100);
    }
    for (int width=8; width>0; width--)
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
      delay(100);
    }
    delay(1000);*/

    if (height == UP_HEIGHT)
    {
      height = DOWN_HEIGHT;
    }
    else
    {
      height = UP_HEIGHT;
    }

    for (int i=0; i<8; i++)
    {
      if (i%2 == 0)
      {
        if (i > 3)
        {
          values[i] = subtask::get_hip_output(0, height);
        }
        else
        {
          values[i] = subtask::get_hip_output(0, UP_HEIGHT);
        }
      }
      else
      {
        if (i > 3)
        {
          values[i] = subtask::get_knee_output(0, height);
        }
        else
        {
          values[i] = subtask::get_knee_output(0, UP_HEIGHT);
        }
      }
    }

    actuators::write(values);
    delay(250);

  }
}
