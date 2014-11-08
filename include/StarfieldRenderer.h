#ifndef STARFIELDRENDERER_H
#define STARFIELDRENDERER_H

#include "ofRectangle.h"

class StarfieldRenderer
{
	public:
		StarfieldRenderer(int color, int size, int num);
		~StarfieldRenderer();
		void update();

	protected:
	private:
		int _numStars;
		ofRectangle _starArray [];
};

#endif // STARFIELDRENDERER_H
