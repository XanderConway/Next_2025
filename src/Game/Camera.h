//#pragma once
//#include "../Game/Math/Vector.h"
//#include "../Game/Utils/ReadObj.h"
//#include "../Game/Engine/GameObject.h"
//
//class Camera : public Component {
//public:
//
//	float nearPlane = 0;
//	float farPlane = 100;
//
//	Matrix4x4 viewMat;
//
//	Matrix4x4 projMat;
//
//	Camera(float n, float f);
//
//	void RenderModel(Model m);
//
//	void UpdateViewMat();
//	Vec3<float> WorldToCameraSpace(Vec3<float> v);
//
//	Vec3<float> CameraToClipSpace(Vec3<float> v);
//	void Update(float deltaTime) override;
//
//
//
//};