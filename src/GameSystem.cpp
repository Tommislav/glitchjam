#include "GameSystem.h"
#include "ofMain.h"

#include "PositionComponent.h"
#include "RectangleComponent.h"
#include "VelocityComponent.h"
#include "RemoveEntityConditionComponent.h"
#include "BulletCollidableComponent.h"

#include "PathComponent.h"
#include "SwarmComponent.h"

GameSystem::GameSystem() {
	addComponentType<GameDataComponent>();
}


void GameSystem::generatePath(std::vector<ofVec2f> &anchors, float speed, std::vector<ofVec2f> &populateInto) {
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




void GameSystem::spawnEnemy() {

	int swarmId = 1;

	std::vector<ofVec2f> anchors;
	anchors.push_back(ofVec2f(50,50));
	anchors.push_back(ofVec2f(800,50));
	anchors.push_back(ofVec2f(800, 250));
	anchors.push_back(ofVec2f(100, 250));
	anchors.push_back(ofVec2f(100, 400));
	anchors.push_back(ofVec2f(800, 400));


	PathComponent *path = new PathComponent();
	generatePath(anchors, 6, path->points);

	artemis::Entity &mother = world->createEntity();
	mother.addComponent(new PositionComponent(anchors[0].x, anchors[0].y));
	mother.addComponent(new RectangleComponent(-20, -20, 40, 40, 0xff0000, 0));
	//mother.addComponent(new VelocityComponent(0, 0));
	mother.addComponent(new RemoveEntityConditionComponent(999, false));
	mother.addComponent(new BulletCollidableComponent(20, 1, 7));
	mother.addComponent(path);

	SwarmComponent *ms = new SwarmComponent(swarmId);
	ms->isMother = true;
	ms->hasMother = false;
	ms->mother = NULL;
	mother.addComponent(ms);

	mother.refresh();


	// swarmlings
	std::vector<ofVec2f> swarmOffset;
	swarmOffset.push_back(ofVec2f(-60,0));
	swarmOffset.push_back(ofVec2f(60,0));
	swarmOffset.push_back(ofVec2f(0,-60));
	swarmOffset.push_back(ofVec2f(0,60));

	for (int i=0; i < swarmOffset.size(); i++) {
		artemis::Entity &swarmling = world->createEntity();
		swarmling.addComponent(new PositionComponent(swarmOffset[i].x, swarmOffset[i].y));
		swarmling.addComponent(new RectangleComponent(-20, -20, 40, 40, 0xffff00, 0));
		swarmling.addComponent(new RemoveEntityConditionComponent(600, false));
		swarmling.addComponent(new BulletCollidableComponent(20, 1, 4));

		SwarmComponent *sc = new SwarmComponent(swarmId);
		sc->isMother = false;
		sc->hasMother = true;
		sc->mother = &mother;
		sc->motherOffX = swarmOffset[i].x;
		sc->motherOffY = swarmOffset[i].y;

		swarmling.addComponent(sc);
		swarmling.refresh();
	}


}







void GameSystem::processEntity(artemis::Entity &e) {
	GameDataComponent *gd = gdMapper.get(e);

	if (--gd->swarmCountdown <= 0) {
		gd->swarmCountdown = 9999;
		spawnEnemy();
	}

}

GameSystem::~GameSystem() {

}
