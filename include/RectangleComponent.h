#ifndef RECTANGLECOMPONENT_H
#define RECTANGLECOMPONENT_H

#include <Artemis/Component.h>


class RectangleComponent : public artemis::Component
{
	public:
		int x;
		int y;
		int width;
		int height;
		int color;

		RectangleComponent(int x, int y, int w, int h, int col):x(x), y(y), width(w), height(h), color(col) {}
		~RectangleComponent() {}
};

#endif // RECTANGLECOMPONENT_H
