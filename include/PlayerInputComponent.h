#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include <Artemis/Component.h>


class PlayerInputComponent : public artemis::Component
{
	public:
		PlayerInputComponent();

		static const int MOVE_UP 			= 1 << 1;
		static const int MOVE_DOWN 			= 1 << 2;
		static const int MOVE_LEFT 			= 1 << 3;
		static const int MOVE_RIGHT 		= 1 << 4;

		int movementBitMask;


		bool up();
		bool down();
		bool left();
		bool right();


	private:
};

#endif // PLAYERINPUTCOMPONENT_H
