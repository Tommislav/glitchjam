#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include <Artemis/Component.h>


class VelocityComponent : public artemis::Component
{
	public:
		float vX;
		float vY;

		VelocityComponent(): vX(0), vY(0) {}
		~VelocityComponent() {}
};

#endif // VELOCITYCOMPONENT_H
