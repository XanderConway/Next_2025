#pragma once
#include <vector>
#include "Camera.h"
#include "../Game/Utils/ReadObj.h"
#include "../Game/Math/Vector.h"


struct GameObject;

struct Component {
	GameObject* go;
	int ComponentType = 0;
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void Render() {};
};

struct GameObject {
	Vec3<float> position;
	Vec3<float> rot;
	Vec3<float> scale;

	std::vector<Component *> components;

	void addComponent(Component *c) {
		components.push_back(c);
		c->go = this;
	}


};

class Camera : public Component {
public:

	float nearPlane = 0;
	float farPlane = 100;

	Matrix4x4 viewMat;

	Matrix4x4 projMat;

	Camera(float n, float f);

	void RenderModel(Model m);

	void UpdateViewMat();
	Vec3<float> WorldToCameraSpace(Vec3<float> v);

	Vec3<float> CameraToClipSpace(Vec3<float> v);
	void Update(float deltaTime) override;
};

struct MeshRenderer : public Component {

	Camera &cam;
	Model m;

	MeshRenderer(Camera &cam, Model m) : cam(cam), m(m) {

	}

	void Start() override {
		return;
	}

	void Update(float deltaTime) override {
		cam.UpdateViewMat();
	}

	void Render() {
		cam.RenderModel(m);
		return;
	}
};

