#include "PositionComponent.h"
#include "ofMain.h"

PositionComponent::PositionComponent(float posX, float posY)
{
	this->posX = posX;
	this->posY = posY;
}

void PositionComponent::drawSomething() {
	ofSetColor(255, 0, 0);
	ofRect(posX, posY, 50, 120);
}

PositionComponent::~PositionComponent()
{
	//dtor
}
