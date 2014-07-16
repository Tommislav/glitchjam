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

using std::vector;

class SpawnFactory {

	private:

		float generatePath(ofVec2f &from, ofVec2f &to, const float &speed, vector<ofVec2f> &popInto) {
			float len = from.distance(to);
			float steps = len / speed;

			float dx = (to.x - from.x) / steps;
			float dy = (to.y - from.y) / steps;
			int count = 0;

			while (count <= steps) {
				ofVec2f p = ofVec2f(
					from.x + (dx * count),
					from.y + (dy * count)
				);
				popInto.push_back(p);
				count++;
			}

			return steps;
		}





		void generatePathFromAnchors(std::vector<ofVec2f> &anchors, const float &speed, std::vector<ofVec2f> &populateInto) {
			for (int i=0; i < anchors.size()-1; i++) {
				ofVec2f &start = anchors[i];
				ofVec2f &end = anchors[i+1];
				generatePath(start, end, speed, populateInto);
			}
		}

		void appendSinCurve(std::vector<ofVec2f> &path, const int& start, const int& end, const float& str, const float& loops=1.0f) {
			float oneLoop = 6.28;
			float tot = oneLoop * loops;
			float steps = end - start;
			float dr = tot / steps;
			int count = 0;
			while (count <= steps) {
				path[start + count].y += (sin(dr * count) * str);
				count++;
			}
		}

		void generateSinPath(std::vector<ofVec2f> &popInto, ofVec2f &from, ofVec2f &to) {
			const float speed = 4;
			ofVec2f start = ofVec2f(0,100);
			ofVec2f end = ofVec2f(800,100);
			float steps = generatePath(start, end, speed, popInto);
			appendSinCurve(popInto, 0, steps, 20);
		}



	public:
		//SpawnFactory();
		//~SpawnFactory();

		void createSwarm(artemis::World& world, int& wave) {
			std::string swarmId = "wave_" + wave;

			std::vector<ofVec2f> anchors;
			anchors.push_back(ofVec2f(50,80));
			anchors.push_back(ofVec2f(800,80));
			anchors.push_back(ofVec2f(800, 250));
			anchors.push_back(ofVec2f(100, 250));
			anchors.push_back(ofVec2f(100, 400));
			anchors.push_back(ofVec2f(800, 400));


			PathComponent *path = new PathComponent();
			generatePathFromAnchors(anchors, 4, path->points);
			appendSinCurve(path->points, 0, 240, 30.0f, 2.0f);

			//ofVec2f from = ofVec2f(0,100);
			//ofVec2f to = ofVec2f(800,100);
			//generateSinPath(path->points, from, to);

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
