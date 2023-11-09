#pragma once

//-----Internals------
#include "utility.h"
#include "task_flow.h"
#include "time_handler.h"
#include "sidekick_state.h"
//Stem include wrapper
// NOTE: Not robust for regualr pico compiles
#ifdef ARDUINO_ARCH_RP2040
#include "stem.h"
#endif
//-----Internals------

#include "skServo.h"

namespace sm {
//------INTERNAL-----
// DO NOT TOUCH
void SM_UPDATE_LOOP() {
    taskSchedule();
}


void SM_INIT() {
    Serial.begin(115200);
    taskInit();
}
//------INTERNAL-----
}  // namespace sm
