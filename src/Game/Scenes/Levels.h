#pragma once
#include "../Game/Scenes/SceneManager.h"
#include "../Game/Utils/ReadObj.h"

struct MainMenu : public Scene {
	char* titleText = "<<SEEING DOUBLE>>";
	char* startText = "Press SPACE or A/X to Start (Controller Recommended!)";
	void AddAssets() override;
};

struct Tutorial : public Scene {
	char* controlsText1 = "KEYBOARD: Arrow Keys to Move, WASD to look around";
	char* controlsText2 = "CONTROLLER: Use Left Stick and Right Stick (Recommended)";
	char* tutorialText2 = "Align your view with the outline to win!";
	void AddAssets() override;
};

struct Station : public Scene {
	Model* postModel;
	Model* tetModel;

	void AddAssets() override;
	void FreeAssets() override;
};

struct Observatory : public Scene {
	Model* tetModel;
	Model* trophyModel;
	Model* roomModel;
	void AddAssets() override;
	void FreeAssets() override;
};

struct EndScreen : public Scene {
	Model* tetModel;
	Model* trophyModel;

	char* victoryString = "YOU WIN!!! Press SPACE or A/X to Restart";
	void AddAssets() override;
	void FreeAssets() override;
};
