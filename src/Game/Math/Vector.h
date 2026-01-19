#pragma once

#include <iostream>
#include <cassert>


template<typename T>
struct Vec3 {
	T x, y, z, w;

	// constexpr constructors so that constant value Vecs can be initialized during compilation
	constexpr Vec3() : x(0), y(0), z(0), w(1) {}
	constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z), w(1) {}
	constexpr Vec3(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

	float& operator[](int i) {
		assert(i < 4 && "Vector index out of bounds!");
		return (&x)[i]; // can index, since x, y, z are contiguous in memory
	}

	// const version of [] is required as well
	const float& operator[](int i) const {
		assert(i < 4 && "Vector index out of bounds!");
		return (&x)[i];
	}

	const Vec3& operator+(const Vec3& other) const {
		return { x + other.x, y + other.y, z + other.z };
	}

	const Vec3& operator-(const Vec3& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	const Vec3& operator*(const float s) const {
		return { x * s, y * s , z * s };
	}
};

Vec3<float> getRand(float min, float max);
Vec3<float> cross(const Vec3<float> v1, const Vec3<float> v2);
float dot(const Vec3<float> v1, const Vec3<float> v2);
float norm(const Vec3<float> v);


struct Matrix4x4 {
	float mat[4][4];
	Matrix4x4() : mat{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} } { }

	Matrix4x4(const float(&values)[4][4]) {
		memcpy(mat, values, sizeof(mat));
	}

	Vec3<float> mul(const Vec3<float> v) const;

	Matrix4x4 mul(const Matrix4x4 other);

	void setRow(Vec3<float> v, int row);
};

Matrix4x4 getRotationMatrix(float yaw, float pitch, float roll);

Matrix4x4 getRotationMatrix(Vec3<float> r);