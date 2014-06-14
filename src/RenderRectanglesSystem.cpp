#include "RenderRectanglesSystem.h"
#include "Artemis/Entity.h"
#include <iostream>
#include "ofMain.h"
#include "ofMath.h"


RenderRectanglesSystem::RenderRectanglesSystem()
{
	addComponentType<RectangleComponent>();
	addComponentType<PositionComponent>();
	//std::cout << "RenderRectanglesSystem constructor()" << std::endl;
}


void RenderRectanglesSystem::processEntity(artemis::Entity &e) {
	//std::cout << "processEntity" << std::endl;
	//...
	RectangleComponent *r = (RectangleComponent*)e.getComponent<RectangleComponent>();
	PositionComponent *p = (PositionComponent*)e.getComponent<PositionComponent>();

	ofSetHexColor( r->color );
	ofRect(p->posX, p->posY, r->width, r->height);

	float rnd = ofRandom(0,10);
	if (rnd <= 1) {
		p->posX += 1;
	} else if (rnd <= 2) {
		p->posX -= 1;
	} else if (rnd <= 3) {
		p->posY -= 1;
	} else if (rnd <= 4) {
		p->posY += 1;
	}
}



