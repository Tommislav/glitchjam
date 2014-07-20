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

		float generatePath(ofVec2f from, ofVec2f to, const float &speed, vector<ofVec2f> &popInto) {
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

		void generatePause(ofVec2f at, const int &wait, vector<ofVec2f> &popInto) {
			for (int i = 0; i < wait; i++) {
				popInto.push_back(at);
			}
		}




		void generatePathFromAnchors(std::vector<ofVec2f> &anchors, const float &speed, std::vector<ofVec2f> &populateInto) {
			for (int i=0; i < anchors.size()-1; i++) {
				ofVec2f &start = anchors[i];
				ofVec2f &end = anchors[i+1];
				generatePath(start, end, speed, populateInto);
			}
		}

		void appendSinCurve(std::vector<ofVec2f> &path, const int& start, const int& end, const float& str, const float& loops=1.0f, bool bobY=true, bool bobX=false) {
			float oneLoop = 6.28;
			float tot = oneLoop * loops;
			float steps = end - start;
			float dr = tot / steps;
			int count = 0;
			while (count <= steps) {
				if (bobY) {
					path[start + count].y += (sin(dr * count - 1.57) * str) + str;
				}
				if (bobX) {
					path[start + count].x += (sin(dr * count) * str);
				}

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

		// Returns the wait-time until we should be called again for a new swarm
		int createSwarm(artemis::World& world, int& wave) {
			std::string swarmId = "wave_" + wave;

			bool usePathOffset = false;
			int pathOffset = -14;
			std::vector<ofVec2f> swarmOffset;
			PathComponent *path = new PathComponent();
			int timeToNext = 240;

			int mothershipHp = 20;

			float s1 = 0;
			float s2 = 0;
			float s3 = 0;
			float s4 = 0;
			float s5 = 0;
			float s6 = 0;


			if (wave == 0) {
				s1 = generatePath(ofVec2f(-250, 180), ofVec2f(800, 180), 1, path->points);
				s2 = generatePath(ofVec2f(800,180), ofVec2f(800, 280), 1, path->points);
				s3 = generatePath(ofVec2f(800, 280), ofVec2f(100, 280), 1, path->points);
				s4 = generatePath(ofVec2f(100, 280), ofVec2f(100, 80), 1, path->points);
				s5 = generatePath(ofVec2f(100, 80), ofVec2f(1024+400, 80), 1, path->points);

				usePathOffset = false;
				pathOffset = 28;
				timeToNext = 60*16;
				mothershipHp = 30;


				swarmOffset.push_back(ofVec2f(-50,50));
				swarmOffset.push_back(ofVec2f(-50,0));
				swarmOffset.push_back(ofVec2f(0,50));
				swarmOffset.push_back(ofVec2f(50,0));
				swarmOffset.push_back(ofVec2f(50,50));
				swarmOffset.push_back(ofVec2f(100,0));
				swarmOffset.push_back(ofVec2f(100,50));
				swarmOffset.push_back(ofVec2f(100,100));
				swarmOffset.push_back(ofVec2f(150,0));
				swarmOffset.push_back(ofVec2f(150,50));
				swarmOffset.push_back(ofVec2f(150,100));
				swarmOffset.push_back(ofVec2f(200,0));
				swarmOffset.push_back(ofVec2f(200,50));
				swarmOffset.push_back(ofVec2f(200,100));

			} else if (wave == 1) {
				s1 = generatePath(ofVec2f(-20, 80), ofVec2f(800, 80), 3, path->points);
				s2 = generatePath(ofVec2f(800,80), ofVec2f(800, 280), 3, path->points);
				s3 = generatePath(ofVec2f(800, 280), ofVec2f(100, 280), 3, path->points);
				s4 = generatePath(ofVec2f(100, 280), ofVec2f(100, 80), 3, path->points);
				s5 = generatePath(ofVec2f(100, 80), ofVec2f(1024+400, 80), 3, path->points);
				appendSinCurve(path->points, s1+s2, s1+s2+s3-1, 30, 3, true, false);
				appendSinCurve(path->points, s1+s2+s3+s4, s1+s2+s3+s4+s5-1, 50, 6, true, false);
				usePathOffset = true;
				pathOffset = 20;
				timeToNext = 100;

				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));

			} else if (wave == 2) {
				s1 = generatePath(ofVec2f(1044, 120), ofVec2f(220, 120), 4, path->points);
				s2 = generatePath(ofVec2f(220,120), ofVec2f(220, 320), 4, path->points);
				s3 = generatePath(ofVec2f(220, 320), ofVec2f(924, 320), 4, path->points);
				s4 = generatePath(ofVec2f(924, 320), ofVec2f(924, 120), 4, path->points);
				s5 = generatePath(ofVec2f(924, 120), ofVec2f(-400, 120), 4, path->points);
				appendSinCurve(path->points, 0, s1, 14, 3, true, false);
				appendSinCurve(path->points, s1+s2, s1+s2+s3-1, 30, 3, true, false);
				appendSinCurve(path->points, s1+s2+s3+s4, s1+s2+s3+s4+s5-1, 50, 6, true, false);
				usePathOffset = true;
				timeToNext = 100;//60*5;

				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));

			} else if (wave == 3) { // <<----------
				s1 = generatePath(ofVec2f(-20, 180), ofVec2f(600, 180), 2, path->points);
				s2 = generatePath(ofVec2f(600,180), ofVec2f(600, 400), 2, path->points);
				s3 = generatePath(ofVec2f(600, 400), ofVec2f(250, 400), 2, path->points);
				s4 = generatePath(ofVec2f(250, 400), ofVec2f(250, 180), 2, path->points);
				s5 = generatePath(ofVec2f(250, 180), ofVec2f(1024+400, 250), 3, path->points);
				appendSinCurve(path->points, 0, s1, 30, 5, false, true);
				appendSinCurve(path->points, s1+s2, s1+s2+s3-1, 30, 3, true, false);
				appendSinCurve(path->points, s1+s2+s3+s4, s1+s2+s3+s4+s5-1, 50, 6, true, false);
				usePathOffset = true;
				pathOffset = 28;
				timeToNext = 60*5;

				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));


			} else if (wave == 4 || wave == 6 || wave == 8) {
				s1 = generatePath(ofVec2f(400,-120), ofVec2f(400,800), 1, path->points);

				swarmOffset.push_back(ofVec2f(0,50));
				swarmOffset.push_back(ofVec2f(-50,50));
				swarmOffset.push_back(ofVec2f(50,50));
				swarmOffset.push_back(ofVec2f(-100,50));
				swarmOffset.push_back(ofVec2f(100,50));

				timeToNext = 200;

			} else if (wave == 5 || wave == 7 || wave == 9) {
				s1 = generatePath(ofVec2f(620,-120), ofVec2f(620,800), 1, path->points);

				swarmOffset.push_back(ofVec2f(0,50));
				swarmOffset.push_back(ofVec2f(-50,50));
				swarmOffset.push_back(ofVec2f(50,50));
				swarmOffset.push_back(ofVec2f(-100,50));
				swarmOffset.push_back(ofVec2f(100,50));


				timeToNext = (wave == 9) ? 4 * 50 : 100;

			} else if (wave == 10) {
				s1 = generatePath(ofVec2f(500, -100), ofVec2f(500, 250), 4, path->points);
				s2 = 320;
				generatePause(ofVec2f(500,250), s2, path->points);
				s3 = generatePath(ofVec2f(500,250), ofVec2f(1024 + 600,250), 3, path->points);
				appendSinCurve(path->points, s1, s1+s2-1, 240, 1, true, true);
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				swarmOffset.push_back(ofVec2f(0,0));
				usePathOffset = true;
				timeToNext = 60*120;
			}


			//float s1 = generatePath(ofVec2f(0,100), ofVec2f(800,100), 2, path->points);
			//appendSinCurve(path->points, 20, s1-1, 30.0f, 2, true, false);
			/*
			float s1= 0;
			float s2 = generatePath(ofVec2f(800,100), ofVec2f(700, 300), 1, path->points);
			appendSinCurve(path->points, s1+20, s2-80, 30.0f, 2, false, true);
			generatePause(ofVec2f(700, 300), 240, path->points);
			appendSinCurve(path->points, s2, s2+240, 120, 1, true, true);
			float s3 = generatePath(ofVec2f(700, 300), ofVec2f(500, -40), 4, path->points);
			appendSinCurve(path->points, s2+240, s3-1, 20, 1, false, true);
			*/
			//ofVec2f from = ofVec2f(0,100);
			//ofVec2f to = ofVec2f(800,100);
			//generateSinPath(path->points, from, to);









			artemis::Entity &mother = world.createEntity();
			mother.addComponent(new PositionComponent(path->points[0].x, path->points[0].y));
			mother.addComponent(new RectangleComponent(-20, -20, 40, 40, 0xff0000, 0));
			mother.addComponent(new RemoveEntityConditionComponent(3000, false));
			mother.addComponent(new BulletCollidableComponent(mothershipHp, 1, 7));
			mother.addComponent(new MothershipComponent(swarmId));
			mother.addComponent(path);
			mother.refresh();

			world.getGroupManager()->set(swarmId, mother);

			// swarmlings
			/*
			std::vector<ofVec2f> swarmOffset;
			swarmOffset.push_back(ofVec2f(-60,0));
			swarmOffset.push_back(ofVec2f(60,0));
			swarmOffset.push_back(ofVec2f(0,-60));
			swarmOffset.push_back(ofVec2f(-120,0));
			*/

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


				sc->motherOffX = swarmOffset[i].x;
				sc->motherOffY = swarmOffset[i].y;

				sc->usePathOffset = usePathOffset;
				sc->pathOffset = pathOffset * (i+1);


				swarmling.addComponent(sc);
				swarmling.refresh();

				world.getGroupManager()->set(swarmId, swarmling);
			}

			return timeToNext;
		}
};

#endif // SPAWNFACTORY_H
