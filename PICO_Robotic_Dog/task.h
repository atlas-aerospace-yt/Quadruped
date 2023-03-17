#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"

#define NUM_OF_LOOPS 10
#define NUM_OF_LEGS 4

#define UP_HEIGHT 15
#define DOWN_HEIGHT 8

namespace task
{
  int* walk_values;
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

  void Jump()
  {
    //
    //  Goes to the lowest position then goes to the heighest without delay
    //
    for (int i=UP_HEIGHT; i>DOWN_HEIGHT; i--)
    {
      float hip_value = subtask::get_hip_output(0, i);
      float knee_value = subtask::get_knee_output(0, i);

      for (int j=0; j<8; j++)
      {
        if (j%2 == 0)
        {
          values[j] = hip_value;
        }
        else
        {
          values[j] = knee_value;
        }
      }
      actuators::write(values);
      delay(100);
    }

    float hip_value = subtask::get_hip_output(0, 15);
    float knee_value = subtask::get_knee_output(0, 15);

    for (int j=0; j<8; j++)
    {
      if (j%2 == 0)
      {
        values[j] = hip_value;
      }
      else
      {
        values[j] = knee_value;
      }
    }
    actuators::write(values);
    delay(1000);
  }

  void PushUp()
  {
    //
    //  Iterates through the height of the leg in a straight vertical line
    //

    for (int i=UP_HEIGHT; i>DOWN_HEIGHT; i--)
    {
      float hip_value = subtask::get_hip_output(0, i);
      float knee_value = subtask::get_knee_output(0, i);

      for (int j=0; j<8; j++)
      {
        if (j%2 == 0)
        {
          values[j] = hip_value;
        }
        else
        {
          values[j] = knee_value;
        }
      }
      actuators::write(values);
      delay(100);
    }
    for (int i=DOWN_HEIGHT; i<UP_HEIGHT; i++)
    {
      float hip_value = subtask::get_hip_output(0, i);
      float knee_value = subtask::get_knee_output(0, i);

      for (int j=0; j<8; j++)
      {
        if (j%2 == 0)
        {
          values[j] = hip_value;
        }
        else
        {
          values[j] = knee_value;
        }
      }
      actuators::write(values);
      delay(100);
    }
  }

  void Twerk()
  {
    //
    //  A simple dance which keeps the front legs solid and moves
    //  the back legs up and down.
    //

    if (height == UP_HEIGHT){
      height = DOWN_HEIGHT;
    }
    else{
      height = UP_HEIGHT;
    }

    for (int i=0; i<8; i++){
      // if the actuator is a hip, compute a hip angle
      if (i%2 == 0){
        if (i > 3){
          values[i] = subtask::get_hip_output(0, height);
        }
        else{
          values[i] = subtask::get_hip_output(0, UP_HEIGHT);
        }
      }
      // otherwise if the actuator is a knee, compute a knee angle
      else{
        if (i > 3){
          values[i] = subtask::get_knee_output(0, height);
        }
        else{
          values[i] = subtask::get_knee_output(0, UP_HEIGHT);
        }
      }
    }

    actuators::write(values);
    delay(200);
  }

  void Bop()
  {
    //
    //  Goes into sit position and moves the front legs up and down
    //

    if (height == UP_HEIGHT){
      height = DOWN_HEIGHT;
    }
    else{
      height = UP_HEIGHT;
    }

    for (int i=0; i<8; i++){
      // if the actuator is a hip, compute a hip angle
      if (i%2 == 0){
        if (i > 3){
          values[i] = subtask::get_hip_output(0, DOWN_HEIGHT);
        }
        else{
          values[i] = subtask::get_hip_output(0, height);
        }
      }
      // otherwise if the actuator is a knee, compute a knee angle
      else{
        if (i > 3){
          values[i] = subtask::get_knee_output(0, DOWN_HEIGHT);
        }
        else{
          values[i] = subtask::get_knee_output(0, height);
        }
      }
    }

    actuators::write(values);
    delay(200);
  }

  void Loop()
  {
    //
    // A walking demo without any forms of control.
    //

    /*subtask::update_gait();
    subtask::get_positions();
    actuators::write(subtask::positions);

    delay(100);*/

    for (int i=0; i<NUM_OF_LOOPS; i++){
      Bop();
    }
    PushUp();
    for (int i=0; i<NUM_OF_LOOPS; i++){
      Twerk();
    }
    PushUp();
  }
}
