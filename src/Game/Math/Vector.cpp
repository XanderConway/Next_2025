#include "../Game/Math/Vector.h"

Vec3<float> cross(const Vec3<float> v1, const Vec3<float> v2) {
	Vec3<float> out;
	out.x = v1.y * v2.z - v1.z * v2.y;
	out.y = v1.z * v2.x - v1.x * v2.z;
	out.z = v1.x * v2.y - v1.y * v2.x;
	out.w = 0;
	return out;
}

// Note, w components are not included in the dot product
float dot(const Vec3<float> v1, const Vec3<float> v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Matrix4x4 getRotationMatrix(Vec3<float> r) {
	return getRotationMatrix(r.y, r.x, r.z);
}


Matrix4x4 getRotationMatrix(float yaw, float pitch, float roll) {
	// Compute Rotation Matricies, based on yaw, pitch and roll

	Matrix4x4 output;

	// Compute Rotation Matricies, based on yaw, 
	Matrix4x4 yawMat({
		{cos(yaw), 0, sin(yaw), 0},
		{0, 1, 0, 0},
		{-sin(yaw), 0, cos(yaw), 0},
		{0, 0, 0, 1}
		});

	Matrix4x4 pitchMat({
		{1, 0, 0, 0},
		{0, cos(pitch), -sin(pitch), 0},
		{0, sin(pitch), cos(pitch), 0},
		{0, 0, 0, 1}
		});


	Matrix4x4 rollMat({
		{cos(roll), -sin(roll), 0, 0},
		{sin(roll), cos(roll), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
		});

	return rollMat.mul(pitchMat.mul(yawMat));
}