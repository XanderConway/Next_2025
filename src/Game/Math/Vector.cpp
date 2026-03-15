#include "../Game/Math/Vector.h"
#include "../Game/Utils/ReadObj.h"
#include <cmath>
#include <random>

const unsigned int SEED = 99;

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

float norm(const Vec3<float> v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float getRand(float min, float max) {
	static std::random_device rd;
	static std::mt19937 eng(99);
	std::uniform_real_distribution<float> dist(min, max);
	return dist(eng);
}

Vec3<float> getRandVec(float min, float max) {
	return Vec3<float>(getRand(min, max), getRand(min, max), getRand(min, max));
}

Vec3<float> Matrix4x4::mul(const Vec3<float> v) const {
	Vec3<float> o(0, 0, 0, 0);
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			o[r] += mat[r][c] * v[c];
		}
	}
	return o;
}

Matrix4x4 Matrix4x4::mul(const Matrix4x4 other) {

	Matrix4x4 o({
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		});

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			for (int x = 0; x < 4; x++) {
				o.mat[r][c] += mat[r][x] * other.mat[x][c];
			}
		}
	}
	return o;
}

void Matrix4x4::setRow(Vec3<float> v, int row) {
	for (int i = 0; i < 4; i++) {
		mat[row][i] = v[i];
	}
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