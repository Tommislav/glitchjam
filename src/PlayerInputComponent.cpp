#include "PlayerInputComponent.h"



PlayerInputComponent::PlayerInputComponent()
{
	this->movementBitMask = 0;
}

bool PlayerInputComponent::up() {
	return this->movementBitMask & PlayerInputComponent::MOVE_UP;
}

bool PlayerInputComponent::down() {
	return this->movementBitMask & PlayerInputComponent::MOVE_DOWN;
}

bool PlayerInputComponent::left() {
	return this->movementBitMask & PlayerInputComponent::MOVE_LEFT;
}

bool PlayerInputComponent::right() {
	return this->movementBitMask & PlayerInputComponent::MOVE_RIGHT;
}
