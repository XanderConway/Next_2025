#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/MeshRenderer.h"
#include "../Game/Engine/ECS/Systems/TextRenderer.h"
#include "../Game/Engine/ECS/Systems/MoveParticles.h"
#include "../Game/Engine/ECS/Systems/MenuController.h"
#include "Scenes/Levels.h"
#include "../ContestAPI/app.h"


using namespace ECS;

void EndScreen::AddAssets() {

	tetModel = readFromFile("./data/TestData/tetrahedron.obj");
	trophyModel = readFromFile("./data/TestData/trophy.obj");

	// The Main Cam
	EntityID cam = world->addEntity();
	world->addComponent(cam, Position(0, 0, -75));
	world->addComponent(cam, Rotation(0, 0, 0));
	world->addComponent(cam, Camera(1, 1000));

	const int NUM_PARTICLES = 800;

	for (int i = 0; i < NUM_PARTICLES; i++) {

		float s = getRand(0.1, 0.3);

		EntityID tet = world->addEntity();
		world->addComponent(tet, Position(getRandVec(-50, 50)));
		world->addComponent(tet, Rotation(getRandVec(-1, 1)));
		world->addComponent(tet, Scale{ s });
		world->addComponent(tet, Mesh{ tetModel });
		world->addComponent(tet, Particle());
		world->addComponent(tet, Velocity{ getRandVec(-0.001, 0.001) });
		world->addComponent(tet, AngularVel{ Vec3<float>(0.0, 0.0, getRand(0, 0.001)) });
		world->addComponent(tet, Material{ 1, 1, getRand(0.5f, 1), false, true, false });
	}

	EntityID victoryMessage = world->addEntity();
	world->addComponent(victoryMessage, Text(victoryString, 300, 60, GLUT_BITMAP_TIMES_ROMAN_24));
	world->addComponent(victoryMessage, Material{ 1, 1, 1 });

	// Trophy
	const float GRAVITY = -0.002;
	EntityID trophy = world->addEntity();
	world->addComponent(trophy, Position(0, 0, 0));
	world->addComponent(trophy, Rotation(0.5, 0, 0));
	world->addComponent(trophy, Scale{ 3 });
	world->addComponent(trophy, Mesh{ trophyModel });
	world->addComponent(trophy, Material{ 1, 1, 0.7, false, true, false });
	world->addComponent(trophy, Velocity{ Vec3<float>(0, -GRAVITY, 0) }); // ;)
	world->addComponent(trophy, Particle());
	world->addComponent(trophy, AngularVel{ Vec3<float>(0, 0.001, 0) });

	// Register Systems
	world->systems.push_back(new MeshRenderer(world));
	world->systems.push_back(new TextRenderer(world));
	world->systems.push_back(new MoveParticles(world, Vec3<float>(-50, -50, -50), Vec3<float>(50, 50, 50), Vec3<float>(0, GRAVITY, 0)));
	world->systems.push_back(new MenuController(world, 0));
}

void EndScreen::FreeAssets() {
	delete trophyModel;
	delete tetModel;
}
