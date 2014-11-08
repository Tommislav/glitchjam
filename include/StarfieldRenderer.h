#ifndef STARFIELDRENDERER_H
#define STARFIELDRENDERER_H

#include "ofRectangle.h"

struct GlitchStar {
	float x;
	float y;
	float z;
	float w;
	float h;
	float speedX;
	float speedY;
};

class StarfieldRenderer
{
	public:
		StarfieldRenderer(int color, float size, int num);
		~StarfieldRenderer();
		void update();

	protected:
	private:
		int _numStars;
		float _starSize;
		int _color;
		GlitchStar *_starArray;
		void randomizeStar(GlitchStar &star);
};

#endif // STARFIELDRENDERER_H
