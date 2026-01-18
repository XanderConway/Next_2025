#pragma once

#include <bitset>
#include <vector>

namespace ECS {

	const int MAX_ENTITIES = 1024;
	const int MAX_COMPONENTS = 16;

	typedef int EntityID;
	typedef int ComponentID;
	typedef std::bitset< MAX_COMPONENTS> ComponentBits;

	struct Entity {
		EntityID id;
		ComponentBits bitmask;
	};

	// Block of memory allocated for components
	struct ComponentPool {

		char* data;
		size_t compSize;

		ComponentPool(size_t compSize);
		void* get(int i);
		~ComponentPool();
	};

	struct Scene;

	struct System {
		Scene* s;

		System(Scene* s) : s(s) {}

		virtual void Start() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void Shutdown() {}
	};

	struct Scene {
		std::vector<Entity> entities;
		std::vector<ComponentPool*> components;
		std::vector<System*> systems;
		int numComponents = 0;

		EntityID addEntity();

		// Since id is initalized once, calling getId will return a unique id for any class
		template<typename T>
		ComponentID getId() {
			static int id = numComponents;
			return id;
		}

		template<typename T>
		void registerComponentType() {
			ComponentID id = getId<T>();
			numComponents += 1;
			components.push_back(new ComponentPool(sizeof(T)));
		}

		template<typename T>
		void addComponent(EntityID id, T& component) {
			ComponentID compID = getId<T>();

			// We have not established a memory pool for this struct type yet
			if (compID >= components.size()) {
				registerComponentType<T>();
			}

			entities[id].bitmask.set(compID);
			memcpy(components[compID]->get(id), &component, sizeof(T));
		}

		template<typename T>
		bool hasComponent(EntityID id) {
			// We never registered this component, ID must be < numComponents
			if (getId<T>() >= numComponents) {
				return false;
			}

			return entities[id].bitmask.test(getId<T>());
		}

		template<typename T>
		T* getComponent(EntityID id) {
			ComponentID compID = getId<T>();
			return static_cast<T*>(components[compID]->get(id));
		}

		void Start();
		void Update(float deltatime);
		void Render();
	};


	// Since we never add or remove components, we can store all ids in a list
	template<typename... T>
	struct SceneView {
		std::vector<EntityID> entities;

		SceneView(Scene* s) {
			ComponentBits valid;

			ComponentID ids[] = { 0, s->getId<T>() ... };
			for (int i = 1; i < sizeof ...(T) + 1; i++) {
				valid.set(ids[i]);
			}

			for (Entity e : s->entities) {
				if ((valid & e.bitmask) == valid) {
					entities.push_back(e.id);
				}
			}
		}
	};
}