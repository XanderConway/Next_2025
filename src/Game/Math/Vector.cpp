#include "../Game/Math/Vector.h"

Vec3<float> cross(const Vec3<float> v1, const Vec3<float> v2) {
	Vec3<float> out;
	out.x = v1.y * v2.z - v1.z * v2.y;
	out.y = v1.z * v2.x - v1.x * v2.z;
	out.z = v1.x * v2.y - v1.y * v2.x;
	out.w = 0;
	return out;
}