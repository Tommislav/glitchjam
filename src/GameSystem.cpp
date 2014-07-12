#include "GameSystem.h"
#include "ofMain.h"

#include "PositionComponent.h"
#include "RectangleComponent.h"
#include "VelocityComponent.h"
#include "RemoveEntityConditionComponent.h"
#include "BulletCollidableComponent.h"

#include "PathComponent.h"

GameSystem::GameSystem() {
	addComponentType<GameDataComponent>();
}


void GameSystem::generatePath(std::vector<ofVec2f> &anchors, float speed, std::vector<ofVec2f> &populateInto) {
	populateInto.push_back(anchors[0]);

	std::cout << "lala " << anchors.size() << std::endl;

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
	float x=30;
	float y=ofRandom(30,200);
	float vX=ofRandom(0.1, 1);
	float vY=ofRandom(0.1, 0.5);

	std::vector<ofVec2f> anchors;
	anchors.push_back(ofVec2f(50,50));
	anchors.push_back(ofVec2f(800,50));
	anchors.push_back(ofVec2f(800, 250));
	anchors.push_back(ofVec2f(100, 250));
	anchors.push_back(ofVec2f(100, 400));
	anchors.push_back(ofVec2f(800, 400));

	PathComponent *path = new PathComponent();
	generatePath(anchors, 2, path->points);

	artemis::Entity &enemy = world->createEntity();
	enemy.addComponent(new PositionComponent(50, 50));
	enemy.addComponent(new RectangleComponent(-20, -20, 40, 40, 0xff0000, 0));
	//enemy.addComponent(new VelocityComponent(0, 0));
	enemy.addComponent(new RemoveEntityConditionComponent(99999, true));
	enemy.addComponent(new BulletCollidableComponent(20, 1, 7));
	enemy.addComponent(path);
	enemy.refresh();


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
