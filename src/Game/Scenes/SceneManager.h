#pragma once

#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include <vector>
#include <cassert>

typedef int SCENE_ID;

// Wrapper class for worlds, so that Scenes can be instansiated one at a time
// TODO: Could move AddAssets to World struct and use subclasses of world for levels instead
struct Scene {
	ECS::World *const world;

	Scene() : world(new ECS::World()) {}

	// Add all entities, components and systems to the Scene
	virtual void AddAssets() {};

	void InitalizeScene() {
		if (world->entities.size() > 0) {
			assert(false && "World data must be cleared before initialization");
		}
		AddAssets();
		Start();
	}
	
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
	}
};

struct SceneManager {
	SCENE_ID currScene = 0;
	SCENE_ID nextScene = -1;
	std::vector<Scene*> scenes;

	// Singelton Pattern
	static SceneManager& getInstance() {
		static SceneManager manager;
		return manager;
	}

	void requestSceneLoad(SCENE_ID id) {
		nextScene = id;
	}

	void Update(float deltaTime) {
		if (nextScene >= 0) {
			scenes[currScene]->Shutdown();

			currScene = nextScene;
			scenes[currScene]->InitalizeScene();
			nextScene = -1;
		}

		scenes[currScene]->Update(deltaTime);
	}
	void Render() {
		scenes[currScene]->Render();
	}

	void Shutdown() {
		scenes[currScene]->Shutdown();
	}
};