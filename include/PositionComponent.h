#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <Artemis/Component.h>


class PositionComponent : public artemis::Component
{
	public:
		PositionComponent(float posX, float posY);
		float posX;
		float posY;
		void drawSomething();
		virtual ~PositionComponent();
	protected:
	private:
};

#endif // POSITIONCOMPONENT_H
