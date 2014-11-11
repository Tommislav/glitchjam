#include "StarfieldRenderer.h"
#include "ofApp.h"





StarfieldRenderer::StarfieldRenderer(int color, int num)
{
	_numStars = num;
	_starSize = 4000000.0f;
	_color = color;
	_starArray = new GlitchStar[_numStars];
	for (int i=0; i < _numStars; i++) {
		GlitchStar star;
		randomizeStar(star);
		star.y = ofRandom(0,768);
		_starArray[i] = star;
	}
};

StarfieldRenderer::~StarfieldRenderer()
{

};




void StarfieldRenderer::update() {

	float speedX = 0.0f;
	float speedY = 1200000.0f;

	ofSetHexColor(_color);
	for (int i=0; i < _numStars; i++) {
		GlitchStar *star = &_starArray[i];
		star->y += speedY * star->z;


		if (star->y > 768) {
			randomizeStar(*star);
		}


		ofRect(_starArray[i].x, _starArray[i].y, _starArray[i].w, _starArray[i].h);
	}

};

void StarfieldRenderer::randomizeStar(GlitchStar &star) {
	float minValue = (ofRandom(1.0f) < 0.01) ? 30000.0f : 1200000.0f;

	float z = 1.0f / (ofRandom(minValue, 2000000.0f));
	star.z = z;
	star.h = star.w = _starSize * z;
	star.x = ofRandomf() * 1024;
	star.y = -star.h;
};
