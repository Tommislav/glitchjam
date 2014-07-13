#ifndef MOVESWARMSYSTEM_H
#define MOVESWARMSYSTEM_H

#include "SwarmComponent.h"

class MoveSwarmSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<SwarmComponent> swarmMapper;
		artemis::ComponentMapper<PositionComponent> posMapper;

	public:
		MoveSwarmSystem() {
			addComponentType<SwarmComponent>();
			addComponentType<PositionComponent>();
		}
		virtual ~MoveSwarmSystem(){}

		virtual void initialize() {
			swarmMapper.init(*world);
			posMapper.init(*world);
		}

		virtual void processEntity(artemis::Entity &e){

			SwarmComponent *sw = (SwarmComponent*) e.getComponent<SwarmComponent>();
			if (sw->hasMother && !sw->isMother) {
				/*
				if (sw->mother == NULL) {
					// mother is dead!
					BulletCollidableComponent *bull = (BulletCollidableComponent*) e.getComponent<BulletCollidableComponent>();
					bull->hp -= ofRand(1,8);
					return;
				}
				*/

				PositionComponent *pos = (PositionComponent*) e.getComponent<PositionComponent>();
				PositionComponent *mPos = (PositionComponent*) sw->mother->getComponent<PositionComponent>();

				pos->posX = mPos->posX + sw->motherOffX;
				pos->posY = mPos->posY + sw->motherOffY;
			}

		}
};

#endif // MOVESWARMSYSTEM_H
