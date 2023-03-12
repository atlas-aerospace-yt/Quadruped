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
    actuators::test();
  }

  void Calibration()
  {
  }

  void Loop()
  {
    for (int width=0; width<8; width++)
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
    delay(1000);
    for (int height=15; height>8; height--)
    {
      for (int i=0; i<8; i ++)
      {
        if (i%2 == 0){
          values[i] = subtask::get_hip_output(0, height);
        }
        else
        {
          values[i] = subtask::get_knee_output(0, height);
        }
      }
      PRINT(height);
      PRINT(" , ");
      actuators::write(values);
      delay(100);
    }
    for (int height=8; height<15; height++)
    {
      for (int i=0; i<8; i ++)
      {
        if (i%2 == 0){
          values[i] = subtask::get_hip_output(0, height);
        }
        else
        {
          values[i] = subtask::get_knee_output(0, height);
        }
      }
      PRINT(height);
      PRINT(" , ");
      actuators::write(values);
      delay(100);
    }
    delay(1000);
  }
}
