#ifndef SINEOFFSETCOMPONENT_H
#define SINEOFFSETCOMPONENT_H

#include <Artemis/Component.h>


class SineOffsetComponent : public artemis::Component
{
	public:
		SineOffsetComponent(float start, float speed):rad(start), speed(speed){
		}
		virtual ~SineOffsetComponent(){}
		float rad;
		float offset;
		float speed;

	protected:
	private:
};

#endif // SINEOFFSETCOMPONENT_H
