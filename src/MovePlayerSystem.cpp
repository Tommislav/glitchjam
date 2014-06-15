#include "MovePlayerSystem.h"
#include "Artemis/Entity.h"
#include <iostream>

MovePlayerSystem::MovePlayerSystem(PlayerInputComponent &input):input(input)
{
	addComponentType<InputControllableComponent>();
}

MovePlayerSystem::~MovePlayerSystem() {}


void MovePlayerSystem::processEntity(artemis::Entity &e) {

	//PlayerInputComponent *input 	= (PlayerInputComponent*)e.getComponent<PlayerInputComponent>();
	VelocityComponent *vel 			= (VelocityComponent*)e.getComponent<VelocityComponent>();
	PositionComponent *pos 			= (PositionComponent*)e.getComponent<PositionComponent>();

	vel->vX = 0;
	vel->vY = 0;

	if (input.up()) {
		vel->vY -= 1;
	}
	if (input.down()) {
		vel->vY += 1;
	}
	if (input.left()) {
		vel->vX -= 1;
	}
	if (input.right()) {
		vel->vX += 1;
	}

	pos->posX += vel->vX;
	pos->posY += vel->vY;
}



