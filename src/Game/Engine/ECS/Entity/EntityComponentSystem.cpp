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

World::World() {
	std::fill(idToPool, idToPool + TOTAL_COMPONENT_TYPES, -1);
}


// Memory pools for components
EntityID World::addEntity() {
	entities.push_back({ (int)entities.size(), ComponentBits() });
	return entities.size() - 1;
}

void World::Start() {
	for (System* s : systems) {
		s->Start();
	}
}

void World::Update(float deltatime) {
	for (System* s : systems) {
		s->Update(deltatime);
	}
}

void World::Render() {
	for (System* s : systems) {
		s->Render();
	}
}

// Clear the worlds memory and assets
void World::Shutdown() {
	for (System* s : systems) {
		s->Shutdown();
	}
	entities.clear();
	for (int i = 0; i < components.size(); i++) {
		delete components[i];
	}
	components.clear();

	for (int i = 0; i < systems.size(); i++) {
		delete systems[i];
	}
	systems.clear();

}


