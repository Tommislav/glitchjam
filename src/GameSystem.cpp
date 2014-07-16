#include "GameSystem.h"

GameSystem::GameSystem() {
	addComponentType<GameDataComponent>();
}

void GameSystem::spawnEnemy(int& wave) {
	factory.createSwarm(*world, wave);
}







void GameSystem::processEntity(artemis::Entity &e) {
	GameDataComponent *gd = gdMapper.get(e);

	if (--gd->swarmCountdown <= 0) {
		gd->swarmCountdown = 300;
		spawnEnemy(gd->wave);
		gd->wave++;
	}

}

GameSystem::~GameSystem() {

}
