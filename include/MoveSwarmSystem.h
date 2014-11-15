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
				PathComponent *mPath = (PathComponent*) sw->mother->getComponent<PathComponent>();
				if (mPos == NULL || mPath == NULL) {
					return;
				}

				if (sw->usePathOffset) {
					int max = mPath->points.size();
					int n = mPath->currentIndex + sw->pathOffset;
					if (n < 0) n = 0;
					if (n > max -1) n = max -1;

					pos->posX = mPath->points[n].x + sw->motherOffX;
					pos->posY = mPath->points[n].y + sw->motherOffY;

				} else {
					pos->posX = mPos->posX + sw->motherOffX;
					pos->posY = mPos->posY + sw->motherOffY;
				}

			} else if (!sw->hasMother) {

				BulletCollidableComponent *bull = (BulletCollidableComponent*) e.getComponent<BulletCollidableComponent>();
				bull->hp -= 20;
			}
		}
};

#endif // MOVESWARMSYSTEM_H
