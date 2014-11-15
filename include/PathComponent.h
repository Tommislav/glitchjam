#ifndef PATHCOMPONENT_H_INCLUDED
#define PATHCOMPONENT_H_INCLUDED

#include <vector>
#include "ofVec2f.h"

class PathComponent : public artemis::Component {
	public:

		std::vector<ofVec2f> points;
		int pauseCountdown;
		int currentIndex;
		int endAction; // 0 = scatter, 1 = follow player
		int id;

		PathComponent(int id): currentIndex(0), id(id), pauseCountdown(120) {}
		~PathComponent(){}

	private:
		static int counter;
};
#endif // PATHCOMPONENT_H_INCLUDED
