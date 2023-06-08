#pragma once
//-----Internals------
#include "utility.h"
#include "sensor_struct.h"
//-----Internals------

// Include your sensor libraries here
#include "Wire.h"

#include "MPU6050_tockn.h"

namespace sensors {

	MPU6050 mpu6050(Wire1);

	Vec rate = {0.0f, 0.0f, 0.0f};
	Vec accel = {0.0f, 0.0f, 0.0f};

	void init() {
		Wire1.begin();
		mpu6050.begin();
		//mpu6050.calcGyroOffsets();
	}

	void update(){
		mpu6050.update();

		rate.x = mpu6050.getGyroX();
		rate.y = mpu6050.getGyroY();
		rate.z = mpu6050.getGyroZ();

		accel.x = mpu6050.getAccX();
		accel.y = mpu6050.getAccY();
		accel.z = mpu6050.getAccZ();
	}

}  // namespace sensors
