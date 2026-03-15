#pragma once

#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include <vector>

typedef int SCENE_ID;

// Wrapper class for worlds, so that Scenes can be instansiated one at a time
// TODO: Could move AddAssets to World struct and delete this
struct Scene {
	ECS::World *const world;

	Scene() : world(new ECS::World()) {}

	virtual void AddAssets() {};
	
	void Update(float deltaTime) {
		world->Update(deltaTime);
	}

	void Start() {
		world->Start();
	}

	void Render() {
		world->Render();
	}

	void Shutdown() {
		world->Shutdown();
		delete world;
	}
};

struct SceneManager {
	SCENE_ID currScene = 0;
	std::vector<Scene*> scenes;

	// Singelton Pattern
	static SceneManager& getInstance() {
		static SceneManager manager;
		return manager;
	}

	// Load the the given Scene
	void loadScene(SCENE_ID id) {
		static bool firstScene = true;

		if (!firstScene) {
			scenes[currScene]->Shutdown();
		}
		currScene = id;
		scenes[currScene]->AddAssets();
		scenes[currScene]->Start();

		firstScene = false;
	}
	void Update(float deltaTime) {
		scenes[currScene]->Update(deltaTime);
	}
	void Render() {
		scenes[currScene]->Render();
	}

	void Shutdown() {
		scenes[currScene]->Shutdown();
	}
};