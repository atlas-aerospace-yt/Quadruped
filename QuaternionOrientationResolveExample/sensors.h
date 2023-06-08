#pragma once
//-----Internals------
#include "utility.h"
#include "sensor_struct.h"
//-----Internals------

// Include your sensor libraries here
#include "Wire.h"

#include "MPU6050_tockn.h"

namespace sensors {

	MPU6050 mpu6050(Wire);
	Vec rate = {0.0f, 0.0f, 0.0f};

	void init() {
		Wire.begin();
		mpu6050.begin();
		mpu6050.calcGyroOffsets(true);
	}

	void update() {
		rate.x = mpu6050
	}

}  // namespace sensors
