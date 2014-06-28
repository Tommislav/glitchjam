#include "MovePlayerSystem.h"
#include "Artemis/Entity.h"
#include <iostream>
#include "ofMain.h"

MovePlayerSystem::MovePlayerSystem():inputMask(0), up(false), down(false) {
	ofRegisterKeyEvents(this);
	addComponentType<VelocityComponent>();
	addComponentType<PlayerComponent>();
}

MovePlayerSystem::~MovePlayerSystem() {
	ofUnregisterKeyEvents(this);
}

void MovePlayerSystem::initialize() {
	velocityMapper.init(*world);
	playerMapper.init(*world);
	//cameraMapper.init(*world);
}


void clamp(float &val, float const &min, float const &max) {
	if (val < min) val = min;
	if (val > max) val = max;
}


void MovePlayerSystem::begin() {
	up 		= this->inputMask & MovePlayerSystem::MOVE_UP;
	down 	= this->inputMask & MovePlayerSystem::MOVE_DOWN;
	left 	= this->inputMask & MovePlayerSystem::MOVE_LEFT;
	right 	= this->inputMask & MovePlayerSystem::MOVE_RIGHT;

	vert = (up || down);
	horis = (left || right);
}

void MovePlayerSystem::processEntity(artemis::Entity &e) {

	if (((PlayerComponent*)e.getComponent<PlayerComponent>())->type != 0) {
		return;
	}

	//PlayerInputComponent *input 	= (PlayerInputComponent*)e.getComponent<PlayerInputComponent>();
	VelocityComponent *vel 			= (VelocityComponent*)e.getComponent<VelocityComponent>();
	//PositionComponent *pos 			= (PositionComponent*)e.getComponent<PositionComponent>();

	if (!vert) {
		vel->vY *= 0.96;
	}

	if (!horis) {
		vel->vX *= 0.96;
	}

	if (up) {
		vel->vY -= 1;
	}
	if (down) {
		vel->vY += 1;
	}
	if (left) {
		vel->vX -= 1;
	}
	if (right) {
		vel->vX += 1;
	}

	float maxSpeed = 8;
	clamp(vel->vX, -maxSpeed, maxSpeed);
	clamp(vel->vY, -maxSpeed, maxSpeed);

}

void MovePlayerSystem::end() {
}

void MovePlayerSystem::keyPressed(ofKeyEventArgs &args) {
	int &key = args.key;
	// KEYCODE_ATK_UP
	if (key == KEYCODE_UP) 			{		this->inputMask |= MovePlayerSystem::MOVE_UP;		}
	if (key == KEYCODE_DOWN) 		{		this->inputMask |= MovePlayerSystem::MOVE_DOWN;		}
	if (key == KEYCODE_LEFT) 		{		this->inputMask |= MovePlayerSystem::MOVE_LEFT;		}
	if (key == KEYCODE_RIGHT) 		{		this->inputMask |= MovePlayerSystem::MOVE_RIGHT;	}

	if (key == KEYCODE_ATK_UP) 		{		this->inputMask |= MovePlayerSystem::ATK_UP;		}
	if (key == KEYCODE_ATK_DOWN) 	{		this->inputMask |= MovePlayerSystem::ATK_DOWN;		}
	if (key == KEYCODE_ATK_LEFT) 	{		this->inputMask |= MovePlayerSystem::ATK_LEFT;		}
	if (key == KEYCODE_ATK_RIGHT) 	{		this->inputMask |= MovePlayerSystem::ATK_RIGHT;	}

	if (key == KEYCODE_Z) 			{		this->inputMask |= MovePlayerSystem::ATK_1;			}
	if (key == KEYCODE_X) 			{		this->inputMask |= MovePlayerSystem::ATK_2;			}

	std::cout << "KEY WAS PRESSED ! " << args.key << "UP = " << KEYCODE_UP << " " << (this->inputMask) << std::endl;
}
void MovePlayerSystem::keyReleased(ofKeyEventArgs &args) {
	int &key = args.key;
	if (key == KEYCODE_UP) 			{		this->inputMask &= ~MovePlayerSystem::MOVE_UP;		}
	if (key == KEYCODE_DOWN) 		{		this->inputMask &= ~MovePlayerSystem::MOVE_DOWN;	}
	if (key == KEYCODE_LEFT) 		{		this->inputMask &= ~MovePlayerSystem::MOVE_LEFT;	}
	if (key == KEYCODE_RIGHT) 		{		this->inputMask &= ~MovePlayerSystem::MOVE_RIGHT;	}

	if (key == KEYCODE_ATK_UP) 		{		this->inputMask &= ~MovePlayerSystem::ATK_UP;		}
	if (key == KEYCODE_ATK_DOWN) 	{		this->inputMask &= ~MovePlayerSystem::ATK_DOWN;	}
	if (key == KEYCODE_ATK_LEFT) 	{		this->inputMask &= ~MovePlayerSystem::ATK_LEFT;	}
	if (key == KEYCODE_ATK_RIGHT) 	{		this->inputMask &= ~MovePlayerSystem::ATK_RIGHT;	}

	if (key == KEYCODE_Z) 		{		this->inputMask &= ~MovePlayerSystem::ATK_1;		}
	if (key == KEYCODE_X) 		{		this->inputMask &= ~MovePlayerSystem::ATK_2;		}

	if (key == 32) {
		// RESET DRONES
	}
}




