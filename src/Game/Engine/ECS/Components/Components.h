// Defines structs for different components in the ECS. Wrapper structs are required, instead typdef,
// since each struct gets it's own id

#pragma once
#include "../Game/Math/Vector.h"
#include "../Game/Utils/ReadObj.h"
#include <string>


struct Position {
	Vec3<float> pos;
	Position(float x, float y, float z) : pos(x, y, z) {}
	Position(Vec3<float> pos) : pos(pos) {}
};

struct Rotation {
	Vec3<float> rot;
	Rotation(float x, float y, float z) : rot(x, y, z) {}
	Rotation(Vec3<float> rot) : rot(rot) {}
};

struct Scale {
	float scale;
};

struct Velocity {
	Vec3<float> vel;
};

struct AngularVel {
	Vec3<float> vel;
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

	Camera(Matrix4x4 projMat) : projMat(projMat) {};
};

struct Mesh {
	Model* model;
};

struct Material {

	Vec3<float> rgb;

	bool backFaceCull = false;
	bool lit = true;
	bool wireframe = false;

	Material(float r, float g, float b) : rgb(r, g, b), backFaceCull(false), lit(false), wireframe(false) {};
	Material(float r, float g, float b, bool cull, bool lit, bool wireframe) : rgb(r, g, b), backFaceCull(cull), lit(lit), wireframe(wireframe) {};
};

struct Text {
	char* text;
	int x;
	int y;
	void* font;

	Text(char *text, int x, int y, void* font) : text(text), x(x), y(y), font(font) {};
};

struct Player {};

struct GoalPerspective {};

struct Particle {};

