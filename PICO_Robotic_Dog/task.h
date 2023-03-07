#pragma once

#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "sidekick.h"

namespace task
{
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
      float knee_value = subtask::get_knee_output(-0.04f, 0.12f);
      float hip_value = subtask::get_hip_output(-0.04f, 0.12f);

      actuators::write(knee_value, hip_value);
    }
}
