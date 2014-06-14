#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H

#include <Artemis/Component.h>


class RectangleComponent : public artemis::Component
{
	public:
		RectangleComponent(int x, int y, int w, int h, int col);
		int x;
		int y;
		int width;
		int height;
		int color;
};

#endif // RECTANGLECOMPONENT_H
