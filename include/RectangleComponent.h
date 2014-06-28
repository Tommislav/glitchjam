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
		int layer;

		RectangleComponent(int x, int y, int w, int h, int col, int layer):x(x), y(y), width(w), height(h), color(col), layer(layer) {}
		~RectangleComponent() {}
};

#endif // RECTANGLECOMPONENT_H
