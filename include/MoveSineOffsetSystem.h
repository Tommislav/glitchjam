#ifndef MOVESINEOFFSETSYSTEM_H
#define MOVESINEOFFSETSYSTEM_H

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>
#include <SineOffsetComponent.h>
#include <PositionComponent.h>


class MoveSineOffsetSystem : public artemis::EntityProcessingSystem
{
	private:
		artemis::ComponentMapper<SineOffsetComponent> sineMapper;
		artemis::ComponentMapper<PositionComponent> positionMapper;

	public:
		MoveSineOffsetSystem();
		virtual ~MoveSineOffsetSystem();

		virtual void initialize() {
			sineMapper.init(*world);
			positionMapper.init(*world);
		}

		virtual void processEntity(artemis::Entity &e);
};

#endif // MOVESINEOFFSETSYSTEM_H
