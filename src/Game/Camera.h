#pragma once
#include "../Game/Math/Vector.h"
#include "../Game/Utils/ReadObj.h"

class Camera {
public:
	Vec3<float> pos;
	float yaw;
	float pitch;

	float nearPlane = 0;
	float farPlane = 100;

	Matrix4x4 viewMat;

	Matrix4x4 projMat;

	Camera(float n, float f);

	void Render(Model m);

	void UpdateViewMat();
	Vec3<float> WorldToCameraSpace(Vec3<float> v);

	Vec3<float> CameraToClipSpace(Vec3<float> v);


};