#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <vector>
#include "ofVec2f.h"

#include <Artemis/EntityProcessingSystem.h>
#include "Artemis/ComponentMapper.h"
#include "Artemis/Entity.h"
#include "GameDataComponent.h"

class GameSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<GameDataComponent> gdMapper;

	public:
		GameSystem();
		virtual ~GameSystem();

		virtual void initialize() {
			gdMapper.init(*world);
		}

		virtual void processEntity(artemis::Entity &e);



	private:
		void spawnEnemy(int& waveNum);
		void generatePath(std::vector<ofVec2f> &anchors, float speed, std::vector<ofVec2f> &populateInto);
};

#endif // GAMESYSTEM_H
