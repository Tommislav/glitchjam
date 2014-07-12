#ifndef PATHCOMPONENT_H_INCLUDED
#define PATHCOMPONENT_H_INCLUDED

#include <vector>
#include "ofVec2f.h"

class PathComponent : public artemis::Component {
	public:
		std::vector<ofVec2f> points;
		int currentIndex;
		int endAction; // 0 = scatter, 1 = follow player

		PathComponent(): currentIndex(0) {}
		~PathComponent(){}
};

#endif // PATHCOMPONENT_H_INCLUDED
