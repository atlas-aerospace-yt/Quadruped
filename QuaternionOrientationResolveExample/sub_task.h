#pragma once

#include "utility.h"
#include "quaternion.h"
#include "vector.h"

// This is where we place long functions or repeated code
/*Say hypothetically you have a filtering process you apply to your data 10
times for a loop (its a hypothetical) you might do that in here to keep the
task.h file cleaner
*/
namespace subtask {

	Quat OriQuat = {1.0f, 0.0f, 0.0f, 0.0f};
	Vec OriAcc;
	Vec OriGyro;

	void exampleLongFunc() {}

	Vec ResOriFromAcc(Vec Acc){
		Vec GlobAcc = {Acc.magnitude(), 0.0f , 0.0f};
		float dot = Acc.dot(GlobAcc);
		Vec cross = Acc * GlobAcc;

		Quat q = Quat(dot + sqrt(dot * dot + cross.dot(cross)), cross.x, cross.y, cross.z);
		q.normalize();

		OriQuat.toEulerVector(&OriAcc);
		return OriAcc;
	}

	Vec ResOriFromGyro(Vec Rate){
		OriQuat += OriQuat.fromAngularRate(Rate) * 0.01;
		OriQuat.normalize();

		float* ypr[3] = {OriQuat.toEuler()};
		Vec ori = {*(ypr[0]), *(ypr[1]), *(ypr[2])};
		return ori;
	}

}  // namespace subtask
