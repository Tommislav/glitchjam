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
		int countToNext = factory.createSwarm(*world, gd->wave);
		gd->swarmCountdown = countToNext;
		gd->wave++;
	}

}

GameSystem::~GameSystem() {

}
