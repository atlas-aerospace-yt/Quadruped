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

#define FWD_RATIO 36.0f / 19.0f
#define BWD_RATIO -5.0f / 3.0f

#define MIN 0
#define MAX 180

#define MIN_HEIGHT 10.0f
#define MAX_HEIGHT 15.0f

#define STEPS 1000.0f

namespace actuators{

  // Globals can be defined here
  Servo knee;
  Servo hip;

  void init(){
    knee.attach(0);
    hip.attach(1);
  }

  int servo_forward(int value){
    int output = static_cast<int>(FWD_RATIO * value);
    return output < MIN ? MIN : output > MAX ? MAX : output;
  }

  int servo_backward(int value){
    int output = static_cast<int>(BWD_RATIO * value + MAX);
    return output < MIN ? MIN : output > MAX ? MAX : output;
  }

  void write(int point){
    float x = 0.0f;
    float y = sk_math::SMOOTHLERP(MIN_HEIGHT, MAX_HEIGHT, point/STEPS);

    int* pos = subtask::get_positions(x, y);
    knee.write(servo_forward(pos[0]));
    hip.write(servo_backward(pos[1]));
  }

}  // namespace actuators
