#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/MeshRenderer.h"
#include "../Game/Engine/ECS/Systems/PlayerController.h"
#include "../Game/Engine/ECS/Systems/CheckWin.h"
#include "../Game/Engine/ECS/Systems/Spin.h"
#include "../Game/Engine/ECS/Systems/TextRenderer.h"
#include "../Game/Engine/ECS/Systems/MoveParticles.h"
#include "Scenes/Levels.h"
#include "../ContestAPI/app.h"

using namespace ECS;

void Station::AddAssets() {

	tetModel = readFromFile("./data/TestData/tetrahedron.obj");
	postModel = readFromFile("./data/TestData/post.obj");

	// The Main Cam
	EntityID cam = world->addEntity();
	world->addComponent(cam, Position(0, 0, -75));
	world->addComponent(cam, Rotation(0, 0, 0));
	world->addComponent(cam, Camera(1, 1000));
	world->addComponent(cam, Player());

	// The Goal Camera
	EntityID secondCam = world->addEntity();
	world->addComponent(secondCam, Position(0, 0, 22));
	world->addComponent(secondCam, Rotation(0, 3.14 / 4, 0));
	world->addComponent(secondCam, Camera(Matrix4x4({
		{1064, 0, 0, 0},
		{0, 768, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 1, 0}
		})));
	world->addComponent(secondCam, Material{0.5f, 0.5f, 0.5f, false, false, true});
	world->addComponent(secondCam, GoalPerspective());

	// Right side
	const int NUM_PARTICLES = 400;

	for (int i = 0; i < NUM_PARTICLES; i++) {
		float x = getRand(40, 60);
		float y = getRand(0, 20);
		float z = getRand(-100, 100);

		if (i > NUM_PARTICLES / 2)
			x *= -1;

		float s = getRand(1, 3);

		EntityID tet = world->addEntity();
		world->addComponent(tet, Position(x, y, z));
		world->addComponent(tet, Rotation(x, y, z));
		world->addComponent(tet, Scale{ s });
		world->addComponent(tet, Mesh{ tetModel });
		world->addComponent(tet, Particle());
		world->addComponent(tet, Velocity({ Vec3<float>(0, 0, getRand(0, 0.002)) }));
		world->addComponent(tet, AngularVel({ getRandVec(0, 0.0001)}));
	}

	for (int i = 0; i < 4; i++) {
		EntityID post1 = world->addEntity();
		float x = i > 1 ? 40 : -40;
		float z = i % 2 == 0 ? 50 : 25;
		world->addComponent(post1, Position(x, 0, z));
		world->addComponent(post1, Rotation(0, 3.14 / 2, 0));
		world->addComponent(post1, Scale{ 1.2 });
		world->addComponent(post1, Mesh{ postModel });
		world->addComponent(post1, Material(1, 0.9, 0.9, false, true, false));
	}

	// Register Systems
	world->systems.push_back(new PlayerController(world, Vec3<float>(-25, -50, -100), Vec3<float>(25, 50, 100)));
	world->systems.push_back(new CheckWin(world));
	world->systems.push_back(new MeshRenderer(world));
	world->systems.push_back(new TextRenderer(world));
	world->systems.push_back(new MoveParticles(world, Vec3<float>(-100, -100, -100), Vec3<float>(100, 100, 100), Vec3<float>(0, 0, 0.001f)));
}

void Station::FreeAssets() {
	delete tetModel;
	delete postModel;
}
