#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/MeshRenderer.h"
#include "../Game/Utils/ReadObj.h"
#include "../ContestAPI/app.h"

using namespace ECS;

Matrix4x4 MeshRenderer::computeCamRotMat(EntityID camId) {
	Rotation& rot = *s->getComponent<Rotation>(camId);
	Matrix4x4 camRotationMat;

	float yaw = rot.y;
	float pitch = rot.x;

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

	camRotationMat.setRow(right, 0);
	camRotationMat.setRow(up, 1);
	camRotationMat.setRow(forward, 2);
	return camRotationMat;
}

Matrix4x4 MeshRenderer::computeCamTranslationMat(EntityID camId) {
	Position& pos = *s->getComponent<Position>(camId);
	return Matrix4x4({ { 1, 0, 0, -pos.x }, { 0, 1, 0, -pos.y }, { 0, 0, 1, -pos.z }, { 0, 0, 0, 1 } });
}

void MeshRenderer::Render() {
	assert(camView.entities.size() > 0 && "Mesh Renderer requires a camera!");

	for (EntityID camId : camView.entities) {
		Camera& cam = *s->getComponent<Camera>(camId);
		Matrix4x4 camR = computeCamRotMat(camId);
		Matrix4x4 camT = computeCamTranslationMat(camId);
		Matrix4x4 projetionMat = cam.projMat.mul(camR.mul(camT));

		Rotation& camRot = *s->getComponent<Rotation>(camId);
		Vec3<float> viewDir = getRotationMatrix(camRot).mul(Vec3<float>{0, 0, 1});

		// Default Material
		Material material(1, 1, 1, false, true, false);
		bool materialOverride = false;

		if (s->hasComponent<Material>(camId)) {
			material = *s->getComponent<Material>(camId);
			materialOverride = true;
		}

		for (EntityID e : view.entities) {

			Rotation& rot = *s->getComponent<Rotation>(e);
			Position& pos = *s->getComponent<Position>(e);

			Scale& scale = *s->getComponent<Scale>(e);

			Matrix4x4 scaleMat({
				{scale.scale, 0, 0, pos.x},
				{0, scale.scale, 0, pos.y},
				{0, 0, scale.scale, pos.z},
				{0, 0, 0, 1}
			});

			Matrix4x4 rotMat = getRotationMatrix(rot.y, rot.x, rot.z);

			Matrix4x4 obj2WorldMat(scaleMat.mul(rotMat));

			// Transform Object Position to World Position
			Model& m = *s->getComponent<Mesh>(e)->model;

			if (!materialOverride && s->hasComponent<Material>(e)) {
				material = *s->getComponent<Material>(e);
			}

			for (Face f : m.faces) {
				Vec3<float> v1 = m.verticies[f.v1].pos;
				Vec3<float> v2 = m.verticies[f.v2].pos;
				Vec3<float> v3 = m.verticies[f.v3].pos;

				// Assuming flat shading for now (all vert normals are the same)
				Vec3<float> objNorm = m.verticies[f.v1].normal;
				Vec3<float> worldNorm = rotMat.mul(objNorm);

				v1 = obj2WorldMat.mul(v1);
				v2 = obj2WorldMat.mul(v2);
				v3 = obj2WorldMat.mul(v3);

				v1 = projetionMat.mul(v1);
				v2 = projetionMat.mul(v2);
				v3 = projetionMat.mul(v3);

				// Default white material
				//Material material(worldNorm.x, worldNorm.y, worldNorm.z, true);

				if (material.backFaceCull) {
					if (dot(viewDir, worldNorm) > 0.1) {
						continue;
					}
				}

				Material litMat = material;
				if (material.lit) {
					Vec3<float> lightDir(0, 1, 0.2f);
					float light = max(dot(lightDir, worldNorm), 0.2f);
					litMat.x *= light;
					litMat.y *= light;
					litMat.z *= light;
				}

				// Camera to Clip Space
				App::DrawTriangle(v1.x, v1.y, v1.z, v1.w, v2.x, v2.y, v2.z, v2.w, v3.x, v3.y, v3.z, v3.w, litMat.x, litMat.y, litMat.z, litMat.x, litMat.y, litMat.z, litMat.x, litMat.y, litMat.z, material.wireframe);
			}
		}
	}
}
