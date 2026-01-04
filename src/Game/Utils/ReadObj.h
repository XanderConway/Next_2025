#pragma once

#include <string>
#include <vector>
#include <cassert>

#include "../Game/Math/Vector.h"


template<typename T>
struct UV {
	T u, v;

	constexpr UV() : u(0), v(0) {}
	constexpr UV(T u, T v) : u(u), v(v) {};
};

struct Vert {
	Vec3<float> pos;
	UV<float> uv;
	Vec3<float> normal;
};

struct Face {
	int v1, v2, v3;
};

struct Model {
	std::vector<Vert> verticies;
	std::vector<Face> faces;
};

Model readFromFile(std::string filename);