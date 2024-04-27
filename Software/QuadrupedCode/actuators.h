#pragma once

//-----Internals------

#include "actuator_struct.h"
#include "utility.h"
#include "sk_math.h"
//#include "internal_defs.h"

//-----Internals------
#include <Servo.h>

// Include your Actuator libraries here
#include "sub_task.h"
#include "vector.h"

// Constant definitions
#define FWD_RATIO 5.0f / 3.0f
#define BWD_RATIO -5.0f / 3.0f

#define MIN 0
#define MAX 180

#define MIN_HEIGHT 8.0f
#define MAX_HEIGHT 15.0f
#define NORM_HEIGHT 13.0f

namespace actuators{

  // Globals can be defined here
  Servo knee_br;
  Servo hip_br;
  Servo knee_bl;
  Servo hip_bl;
  Servo knee_fr;
  Servo hip_fr;
  Servo knee_fl;
  Servo hip_fl;

  void init(){
    // Connect all of the servos
    knee_br.attach(9);
    hip_br.attach(8);
    knee_bl.attach(11);
    hip_bl.attach(10);
    knee_fr.attach(13);
    hip_fr.attach(12);
    knee_fl.attach(15);
    hip_fl.attach(14);
  }

  int servo_forward(int value){
    // Calculate the servo value for a real world value
    int output = static_cast<int>(FWD_RATIO * value);
    return output < MIN ? MIN : output > MAX ? MAX : output;
  }

  int servo_backward(int value){
    // Calculate the servo value for a real world value
    int output = static_cast<int>(BWD_RATIO * value + MAX);
    return output < MIN ? MIN : output > MAX ? MAX : output;
  }

  float write_control(float height, float delta_x, float delta_y){
    if (MIN_HEIGHT <= height+delta_x+delta_y <= MAX_HEIGHT){
      return height+delta_x+delta_y;
    }
    if (height+delta_x+delta_y < MIN_HEIGHT) {
      return MIN_HEIGHT;
    }
    return MAX_HEIGHT;
  }

  void write(float* positions, Vec ori={0,0,0}, float dt=0, bool control=false){
    // If control is wanted, write the control values onto the position values
    if (control) {
      float* output = subtask::control_loop(ori, dt);
      positions[1] = write_control(positions[1], -output[1], output[0]);
      positions[3] = write_control(positions[3], output[1], output[0]);
      positions[5] = write_control(positions[5], -output[1], -output[0]);
      positions[7] = write_control(positions[7], output[1], -output[0]);
    }

    // Check that all of the height positions are valid
    for (int i=0; i<4; i++){
      if (positions[2*i+1] > MAX_HEIGHT) {
        positions[2*i+1] = MAX_HEIGHT;
      } else if (positions[2*i+1] < MIN_HEIGHT) {
        positions[2*i+1] = MIN_HEIGHT;
      }
    }

    // Write the values to the servos
    float* pos = subtask::get_positions(positions[0], positions[1]);
    knee_br.write(servo_forward(pos[0]));
    hip_br.write(servo_backward(pos[1]));

    pos = subtask::get_positions(positions[2], positions[3]);
    knee_bl.write(servo_backward(pos[0]));
    hip_bl.write(servo_forward(pos[1]));

    pos = subtask::get_positions(positions[4], positions[5]);
    knee_fr.write(servo_backward(pos[0]));
    hip_fr.write(servo_forward(pos[1]));

    pos = subtask::get_positions(positions[6], positions[7]);
    knee_fl.write(servo_forward(pos[0]));
    hip_fl.write(servo_backward(pos[1]));

    GRAPH("leg_br", positions[1], TOP);
    GRAPH("leg_bl", positions[3], TOP);
    GRAPH("leg_fbr", positions[5], TOP);
    GRAPH("leg_fl", positions[7], TOP);
  }

}  // namespace actuators
