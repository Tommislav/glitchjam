#include "MoveSineOffsetSystem.h"
#include "Artemis/Entity.h"
#include <math.h>

MoveSineOffsetSystem::MoveSineOffsetSystem() {
	addComponentType<SineOffsetComponent>();
	addComponentType<PositionComponent>();
}


void MoveSineOffsetSystem::processEntity(artemis::Entity &e) {
	sineMapper.get(e)->rad += sineMapper.get(e)->speed;
	sineMapper.get(e)->offset = sin(sineMapper.get(e)->rad) * 3.0f;
	positionMapper.get(e)->posY += sineMapper.get(e)->offset;
}



MoveSineOffsetSystem::~MoveSineOffsetSystem() {
}
