#ifndef MOVEWITHPATHSYSTEM_H_INCLUDED
#define MOVEWITHPATHSYSTEM_H_INCLUDED

#include "PathComponent.h"
#include <iostream>

class MoveWithPathSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<PositionComponent> posMapper;
		artemis::ComponentMapper<PathComponent> pathMapper;
		//artemis::ComponentMapper<VelocityComponent> velMapper;

	public:
		MoveWithPathSystem() {
			addComponentType<PositionComponent>();
			addComponentType<PathComponent>();
			//addComponentType<VelocityComponent>();
		}

		virtual ~MoveWithPathSystem() {}

		virtual void initialize() {
			posMapper.init(*world);
			pathMapper.init(*world);
			//velMapper.init(*world);
		}

		virtual void processEntity(artemis::Entity &e) {
			PositionComponent *pos = posMapper.get(e);
			PathComponent *path = pathMapper.get(e);
			//VelocityComponent *vel = velMapper.get(e);

			int &index = path->currentIndex;
			vector<ofVec2f> &points = path->points;
			int size = points.size();

			/*
			for (int i=0; i<points.size(); i++) {
				std::cout << "move x:" << points[i].x << ", y: " << points[i].y <<std::endl;
			}
			*/


			if (index >= points.size()) {
				// scatter or follow player
				float rad = ofRandom(0,6.28);
				float speed = 12;

				VelocityComponent *vel = new VelocityComponent(cos(rad)*speed, sin(rad)*speed);
				e.addComponent(vel);
				e.removeComponent<PathComponent>();
				e.refresh();

				//ofVec2f &p = points[points.size()-1];
				//pos->posX += p.x;
				//pos->posY += p.y;


			} else {
				ofVec2f &p = points[index];
				//std::cout << "sys: position rect at " << p.x << ", " << p.y << std::endl;
				pos->posX = p.x;
				pos->posY = p.y;
				index += 1;
			}

			//std::cout << "pos: " << pos->posX << ", " << pos->posY << std::endl;
		}
};

#endif // MOVEWITHPATHSYSTEM_H_INCLUDED
