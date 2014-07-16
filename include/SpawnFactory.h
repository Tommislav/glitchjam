#ifndef SPAWNFACTORY_H
#define SPAWNFACTORY_H

#include "ofMain.h"
#include <vector>
#include "ofVec2f.h"

#include "PositionComponent.h"
#include "RectangleComponent.h"
#include "VelocityComponent.h"
#include "RemoveEntityConditionComponent.h"
#include "BulletCollidableComponent.h"

#include "PathComponent.h"
#include "SwarmComponent.h"
#include "MothershipComponent.h"

class SpawnFactory {

	private:
		void generatePath(std::vector<ofVec2f> &anchors, float speed, std::vector<ofVec2f> &populateInto) {
			populateInto.push_back(anchors[0]);
			for (int i=0; i < anchors.size()-1; i++) {
				ofVec2f &start = anchors[i];
				ofVec2f &end = anchors[i+1];

				float len = start.distance(end);
				float steps = len / speed;

				float dx = (end.x - start.x) / steps;
				float dy = (end.y - start.y) / steps;


				int count = 0;
				float interpolate = 1 / steps;
				while (steps > 0) {
					ofVec2f p = ofVec2f(
						start.x + (dx * count),
						start.y + (dy * count)
					);

					//std::cout << "create: x:" << p.x << ", y: " << p.y <<std::endl;
					populateInto.push_back(p);
					count++;
					steps -= 1;
				}

			}
		}

		void generateSinPath(std::vector<ofVec2f> &popInto, ofVec2f &from, ofVec2f &to) {
			float speed = 2;
			float len = from.distance(to);
			float steps = len / speed;
			int count;
			float rad = 0;

			float dx = (to.x - from.x) / steps;
			float dy = (to.y - from.y) / steps;
			while (steps > 0) {

				popInto.push_back(ofVec2f(
						from.x + dx * count,
						from.y + sin(rad) * 8
				));
				rad += 0.1;
				steps -= 1;
				count ++;
			}
		}



	public:
		//SpawnFactory();
		//~SpawnFactory();

		void createSwarm(artemis::World& world, int& wave) {
			std::string swarmId = "wave_" + wave;

			std::vector<ofVec2f> anchors;
			anchors.push_back(ofVec2f(50,50));
			anchors.push_back(ofVec2f(800,50));
			anchors.push_back(ofVec2f(800, 250));
			anchors.push_back(ofVec2f(100, 250));
			anchors.push_back(ofVec2f(100, 400));
			anchors.push_back(ofVec2f(800, 400));


			PathComponent *path = new PathComponent();
			//generatePath(anchors, 4, path->points);
			ofVec2f from = ofVec2f(0,100);
			ofVec2f to = ofVec2f(800,100);
			generateSinPath(path->points, from, to);

			artemis::Entity &mother = world.createEntity();
			mother.addComponent(new PositionComponent(anchors[0].x, anchors[0].y));
			mother.addComponent(new RectangleComponent(-20, -20, 40, 40, 0xff0000, 0));
			//mother.addComponent(new VelocityComponent(0, 0));
			mother.addComponent(new RemoveEntityConditionComponent(3000, false));
			mother.addComponent(new BulletCollidableComponent(20, 1, 7));
			mother.addComponent(new MothershipComponent(swarmId));
			mother.addComponent(path);
			mother.refresh();

			world.getGroupManager()->set(swarmId, mother);

			// swarmlings
			std::vector<ofVec2f> swarmOffset;
			swarmOffset.push_back(ofVec2f(-60,0));
			swarmOffset.push_back(ofVec2f(60,0));
			swarmOffset.push_back(ofVec2f(0,-60));
			swarmOffset.push_back(ofVec2f(-120,0));

			for (int i=0; i < swarmOffset.size(); i++) {
				artemis::Entity &swarmling = world.createEntity();
				swarmling.addComponent(new PositionComponent(swarmOffset[i].x, swarmOffset[i].y));
				swarmling.addComponent(new RectangleComponent(-20, -20, 40, 40, 0xffff00, 0));
				swarmling.addComponent(new RemoveEntityConditionComponent(3000, false));
				swarmling.addComponent(new BulletCollidableComponent(20, 1, 4));

				SwarmComponent *sc = new SwarmComponent(swarmId);
				sc->isMother = false;
				sc->hasMother = true;
				sc->mother = &mother;

				if ((wave & 1) == 0) {
					sc->motherOffX = swarmOffset[i].x;
					sc->motherOffY = swarmOffset[i].y;
				} else {
					sc->usePathOffset = true;
					sc->pathOffset = -14 * (i+1);
				}

				swarmling.addComponent(sc);
				swarmling.refresh();

				world.getGroupManager()->set(swarmId, swarmling);
			}
		}
};

#endif // SPAWNFACTORY_H
