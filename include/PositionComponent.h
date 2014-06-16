#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <Artemis/Component.h>


class PositionComponent : public artemis::Component
{
	public:
		float posX;
		float posY;

		PositionComponent(float posX, float posY):posX(posX), posY(posY) {}
		~PositionComponent(){}
};

#endif // POSITIONCOMPONENT_H
