#pragma once

#include <bitset>
#include <vector>

namespace ECS {

	const int MAX_ENTITIES = 1024;
	const int COMPONENTS_PER_ECS = 32;
	const int TOTAL_COMPONENT_TYPES = 128;

	typedef int EntityID;
	typedef int ComponentID;
	typedef int PoolID;
	typedef std::bitset<COMPONENTS_PER_ECS> ComponentBits;

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

	struct World;

	struct System {
		World* s;

		System(World* s) : s(s) {}

		virtual void Start() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void Shutdown() {}
	};

	struct World {
		std::vector<Entity> entities;
		std::vector<ComponentPool*> components;
		std::vector<System*> systems;
		int numComponents = 0;

		// Map Component Types to their pools, required since getTypeId can be called for componenents that aren't registered
		PoolID idToPool[TOTAL_COMPONENT_TYPES];

		EntityID addEntity();

		// Whenever getTypeID is called for a new type, it will increment this value
		ComponentID getNextId() {
			static ComponentID id = -1;
			id += 1;
			return id;
		}

		// Since id is initalized once, calling getId will return a unique id for any class
		template<typename T>
		ComponentID getTypeId() {
			static int id = getNextId();
			return id;
		}

		World::World();

		template<typename T>
		PoolID registerComponentType() {
			ComponentID id = getTypeId<T>();
			components.push_back(new ComponentPool(sizeof(T)));
			idToPool[id] = components.size() - 1;
			return idToPool[id];
		}

		PoolID getPoolID(ComponentID id) {
			return idToPool[id];
		}

		template<typename T>
		void addComponent(EntityID id, const T& component) {
			ComponentID compID = getTypeId<T>();
			PoolID poolId = idToPool[compID];

			// We have not established a memory pool for this struct type yet
			if (poolId < 0) {
				poolId = registerComponentType<T>();
			}

			entities[id].bitmask.set(poolId);
			memcpy(components[poolId]->get(id), &component, sizeof(T));
		}

		template<typename T>
		bool hasComponent(EntityID id) {
			// We never registered this component
			PoolID poolId = idToPool[getTypeId<T>()];
			if (poolId < 0) {
				return false;
			}

			return entities[id].bitmask.test(poolId);
		}

		// Assumes that the type has been registered
		template<typename T>
		T* getComponent(EntityID id) {
			ComponentID compID = getTypeId<T>();
			int poolId = getPoolID(compID);
			return static_cast<T*>(components[poolId]->get(id));
		}

		void Start();
		void Update(float deltatime);
		void Render();
		void Shutdown();
	};


	// Since we never add or remove components, we can store all ids in a list
	template<typename... T>
	struct SceneView {
		std::vector<EntityID> entities;

		SceneView(World* s) {
			ComponentBits valid;

			ComponentID ids[] = { 0, s->getTypeId<T>() ... };
			for (int i = 1; i < sizeof ...(T) + 1; i++) {
				PoolID pID = s->getPoolID(ids[i]);

				// There are no entities with this component type, return
				if (pID < 0) {
					return;
				}
				valid.set(pID);
			}

			for (Entity e : s->entities) {
				if ((valid & e.bitmask) == valid) {
					entities.push_back(e.id);
				}
			}
		}
	};
}