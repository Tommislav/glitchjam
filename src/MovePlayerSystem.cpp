#include "MovePlayerSystem.h"
#include "Artemis/Entity.h"
#include <iostream>

MovePlayerSystem::MovePlayerSystem(PlayerInputComponent &input):input(input)
{
	addComponentType<InputControllableComponent>();
}

MovePlayerSystem::~MovePlayerSystem() {}


void clamp(float &val, float min, float max) {
	if (val < min) val = min;
	if (val > max) val = max;
}

void MovePlayerSystem::processEntity(artemis::Entity &e) {

	//PlayerInputComponent *input 	= (PlayerInputComponent*)e.getComponent<PlayerInputComponent>();
	VelocityComponent *vel 			= (VelocityComponent*)e.getComponent<VelocityComponent>();
	PositionComponent *pos 			= (PositionComponent*)e.getComponent<PositionComponent>();

	bool vert = (input.up() || input.down());
	bool horis = (input.left() || input.right());

	if (!vert) {
		vel->vY *= 0.96;
	}

	if (!horis) {
		vel->vX *= 0.96;
	}

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

	float maxSpeed = 8;
	clamp(vel->vX, -maxSpeed, maxSpeed);
	clamp(vel->vY, -maxSpeed, maxSpeed);

	pos->posX += vel->vX;
	pos->posY += vel->vY;
}



