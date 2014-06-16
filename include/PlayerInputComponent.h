#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <Artemis/Component.h>


class PlayerInputComponent : public artemis::Component
{
	public:
		int &movementBitMask;

		PlayerInputComponent(int *moveBitMask):movementBitMask(*moveBitMask){}

		static const int MOVE_UP 			= 1 << 1;
		static const int MOVE_DOWN 			= 1 << 2;
		static const int MOVE_LEFT 			= 1 << 3;
		static const int MOVE_RIGHT 		= 1 << 4;

		bool up() 		{ 	return this->movementBitMask & PlayerInputComponent::MOVE_UP;		}
		bool down() 	{	return this->movementBitMask & PlayerInputComponent::MOVE_DOWN;		}
		bool left() 	{	return this->movementBitMask & PlayerInputComponent::MOVE_LEFT;		}
		bool right() 	{	return this->movementBitMask & PlayerInputComponent::MOVE_RIGHT;	}

		~PlayerInputComponent() {}
	private:
};


#endif // PLAYERINPUTCOMPONENT_H
