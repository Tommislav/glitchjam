#include "RenderRectanglesSystem.h"
#include "Artemis/Entity.h"
#include <iostream>
#include "ofMain.h"
#include "ofMath.h"

int cnt(0);

RenderRectanglesSystem::RenderRectanglesSystem()
{
	addComponentType<RectangleComponent>();
	addComponentType<PositionComponent>();
	//std::cout << "RenderRectanglesSystem constructor()" << std::endl;
}


void RenderRectanglesSystem::processEntity(artemis::Entity &e) {
	RectangleComponent *r = (RectangleComponent*)e.getComponent<RectangleComponent>();
	PositionComponent *p = (PositionComponent*)e.getComponent<PositionComponent>();


	int color = r->color;
	if (++cnt > 24) {
		color = 0xffff00;
		cnt = 0;
	}

	ofSetHexColor( color );
	ofRect(p->posX, p->posY, r->width, r->height);

/*
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
	*/
}



