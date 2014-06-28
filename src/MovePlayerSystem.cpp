#include "MovePlayerSystem.h"
#include "Artemis/Entity.h"
#include <iostream>
#include "ofMain.h"
#include "FireBulletComponent.h"
#include "TurretComponent.h"

MovePlayerSystem::MovePlayerSystem():inputMask(0), up(false), down(false), turretIndex(1) {
	ofRegisterKeyEvents(this);
	addComponentType<PlayerComponent>();
}

MovePlayerSystem::~MovePlayerSystem() {
	ofUnregisterKeyEvents(this);
}

void MovePlayerSystem::initialize() {
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

	int &type = ((PlayerComponent*)e.getComponent<PlayerComponent>())->type;

	if (type != 0) { // TURRETS

		bool placeTurret = (atkUp==1 || atkDown==1 || atkLeft==1 || atkRight==1);
		bool placeThisTurret = (placeTurret && turretIndex == type);
		bool invokeTurret = (placeThisTurret || resetTurrets);


		if (invokeTurret) {

			if (placeThisTurret) {
				turretIndex = (turretIndex == 1) ? 2 : 1; // only two turrets
			}
			if (resetTurrets) { turretIndex = 1; }

			FireBulletComponent *fire 	= (FireBulletComponent*)e.getComponent<FireBulletComponent>();
			TurretComponent 	*turret = (TurretComponent*)e.getComponent<TurretComponent>();


			turret->attached = resetTurrets;
			PositionComponent *playerPos = (PositionComponent*) world->getTagManager()->getEntity("player").getComponent<PositionComponent>();


			turret->targetX = playerPos->posX + turret->offX;
			turret->targetY = playerPos->posY;
			turret->lockedInPlace = false;

			int dx, dy;
			if (atkLeft == 1) {
				dx = -1;
				dy = 0;
			} else if (atkRight == 1) {
				dx = 1;
				dy = 0;
			} else if (atkUp == 1) {
				dx = 0;
				dy = -1;
			} else if (atkDown == 1) {
				dx = 0;
				dy = 1;
			}

			if (!(dx == 0 && dy == 0)) {
				fire->dirX = 12 * dx;
				fire->dirY = 12 * dy;
				fire->offX = 5 * dx;
				fire->offY = 5 * dy;
			}

			atkUp = atkDown = atkLeft = atkRight = 0;

		}

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
	resetTurrets = false;
}

void MovePlayerSystem::keyPressed(ofKeyEventArgs &args) {
	int &key = args.key;
	// KEYCODE_ATK_UP
	if (key == KEYCODE_UP) 			{		this->inputMask |= MovePlayerSystem::MOVE_UP;		}
	if (key == KEYCODE_DOWN) 		{		this->inputMask |= MovePlayerSystem::MOVE_DOWN;		}
	if (key == KEYCODE_LEFT) 		{		this->inputMask |= MovePlayerSystem::MOVE_LEFT;		}
	if (key == KEYCODE_RIGHT) 		{		this->inputMask |= MovePlayerSystem::MOVE_RIGHT;	}

	if (key == KEYCODE_ATK_UP) 		{		this->atkUp++;			}
	if (key == KEYCODE_ATK_DOWN) 	{		this->atkDown++;		}
	if (key == KEYCODE_ATK_LEFT) 	{		this->atkLeft++;		}
	if (key == KEYCODE_ATK_RIGHT) 	{		this->atkRight++;		}

	if (key == KEYCODE_Z) 			{		this->inputMask |= MovePlayerSystem::ATK_1;			}
	if (key == KEYCODE_X) 			{		this->inputMask |= MovePlayerSystem::ATK_2;			}

	//std::cout << "KEY WAS PRESSED ! " << args.key << "UP = " << KEYCODE_UP << " " << (this->inputMask) << std::endl;
}
void MovePlayerSystem::keyReleased(ofKeyEventArgs &args) {
	int &key = args.key;
	if (key == KEYCODE_UP) 			{		this->inputMask &= ~MovePlayerSystem::MOVE_UP;		}
	if (key == KEYCODE_DOWN) 		{		this->inputMask &= ~MovePlayerSystem::MOVE_DOWN;	}
	if (key == KEYCODE_LEFT) 		{		this->inputMask &= ~MovePlayerSystem::MOVE_LEFT;	}
	if (key == KEYCODE_RIGHT) 		{		this->inputMask &= ~MovePlayerSystem::MOVE_RIGHT;	}

	if (key == KEYCODE_ATK_UP) 		{		this->atkUp = 0;		}
	if (key == KEYCODE_ATK_DOWN) 	{		this->atkDown = 0;		}
	if (key == KEYCODE_ATK_LEFT) 	{		this->atkLeft = 0;		}
	if (key == KEYCODE_ATK_RIGHT) 	{		this->atkRight = 0;		}

	if (key == KEYCODE_Z) 		{		this->inputMask &= ~MovePlayerSystem::ATK_1;		}
	if (key == KEYCODE_X) 		{		this->inputMask &= ~MovePlayerSystem::ATK_2;		}

	if (key == 32) {
		resetTurrets = true;
	}
}




