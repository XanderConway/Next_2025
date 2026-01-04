// Class for a camera, which is used to render models
#include "../Game/Camera.h"
#include "../ContestAPI/app.h"

Camera::Camera(float n, float f) : nearPlane(n), farPlane(f), pitch(0), yaw(0) {
	this->projMat = Matrix4x4({
		{1064, 0, 0, 0},
		{0, 768, 0, 0},
		{0, 0, f/(f - n), -(f*n)/(f - n)},
		{0, 0, 1, 0}
	});
}

// Update the Camera's view matrix based on it's current position, yaw and pitch
void Camera::UpdateViewMat() {

	// (0, 0, 1) rotated by yaw and pitch
	Vec3<float> forward;
	forward.x = -sin(yaw) * cos(pitch);
	forward.z = cos(yaw) * cos(pitch);
	forward.y = sin(pitch);
	forward.w = 0;

	// (1, 0, 0) rotated by yaw (pitch rotates around x axis, so it has no effect)
	Vec3<float> right;
	right.x = cos(yaw);
	right.z = sin(yaw);
	right.y = 0;
	right.w = 0;

	Vec3<float> up = cross(forward, right);

	this->viewMat.setRow(right, 0);
	this->viewMat.setRow(up, 1);
	this->viewMat.setRow(forward, 2);

	return;
}

Vec3<float> Camera::WorldToCameraSpace(Vec3<float> v) {
	return this->viewMat.mul(v - this->pos);
}

Vec3<float> Camera::CameraToClipSpace(Vec3<float> v) {
	Vec3<float> o = this->projMat.mul(v);

	return o;
}

void Camera::Render(Model m) {
	for (Face f : m.faces) {

		float s = 50;

		Vec3<float> trans{ 0, 0, -500 };

		Vec3<float> v1 = m.verticies[f.v1].pos * s + trans;
		Vec3<float> v2 = m.verticies[f.v2].pos * s + trans;
		Vec3<float> v3 = m.verticies[f.v3].pos * s + trans;

		Vec3<float> temp = Vec3<float>();

		// Object to World Space

		// World to Camera Space
		v1 = this->WorldToCameraSpace(v1);
		v2 = this->WorldToCameraSpace(v2);
		v3 = this->WorldToCameraSpace(v3);

		v1 = this->CameraToClipSpace(v1);
		v2 = this->CameraToClipSpace(v2);
		v3 = this->CameraToClipSpace(v3);


		// Camera to Clip Space

		App::DrawTriangle(v1.x, v1.y, v1.z, v1.w, v2.x, v2.y, v2.z, v2.w, v3.x, v3.y, v3.z, v3.w, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		//App::DrawTriangle((v1.x / v1.z) * s + trans.x, (v1.y / v1.z) * s + trans.y, 0, 1, (v2.x / v1.z) * s + trans.x, v2.y * s + trans.y, 0, 1, v3.x * s + trans.x, v3.y * s + trans.y, 0, 1, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	}
}