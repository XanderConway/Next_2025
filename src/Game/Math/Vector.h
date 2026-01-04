#pragma once
#include <iostream>
#include <cassert>

template<typename T>
struct Vec3 {
	T x, y, z, w;

	// constexpr constructors so that constant value Vecs can be initialized during compilation
	constexpr Vec3() : x(0), y(0), z(0), w(1) {}
	constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z), w(1) {}

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

Vec3<float> cross(const Vec3<float> v1, const Vec3<float> v2);

struct Matrix4x4 {
	float mat[4][4];
	Matrix4x4() : mat{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} } { }

	Matrix4x4(const float(&values)[4][4]) {
		memcpy(mat, values, sizeof(mat));
	}

	Vec3<float> mul(const Vec3<float> v) const {
		Vec3<float> o{};
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				o[r] += mat[r][c] * v[c];
			}
		}
		return o;
	}

	void setRow(Vec3<float> v, int row) {
		for (int i = 0; i < 4; i++) {
			mat[row][i] = v[i];
		}
	}
};