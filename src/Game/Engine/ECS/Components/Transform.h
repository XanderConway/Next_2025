// Defines structs for different components in the ECS. Wrapper structs are required, instead typdef,
// since each struct gets it's own id

#pragma once
#include "../Game/Math/Vector.h"

struct Position : public Vec3<float> {
	using Vec3<float>::Vec3;
};

struct Rotation : public Vec3<float> {
	using Vec3<float>::Vec3;
};

struct Scale {
	float scale;
};

struct ObjToWorld {
	Matrix4x4 mat;
};

struct Camera {
	Matrix4x4 projMat;
	Camera(float n, float f) {
		projMat = Matrix4x4({
			{1064, 0, 0, 0},
			{0, 768, 0, 0},
			{0, 0, f/(f - n), -(f*n)/(f - n)},
			{0, 0, 1, 0}
		});	
	}
};

struct Mesh {
	Model* model;
};

struct Material : public Vec3<float> {
	using Vec3<float>::operator*;
	using Vec3<float>::operator=;
	bool backFaceCull = false;
	Material(float r, float g, float b, bool cull) : Vec3<float>(r, g, b), backFaceCull(cull) {};
};

