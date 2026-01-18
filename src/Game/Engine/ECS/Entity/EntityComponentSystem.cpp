#pragma once
#include "../Game/Engine/ECS/Entity/EntityComponentSystem.h"
#include <bitset>
#include <vector>

using namespace ECS;

// Block of memory allocated for components
ComponentPool::ComponentPool(size_t compSize) : compSize(compSize) {
	data = new char[compSize * MAX_ENTITIES];
}

void* ComponentPool::get(int i) {
	return &data[i * compSize];
}

ComponentPool::~ComponentPool() {
	delete[] data;
}


// Memory pools for components
EntityID Scene::addEntity() {
	entities.push_back({ (int)entities.size(), ComponentBits() });
	return entities.size() - 1;
}


void Scene::Start() {
	for (System* s : systems) {
		s->Start();
	}
}

void Scene::Update(float deltatime) {
	for (System* s : systems) {
		s->Update(deltatime);
	}
}

void Scene::Render() {
	for (System* s : systems) {
		s->Render();
	}
}

