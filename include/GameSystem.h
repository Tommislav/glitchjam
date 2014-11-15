#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include "Artemis/ComponentMapper.h"
#include "Artemis/Entity.h"
#include "GameDataComponent.h"
#include "SpawnFactory.h"

class GameSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<GameDataComponent> gdMapper;
		SpawnFactory factory;
		void spawnEnemy(int& waveNum);
		//void generatePath(std::vector<ofVec2f> &anchors, float speed, std::vector<ofVec2f> &populateInto);
		//void generateSinPath(std::vector<ofVec2f> &popInto, ofVec2f &from, ofVec2f &to);

	public:
		GameSystem();
		virtual ~GameSystem();

		virtual void initialize() {
			gdMapper.init(*world);
		}

		virtual void processEntity(artemis::Entity &e);

};

#endif // GAMESYSTEM_H
