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
    for (float height=0.09f; height < 0.15f; height+= 0.01f)
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
      actuators::write(values);
      delay(200);
    }
    for (float height=0.15f; height > 0.09f; height-= 0.01f)
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
      actuators::write(values);
      delay(200);
    }
  }
}
