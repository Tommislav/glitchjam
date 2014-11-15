#ifndef MOVEWITHPATHSYSTEM_H_INCLUDED
#define MOVEWITHPATHSYSTEM_H_INCLUDED

#include "PathComponent.h"
#include <iostream>

class MoveWithPathSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<PositionComponent> posMapper;
		artemis::ComponentMapper<PathComponent> pathMapper;

	public:
		MoveWithPathSystem() {
			addComponentType<PositionComponent>();
			addComponentType<PathComponent>();
		}

		virtual ~MoveWithPathSystem() {}

		virtual void initialize() {
			posMapper.init(*world);
			pathMapper.init(*world);
		}

		virtual void processEntity(artemis::Entity &e) {
			PositionComponent *pos = posMapper.get(e);
			PathComponent *path = pathMapper.get(e);
			
			int &startCountdown = path->pauseCountdown;
			if (startCountdown > 0) {
				startCountdown--;
				return;
			}


			int &index = path->currentIndex;
			vector<ofVec2f> &points = path->points;
			int size = points.size();


			if (index >= size) {
				// scatter or follow player
				float rad = ofRandom(0,6.28);
				float speed = 12;

				VelocityComponent *vel = new VelocityComponent(cos(rad)*speed, sin(rad)*speed);
				e.addComponent(vel);
				e.removeComponent<PathComponent>();
				e.refresh();

			} else {
				ofVec2f &p = points[index];
				
				pos->posX = p.x;
				pos->posY = p.y;
				index += 1;
			}
		}
};

#endif // MOVEWITHPATHSYSTEM_H_INCLUDED
