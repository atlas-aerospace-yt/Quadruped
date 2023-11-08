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
#define FWD_RATIO 36.0f / 19.0f
#define BWD_RATIO -5.0f / 3.0f

#define MIN 0
#define MAX 180

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

  void write(float* positions, Vec ori, float dt){
    float* output = subtask::control_loop(ori, dt);
    positions[1] = positions[1] - output[1] + output[0];
    positions[3] = positions[3]+ output[1] + output[0];
    positions[5] = positions[5]- output[1] - output[0];
    positions[7] = positions[7]+ output[1] - output[0];

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
  }

}  // namespace actuators
