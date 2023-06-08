#pragma once

#include "utility.h"

// This is where we place long functions or repeated code
/*Say hypothetically you have a filtering process you apply to your data 10
times for a loop (its a hypothetical) you might do that in here to keep the
task.h file cleaner
*/
namespace subtask {

	OriQuat = Quat {1.0f, 0.0f, 0.0f, 0.0f};

	void exampleLongFunc() {}

	Vec ResOriFromAcc(Vec Acc){
		Vec GlobAcc = Vec(0.0f , 0.0f, Acc.magnitude());
		dot = Acc.dot(GlobAcc);
		cross = Acc * GlobAcc;

		q = Quat(dot + sqrt(dot * dot + cross.dot(cross)), cross.x, cross.y, cross.z);
		q.normalise();

		return Vec(q.toEuler());
	}

	Vec ResOriFromRate(Vec Rate){
		OriQuat += OriQuat.fromAngularRate(Rate);
		OriQuat.normalise();

		return Vec(OriQuat.toEuler());
	}

}  // namespace subtask
