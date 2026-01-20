#include "../Game/Engine/ECS/Components/Components.h"
#include "../Game/Engine/ECS/Systems/MeshRenderer.h"
#include "../Game/Engine/ECS/Systems/PlayerController.h"
#include "../Game/Engine/ECS/Systems/CheckWin.h"
#include "../Game/Engine/ECS/Systems/TextRenderer.h"
#include "../Game/Engine/ECS/Systems/MoveParticles.h"
#include "Scenes/Levels.h"
#include "../ContestAPI/app.h"


using namespace ECS;

void Observatory::AddAssets() {

	tetModel = readFromFile("./data/TestData/tetrahedron.obj");
	trophyModel = readFromFile("./data/TestData/trophy.obj");

	// The Main Cam
	EntityID cam = world->addEntity();
	world->addComponent(cam, Position(0, 0, -75));
	world->addComponent(cam, Rotation(0, 0, 0));
	world->addComponent(cam, Camera(1, 1000));
	world->addComponent(cam, Player());

	// The Goal Camera
	EntityID secondCam = world->addEntity();
	world->addComponent(secondCam, Position(10, 0, 80));
	world->addComponent(secondCam, Rotation(0, -2.3, 0));
	world->addComponent(secondCam, Camera(Matrix4x4({
		{1064, 0, 0, 0},
		{0, 768, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 1, 0}
		})));
	world->addComponent(secondCam, Material{0.5f, 0.5f, 0.5f, false, false, true});
	world->addComponent(secondCam, GoalPerspective());

	const int NUM_PARTICLES = 1600;

	for (int i = 0; i < NUM_PARTICLES; i++) {

		float s = getRand(1, 3);

		EntityID tet = world->addEntity();
		world->addComponent(tet, Position(getRandVec(-100, 100)));
		world->addComponent(tet, Rotation(getRandVec(-1, 1)));
		world->addComponent(tet, Scale{ s });
		world->addComponent(tet, Mesh{ tetModel });
		world->addComponent(tet, Particle());
		world->addComponent(tet, Velocity{getRandVec(-0.003, 0.003)});
		world->addComponent(tet, AngularVel{ Vec3<float>(0.0, 0.0, getRand(0, 0.001)) });
		world->addComponent(tet, Material{ getRand(0.5f, 1), getRand(0.5f, 1), getRand(0.5f, 1), false, true, false });
	}

	// Trophy
	EntityID trophy = world->addEntity();
	world->addComponent(trophy, Position(40, -5, 50));
	world->addComponent(trophy, Rotation(0, 2, 0));
	world->addComponent(trophy, Scale{ 0.8 });
	world->addComponent(trophy, Mesh{ trophyModel });
	world->addComponent(trophy, Material{ 1, 1, 0.7, false, true, false });

	// The Room Model
	roomModel = readFromFile("./data/TestData/room.obj");
	EntityID room = world->addEntity();
	world->addComponent(room, Position(0, 0, 0));
	world->addComponent(room, Rotation(0, 0, 0));
	world->addComponent(room, Scale{ 200 });
	world->addComponent(room, Mesh{ roomModel });
	world->addComponent(room, Material(0.5, 0, 0, false, false, true));

	// Register Systems
	world->systems.push_back(new PlayerController(world));
	world->systems.push_back(new CheckWin(world));
	world->systems.push_back(new MeshRenderer(world));
	world->systems.push_back(new TextRenderer(world));
	world->systems.push_back(new MoveParticles(world, Vec3<float>(-100, -100, -100), Vec3<float>(100, 100, 100), Vec3<float>()));
}

void Observatory::FreeAssets() {
	delete trophyModel;
	delete tetModel;
	delete roomModel;
}
