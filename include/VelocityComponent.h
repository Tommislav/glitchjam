#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include <Artemis/Component.h>


class VelocityComponent : public artemis::Component
{
	public:
		VelocityComponent();
		float vX;
		float vY;
};

#endif // VELOCITYCOMPONENT_H
